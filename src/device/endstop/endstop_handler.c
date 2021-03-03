#include "device/endstop/partial/endstop_handler.h"

#include "device/endstop/config/endstop_connection.h"

void EXTI0_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(XL_PIN);
}

void EXTI1_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(XR_PIN);
}

void EXTI2_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(YL_PIN);
}

void EXTI3_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(YR_PIN);
}

void EXTI4_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(ZL_PIN);
}

void EXTI9_5_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(ZR_PIN);
}