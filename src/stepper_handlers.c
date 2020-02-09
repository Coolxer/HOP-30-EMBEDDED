#include "stepper_handlers.h"

#include "device_manager.h"

void TIM2_IRQHandler(void)
{
    //HAL_TIM_IRQHandler(&steppers[0].slaveTimer);
    HAL_TIM_IRQHandler(&device_manager_getStepper("x")->slaveTimer);
}

void TIM5_IRQHandler(void)
{
    //HAL_TIM_IRQHandler(&steppers[1].slaveTimer);
    HAL_TIM_IRQHandler(&device_manager_getStepper("y")->slaveTimer);
}

void TIM1_BRK_TIM9_IRQHandler(void)
{
    //HAL_TIM_IRQHandler(&steppers[2].slaveTimer);
    HAL_TIM_IRQHandler(&device_manager_getStepper("z")->slaveTimer);
}

void TIM8_BRK_TIM12_IRQHandler(void)
{
    //HAL_TIM_IRQHandler(&steppers[3].slaveTimer);
    HAL_TIM_IRQHandler(&device_manager_getStepper("w")->slaveTimer);
}
