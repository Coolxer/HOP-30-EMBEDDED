//#ifdef STSTM32
#include "endstop.h"

Endstop *endstop_init(Stepper *stepper, uint8_t *name, uint32_t port, uint8_t irq, uint16_t pin)
{
    Endstop endstop;

    endstop.parent_stepper = stepper;

    strcpy(endstop.name, name);

    endstop.port = port;
    endstop.pin = pin;
    endstop.irq = irq;

    endstop_setup_gpio(&endstop); // setups endstop gpio

    return &endstop;
}

void endstop_deinit(Endstop* endstop)
{
    HAL_NVIC_DisableIRQ(endstop->irq);
}

void endstop_setup_gpio(Endstop* endstop)
{
    GPIO_InitTypeDef gpio;

	gpio.Pin = endstop->pin;
	gpio.Mode = GPIO_MODE_IT_RISING;
	gpio.Pull = GPIO_PULLUP;

	HAL_GPIO_Init(endstop->port, &gpio);

    HAL_NVIC_EnableIRQ(endstop->irq); // enables external interrupt on endstop pin
}

uint8_t endstop_clicked(Endstop* endstop)
{
    return HAL_GPIO_ReadPin(endstop->port, endstop->pin);
}
//#endif // STSTM32