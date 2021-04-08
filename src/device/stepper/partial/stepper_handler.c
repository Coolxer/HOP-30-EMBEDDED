#include "device/stepper/partial/stepper_handler.h"

#include "device/device_manager.h"
#include "device/stepper/partial/stepper_helper.h"

void TIM2_IRQHandler(void)
{
    HAL_TIM_IRQHandler(stepper_getSlaveTimer(X_STEPPER));
}

void TIM8_BRK_TIM12_IRQHandler(void)
{
    HAL_TIM_IRQHandler(stepper_getSlaveTimer(Y_STEPPER));
}

void TIM1_BRK_TIM9_IRQHandler(void)
{
    HAL_TIM_IRQHandler(stepper_getSlaveTimer(Z_STEPPER));
}

void TIM5_IRQHandler(void)
{
    HAL_TIM_IRQHandler(stepper_getSlaveTimer(W_STEPPER));
}
