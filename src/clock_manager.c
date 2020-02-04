#include "clock_manager.h"

#include "stm32f4xx_hal.h"

void clocks_init()
{
    __HAL_RCC_GPIOA_CLK_ENABLE();  // enables port A clock, where divider motor is connected 
    __HAL_RCC_GPIOB_CLK_ENABLE();  // enables port B clock, where table motor is connected 

    __HAL_RCC_TIM3_CLK_ENABLE();
    __HAL_RCC_TIM4_CLK_ENABLE();

}

void clocks_deinit()
{
    __HAL_RCC_GPIOA_CLK_DISABLE(); // disables port A clock
    __HAL_RCC_GPIOB_CLK_DISABLE(); // disables port A clock

    __HAL_RCC_TIM3_CLK_DISABLE();
    __HAL_RCC_TIM4_CLK_DISABLE();
}
