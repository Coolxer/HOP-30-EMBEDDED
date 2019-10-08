//#ifdef STSTM32
#include "endstop_divider_min.h"

struct Endstop *create_endstop_divider_min()
{
    endstop_init(&endstop_divider_min, "div_MIN", GPIOA, EXTI15_10_IRQn, GPIO_PIN_5);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if(GPIO_Pin == endstop_divider_min.pin)
    {
        if(HAL_GPIO_ReadPin(endstop_divider_min.port, endstop_divider_min.pin))
            endstop_divider_min.clicked = 1;
        else
             endstop_divider_min.clicked = 0;
    }
}

//#endif // STSTM32

