
#include "null.h"

#include "device/stepper/partial/stepper_peripheral.h"
#include "device/stepper/partial/stepper_calculator.h"
#include "device/stepper/partial/stepper_helper.h"

void stepper_setupGpio(Stepper *stepper)
{
    GPIO_InitTypeDef gpio = {0};

    /* setups gpio for all stepper pins except step_pin */
    gpio.Pin = stepper->hardware.dir | stepper->hardware.enable;
    gpio.Mode = GPIO_MODE_OUTPUT_PP;
    gpio.Pull = GPIO_NOPULL;
    gpio.Speed = GPIO_SPEED_FREQ_LOW;

    HAL_GPIO_Init((GPIO_TypeDef *)stepper->hardware.port, &gpio);
    HAL_GPIO_WritePin((GPIO_TypeDef *)stepper->hardware.port, stepper->hardware.enable, GPIO_PIN_SET);

    /* setups gpio for step_pin */
    gpio.Pin = stepper->hardware.step;
    gpio.Mode = GPIO_MODE_AF_PP;
    gpio.Pull = GPIO_PULLUP;
    gpio.Speed = GPIO_SPEED_FREQ_HIGH;
    gpio.Alternate = stepper->hardware.alternateFunction;

    HAL_GPIO_Init((GPIO_TypeDef *)stepper->hardware.port, &gpio);
    HAL_GPIO_WritePin((GPIO_TypeDef *)stepper->hardware.port, stepper->hardware.step, GPIO_PIN_RESET);
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

    getSlaveTimer(stepper)->Init.Prescaler = 0;
    getSlaveTimer(stepper)->Init.CounterMode = TIM_COUNTERMODE_UP;
    getSlaveTimer(stepper)->Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;

    HAL_TIM_Base_Init(getSlaveTimer(stepper));

    slaveConfig.SlaveMode = TIM_SLAVEMODE_EXTERNAL1;
    slaveConfig.InputTrigger = stepper->hardware.itr;
    HAL_TIM_SlaveConfigSynchronization(getSlaveTimer(stepper), &slaveConfig);

    masterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    masterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    HAL_TIMEx_MasterConfigSynchronization(getSlaveTimer(stepper), &masterConfig);

    HAL_NVIC_SetPriority(stepper->hardware.irq, 2, 0); // set priority of stepper slaveTimer interrupt
    HAL_NVIC_EnableIRQ(stepper->hardware.irq);         // enable stepper slaveTimer interrupt

    __HAL_TIM_CLEAR_FLAG(getSlaveTimer(stepper), TIM_SR_UIF);      // clear interrupt flag
    __HAL_TIM_CLEAR_FLAG(getSlaveTimer(stepper), TIM_FLAG_UPDATE); // clear update flag
    __HAL_TIM_CLEAR_IT(getSlaveTimer(stepper), TIM_IT_UPDATE);     // clear update flag
}

void stepper_setPeripherals(Stepper *stepper)
{
    stepper_setupGpio(stepper);
    stepper_setupMasterTimer(stepper);
    stepper_setupSlaveTimer(stepper);
}

void stepper_stopTimers(Stepper *stepper)
{
    HAL_TIM_PWM_Stop(&stepper->hardware.masterTimer, stepper->hardware.channel); // stop masterTimer

    if (getState(stepper) == MOVING)                  // check if stepper is in MOVING state i need to stop slaveTimer too
        HAL_TIM_Base_Stop_IT(getSlaveTimer(stepper)); // stop slaveTimer

    __HAL_TIM_SET_COUNTER(getSlaveTimer(stepper), 0);         // reset slaveTimer counter
    __HAL_TIM_SET_COUNTER(&stepper->hardware.masterTimer, 0); // reset masterTimer counter
}

uint8_t stepper_reload(Stepper *stepper)
{
    uint32_t target = getGeneralTarget(stepper);

    if (target > 0)
    {
        if (target > MAX_16BIT_VALUE)
        {
            __HAL_TIM_SET_AUTORELOAD(getSlaveTimer(stepper), MAX_16BIT_VALUE - 1);
            target -= MAX_16BIT_VALUE;
        }
        else
        {
            __HAL_TIM_SET_AUTORELOAD(getSlaveTimer(stepper), target);
            target = 0;
        }

        setGeneralTarget(stepper, target);

        if (getState(stepper) == MOVING)
            setStepsNeededToAccelerate(stepper, getStepsNeededToAccelerate(stepper) + ((uint32_t)MAX_16BIT_VALUE - 1));

        return 1; // reloaded
    }

    return 0; // not reloaded
}

void stepper_setSpeedRegisters(Stepper *stepper, uint16_t psc, uint16_t arr, uint16_t pul)
{
    __HAL_TIM_SET_PRESCALER(&stepper->hardware.masterTimer, psc);
    __HAL_TIM_SET_AUTORELOAD(&stepper->hardware.masterTimer, arr);
    __HAL_TIM_SET_COMPARE(&stepper->hardware.masterTimer, stepper->hardware.channel, pul); // set pulse width
}