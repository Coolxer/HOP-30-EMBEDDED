#include "stepper_handlers.h"

#include "device_manager.h"

void TIM2_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&device_manager_getStepper((uint8_t*)"x")->slaveTimer);
}

void TIM5_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&device_manager_getStepper((uint8_t*)"w")->slaveTimer);
}

void TIM1_BRK_TIM9_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&device_manager_getStepper((uint8_t*)"z")->slaveTimer);
}

void TIM8_BRK_TIM12_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&device_manager_getStepper((uint8_t*)"y")->slaveTimer);
}
