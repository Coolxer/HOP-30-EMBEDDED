//#ifdef STSTM32
#include "endstop.h"

Endstop *endstop_init(Stepper *_stepper, uint8_t *_name, uint32_t _port, uint8_t _ext, uint16_t _pin)
{
    Endstop endstop;

    endstop.parent_stepper = _stepper;

    endstop.port = _port;
    endstop.pin = _pin;
    endstop.ext = _ext;

    endstop_setup_gpio(&endstop); // setups endstop gpio

    return &endstop;
}

void endstop_deinit(Endstop* endstop)
{
    HAL_NVIC_DisableIRQ(endstop->ext);
}

void endstop_setup_gpio(Endstop* endstop)
{
    GPIO_InitTypeDef gpio;

	gpio.Pin = endstop->pin;
	gpio.Mode = GPIO_MODE_IT_RISING;
	gpio.Pull = GPIO_PULLUP;

	HAL_GPIO_Init(endstop->port, &gpio);

    HAL_NVIC_EnableIRQ(endstop->ext); // enables external interrupt on endstop pin
}

uint8_t endstop_clicked(Endstop* endstop)
{
    endstop->clicked = HAL_GPIO_ReadPin(endstop->port, endstop->pin); // assigns current endstop state by reading state on endstop pin
    return endstop->clicked;
}
//#endif // STSTM32