#include "stepper/partial/stepper_peripheral.h"

void stepper_setupGpio(Stepper *stepper)
{
    GPIO_InitTypeDef gpio;

    /* setups gpio for all stepper pins except step_pin */
    gpio.Pin = stepper->dir | stepper->enable;
    gpio.Mode = GPIO_MODE_OUTPUT_PP;
    gpio.Pull = GPIO_NOPULL;
    gpio.Speed = GPIO_SPEED_FREQ_LOW;

    HAL_GPIO_Init((GPIO_TypeDef *)stepper->port, &gpio);
    HAL_GPIO_WritePin((GPIO_TypeDef *)stepper->port, stepper->enable, GPIO_PIN_SET);

    /* setups gpio for step_pin */
    gpio.Pin = stepper->step;
    gpio.Mode = GPIO_MODE_AF_PP;
    gpio.Pull = GPIO_PULLUP;
    gpio.Speed = GPIO_SPEED_FREQ_HIGH;
    gpio.Alternate = stepper->alternateFunction;

    HAL_GPIO_Init((GPIO_TypeDef *)stepper->port, &gpio);
}

void stepper_setupMasterTimer(Stepper *stepper)
{
    TIM_MasterConfigTypeDef masterConfig = {0};
    TIM_OC_InitTypeDef configOC = {0};

    stepper->masterTimer.Init.CounterMode = TIM_COUNTERMODE_UP;
    stepper->masterTimer.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    stepper->masterTimer.Init.Prescaler = 0;
    stepper->masterTimer.Init.Period = 0;
    stepper->masterTimer.Instance->CNT = 0;
    HAL_TIM_Base_Init(&stepper->masterTimer);

    //clockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    //HAL_TIM_ConfigClockSource(&stepper->master_timer, &clockSourceConfig);

    masterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
    masterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    HAL_TIMEx_MasterConfigSynchronization(&stepper->masterTimer, &masterConfig);

    configOC.OCMode = TIM_OCMODE_PWM1;
    configOC.Pulse = 0;
    configOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    configOC.OCFastMode = TIM_OCFAST_ENABLE; // TIM_OCFAST_DISABLE
    HAL_TIM_PWM_ConfigChannel(&stepper->masterTimer, &configOC, stepper->channel);
}

void stepper_setupSlaveTimer(Stepper *stepper)
{
    TIM_SlaveConfigTypeDef slaveConfig = {0};
    TIM_MasterConfigTypeDef masterConfig = {0};

    stepper->slaveTimer.Init.Prescaler = 0;
    stepper->slaveTimer.Init.CounterMode = TIM_COUNTERMODE_UP;
    stepper->slaveTimer.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    stepper->slaveTimer.Instance->CNT = 0;
    HAL_TIM_Base_Init(&stepper->slaveTimer);

    __HAL_TIM_CLEAR_FLAG(&stepper->slaveTimer, TIM_SR_UIF);  // clear interrupt flag
    __HAL_TIM_CLEAR_IT(&stepper->slaveTimer, TIM_IT_UPDATE); // clear update flag

    slaveConfig.SlaveMode = TIM_SLAVEMODE_EXTERNAL1;
    slaveConfig.InputTrigger = stepper->itr;
    HAL_TIM_SlaveConfigSynchronization(&stepper->slaveTimer, &slaveConfig);

    masterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    masterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    HAL_TIMEx_MasterConfigSynchronization(&stepper->slaveTimer, &masterConfig);

    HAL_NVIC_SetPriority(stepper->irq, 0, 0); // set priority of stepper slaveTimer interrupt
    HAL_NVIC_EnableIRQ(stepper->irq);         // enable stepper slaveTimer interrupt
}

void stepper_setup_peripherals(Stepper *stepper)
{
    stepper_setupGpio(stepper);
    stepper_setupMasterTimer(stepper);
    stepper_setupSlaveTimer(stepper);
}