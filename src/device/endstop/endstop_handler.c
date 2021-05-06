#include "device/endstop/partial/endstop_handler.h"

#include "device/endstop/config/endstop_connection.h"

void EXTI2_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(ZL_PIN);
}

void EXTI3_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(ZR_PIN);
}

void EXTI9_5_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(YL_PIN);
}

void EXTI15_10_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(XL_PIN);
  HAL_GPIO_EXTI_IRQHandler(XR_PIN);
  HAL_GPIO_EXTI_IRQHandler(YR_PIN);
}