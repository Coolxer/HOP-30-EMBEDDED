#include "device/stepper/partial/stepper_peripheral.h"

#include "null.h"
#include "device/stepper/partial/stepper_state_manager.h"

#include "device/stepper/partial/stepper_calculator.h"

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

    stepper->hardware.slaveTimer.Init.Prescaler = 0;
    stepper->hardware.slaveTimer.Init.CounterMode = TIM_COUNTERMODE_UP;
    stepper->hardware.slaveTimer.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;

    HAL_TIM_Base_Init(&stepper->hardware.slaveTimer);

    //__HAL_TIM_URS_ENABLE(&stepper->hardware.slaveTimer);

    slaveConfig.SlaveMode = TIM_SLAVEMODE_EXTERNAL1;
    slaveConfig.InputTrigger = stepper->hardware.itr;
    HAL_TIM_SlaveConfigSynchronization(&stepper->hardware.slaveTimer, &slaveConfig);

    masterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    masterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    HAL_TIMEx_MasterConfigSynchronization(&stepper->hardware.slaveTimer, &masterConfig);

    HAL_NVIC_SetPriority(stepper->hardware.irq, 2, 0); // set priority of stepper slaveTimer interrupt
    HAL_NVIC_EnableIRQ(stepper->hardware.irq);         // enable stepper slaveTimer interrupt

    __HAL_TIM_CLEAR_FLAG(&stepper->hardware.slaveTimer, TIM_SR_UIF);      // clear interrupt flag
    __HAL_TIM_CLEAR_FLAG(&stepper->hardware.slaveTimer, TIM_FLAG_UPDATE); // clear update flag
    __HAL_TIM_CLEAR_IT(&stepper->hardware.slaveTimer, TIM_IT_UPDATE);     // clear update flag
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

    if (stepper_isState(stepper, MOVING))                    // check if stepper is in MOVING state i need to stop slaveTimer too
        HAL_TIM_Base_Stop_IT(&stepper->hardware.slaveTimer); // stop slaveTimer

    __HAL_TIM_SET_COUNTER(&stepper->hardware.slaveTimer, 0);  // reset slaveTimer counter
    __HAL_TIM_SET_COUNTER(&stepper->hardware.masterTimer, 0); // reset masterTimer counter
}

uint8_t stepper_reload(Stepper *stepper)
{
    uint32_t target = stepper->movement.target;

    if (target > 0)
    {
        if (target > MAX_16BIT_VALUE)
        {
            __HAL_TIM_SET_AUTORELOAD(&stepper->hardware.slaveTimer, MAX_16BIT_VALUE - 1);
            stepper->movement.target -= MAX_16BIT_VALUE;
        }
        else
        {
            __HAL_TIM_SET_AUTORELOAD(&stepper->hardware.slaveTimer, target);
            stepper->movement.target = 0;
        }

        if (stepper_isState(stepper, MOVING))
            stepper->acceleration.stepsNeededToAccelerate += (uint32_t)MAX_16BIT_VALUE - 1;

        return 1; // reloaded
    }

    return 0; // not reloaded
}