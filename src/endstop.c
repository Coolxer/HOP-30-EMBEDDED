//#ifdef STSTM32
#include "endstop.h"

void endstop_init(struct Endstop* e, uint8_t *_name, uint32_t _port, uint16_t _pin)
{
    strcpy(e->name, _name);
    e->port = _port;
    e->pin = _pin;

    endstop_setup_gpio(e);
}

void endstop_setup_gpio(struct Endstop *e)
{
    GPIO_InitTypeDef gpio;

	gpio.Pin = e->pin;
	gpio.Mode = GPIO_MODE_AF_PP;
	gpio.Pull = GPIO_NOPULL;
	gpio.Speed = GPIO_SPEED_FREQ_LOW;

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

   return HAL_GPIO_ReadPin(e->port, e->pin);
}

//#endif // STSTM32