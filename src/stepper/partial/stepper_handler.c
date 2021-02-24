#include "stepper/partial/stepper_handler.h"

#include "device_manager.h"

void TIM2_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&device_manager_getStepper((uint8_t *)"x")->hardware.slaveTimer);
}

void TIM5_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&device_manager_getStepper((uint8_t *)"w")->hardware.slaveTimer);
}

void TIM1_BRK_TIM9_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&device_manager_getStepper((uint8_t *)"z")->hardware.slaveTimer);
}

void TIM8_BRK_TIM12_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&device_manager_getStepper((uint8_t *)"y")->hardware.slaveTimer);
}
