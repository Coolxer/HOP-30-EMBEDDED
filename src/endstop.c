//#ifdef STSTM32
#include "endstop.h"

void endstop_init(struct Endstop* e, uint8_t *_name, uint32_t _port, uint8_t _ext, uint16_t _pin)
{
    strcpy(e->name, _name);
    e->port = _port;
    e->pin = _pin;
    e->ext = _ext;

    endstop_setup_gpio(e);

    //there are 3 groups of EXT interrupts
    // EXTI0_IRQn - EXTI4_IRQn  -> 0-4
    // EXTI9_5_IRQn -> 5-9
    // EXTI15_10_IRQn -> 10-15

    //HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
    HAL_NVIC_EnableIRQ(e->ext);
}

void endstop_setup_gpio(struct Endstop *e)
{
    GPIO_InitTypeDef gpio;

	gpio.Pin = e->pin;
	gpio.Mode = GPIO_MODE_IT_RISING_FALLING;
	gpio.Pull = GPIO_NOPULL;

	HAL_GPIO_Init(e->port, &gpio);
}

uint8_t endstop_clicked(struct Endstop *e)
{
    /*
    if(HAL_GPIO_ReadPin(e->port, e->pin))
        return 1;
    else
        return 0;
    */
   e->clicked = HAL_GPIO_ReadPin(e->port, e->pin);
   return e->clicked;
}

//#endif // STSTM32