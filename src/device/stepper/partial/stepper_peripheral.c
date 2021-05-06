
#include "null.h"

#include "device/stepper/partial/stepper_peripheral.h"
#include "device/stepper/partial/stepper_calculator.h"
#include "device/stepper/partial/stepper_helper.h"

void stepper_setupGpio(Stepper *stepper)
{
    GPIO_InitTypeDef gpioEnable = {0};
    GPIO_InitTypeDef gpioStep = {0};
    GPIO_InitTypeDef gpioDir = {0};

    /* setups gpio for enable_pin */
    gpioEnable.Pin = stepper->hardware.enablePin;
    gpioEnable.Mode = GPIO_MODE_OUTPUT_OD;
    gpioEnable.Pull = GPIO_PULLUP;
    gpioEnable.Speed = GPIO_SPEED_FREQ_LOW;

    HAL_GPIO_Init((GPIO_TypeDef *)stepper->hardware.enablePort, &gpioEnable);
    HAL_GPIO_WritePin((GPIO_TypeDef *)stepper->hardware.enablePort, stepper->hardware.enablePin, GPIO_PIN_SET);

    /* setups gpio for step_pin */
    gpioStep.Pin = stepper->hardware.stepPin;
    gpioStep.Mode = GPIO_MODE_AF_OD;
    gpioStep.Pull = GPIO_PULLDOWN;
    gpioStep.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    gpioStep.Alternate = stepper->hardware.alternateFunction;

    HAL_GPIO_Init((GPIO_TypeDef *)stepper->hardware.stepPort, &gpioStep);
    HAL_GPIO_WritePin((GPIO_TypeDef *)stepper->hardware.stepPort, stepper->hardware.stepPin, GPIO_PIN_RESET);

    /* setups gpio for dir_pin */
    gpioDir.Pin = stepper->hardware.dirPin;
    gpioDir.Mode = GPIO_MODE_OUTPUT_OD;
    gpioDir.Pull = GPIO_PULLDOWN;
    gpioDir.Speed = GPIO_SPEED_FREQ_MEDIUM;

    HAL_GPIO_Init((GPIO_TypeDef *)stepper->hardware.dirPort, &gpioDir);
    HAL_GPIO_WritePin((GPIO_TypeDef *)stepper->hardware.dirPort, stepper->hardware.dirPin, GPIO_PIN_RESET);
}

void stepper_setupMasterTimer(Stepper *stepper)
{
    TIM_MasterConfigTypeDef masterConfig = {0};
    TIM_OC_InitTypeDef configOC = {0};

    stepper->hardware.masterTimer.Init.CounterMode = TIM_COUNTERMODE_UP;
    stepper->hardware.masterTimer.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;

    stepper->hardware.masterTimer.Init.Prescaler = 0;
    stepper->hardware.masterTimer.Init.Period = 0;

    stepper->hardware.masterTimer.Instance->CNT = 0;
    HAL_TIM_Base_Init(&stepper->hardware.masterTimer);

    //clockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    //HAL_TIM_ConfigClockSource(&stepper->hardware.master_timer, &clockSourceConfig);

    masterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
    masterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    HAL_TIMEx_MasterConfigSynchronization(&stepper->hardware.masterTimer, &masterConfig);

    configOC.OCMode = TIM_OCMODE_PWM1;
    configOC.Pulse = 0;
    configOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    configOC.OCFastMode = TIM_OCFAST_ENABLE; // TIM_OCFAST_DISABLE
    HAL_TIM_PWM_ConfigChannel(&stepper->hardware.masterTimer, &configOC, stepper->hardware.channel);
}

void stepper_setupSlaveTimer(Stepper *stepper)
{
    TIM_SlaveConfigTypeDef slaveConfig = {0};
    TIM_MasterConfigTypeDef masterConfig = {0};

    stepper->hardware.slaveTimer.Init.Prescaler = 0;
    stepper->hardware.slaveTimer.Init.CounterMode = TIM_COUNTERMODE_UP;
    stepper->hardware.slaveTimer.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;

    HAL_TIM_Base_Init(stepper_getSlaveTimer(stepper));

    slaveConfig.SlaveMode = TIM_SLAVEMODE_EXTERNAL1;
    slaveConfig.InputTrigger = stepper->hardware.itr;
    HAL_TIM_SlaveConfigSynchronization(stepper_getSlaveTimer(stepper), &slaveConfig);

    masterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    masterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    HAL_TIMEx_MasterConfigSynchronization(stepper_getSlaveTimer(stepper), &masterConfig);

    HAL_NVIC_SetPriority(stepper->hardware.irq, 2, 0); // set priority of stepper slaveTimer interrupt
    HAL_NVIC_EnableIRQ(stepper->hardware.irq);         // enable stepper slaveTimer interrupt

    __HAL_TIM_CLEAR_FLAG(stepper_getSlaveTimer(stepper), TIM_SR_UIF);      // clear interrupt flag
    __HAL_TIM_CLEAR_FLAG(stepper_getSlaveTimer(stepper), TIM_FLAG_UPDATE); // clear update flag
    __HAL_TIM_CLEAR_IT(stepper_getSlaveTimer(stepper), TIM_IT_UPDATE);     // clear update flag
}

void stepper_setPeripherals(Stepper *stepper)
{
    stepper_setupGpio(stepper);
    stepper_setupMasterTimer(stepper);
    stepper_setupSlaveTimer(stepper);
}

void stepper_setSpeedRegisters(Stepper *stepper, uint16_t psc, uint16_t arr, uint16_t pul)
{
    __HAL_TIM_SET_PRESCALER(&stepper->hardware.masterTimer, psc);
    __HAL_TIM_SET_AUTORELOAD(&stepper->hardware.masterTimer, arr);
    __HAL_TIM_SET_COMPARE(&stepper->hardware.masterTimer, stepper->hardware.channel, pul); // set pulse width
}

void stepper_stopTimers(Stepper *stepper)
{
    HAL_TIM_PWM_Stop(&stepper->hardware.masterTimer, stepper->hardware.channel); // stop masterTimer

    if (stepper_getMoveType(stepper) == PRECISED)
        HAL_TIM_Base_Stop_IT(stepper_getSlaveTimer(stepper));

    __HAL_TIM_SET_COUNTER(stepper_getSlaveTimer(stepper), 0); // reset slaveTimer counter
    __HAL_TIM_SET_COUNTER(&stepper->hardware.masterTimer, 0); // reset masterTimer counter
}

uint8_t stepper_reload(Stepper *stepper)
{
    uint32_t steps = stepper_getUnloadedSteps(stepper);

    if (steps > 0)
    {
        if (steps > MAX_16BIT_VALUE)
        {
            __HAL_TIM_SET_AUTORELOAD(stepper_getSlaveTimer(stepper), MAX_16BIT_VALUE - 1);
            steps -= MAX_16BIT_VALUE;
        }
        else
        {
            __HAL_TIM_SET_AUTORELOAD(stepper_getSlaveTimer(stepper), steps);
            steps = 0;
        }

        stepper_setUnloadedSteps(stepper, steps);

        if (stepper_getSpeedState(stepper) == RAISING)
            stepper_setStepsNeededToAccelerate(stepper, stepper_getStepsNeededToAccelerate(stepper) + ((uint32_t)MAX_16BIT_VALUE - 1));

        return 1; // reloaded
    }

    return 0; // not reloaded
}
