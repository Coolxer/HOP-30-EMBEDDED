#include "device/stepper/partial/stepper_handler.h"

#include "device/device_manager.h"

void TIM2_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&X_STEPPER->hardware.slaveTimer);
}

void TIM8_BRK_TIM12_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&Y_STEPPER->hardware.slaveTimer);
}

void TIM1_BRK_TIM9_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&Z_STEPPER->hardware.slaveTimer);
}

void TIM5_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&W_STEPPER->hardware.slaveTimer);
}
