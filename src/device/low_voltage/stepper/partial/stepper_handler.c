#include "device/low_voltage/stepper/partial/stepper_handler.h"

#include "device/device_manager.h"
#include "device/low_voltage/stepper/partial/stepper_helper.h"

void TIM1_BRK_TIM9_IRQHandler(void)
{
    HAL_TIM_IRQHandler(stepper_getSlaveTimer(A_STEPPER));
}

void TIM8_BRK_TIM12_IRQHandler(void)
{
    HAL_TIM_IRQHandler(stepper_getSlaveTimer(X_STEPPER));
}

void TIM3_IRQHandler(void)
{
    HAL_TIM_IRQHandler(stepper_getSlaveTimer(Y_STEPPER));
}

void TIM5_IRQHandler(void)
{
    HAL_TIM_IRQHandler(stepper_getSlaveTimer(Z_STEPPER));
}