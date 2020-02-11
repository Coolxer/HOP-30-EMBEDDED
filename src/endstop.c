//#ifdef STSTM32
#include "endstop.h"
#include <string.h>

Endstop *endstop_init(Endstop *endstop, uint8_t *name, Stepper *parentStepper, uint32_t port, uint16_t pin, uint8_t irq)
{
    strcpy((void *)endstop->name, (void *)name);

    endstop->parentStepper = parentStepper;

    endstop->port = port;
    endstop->pin = pin;

    endstop->irq = irq;

    endstop_setupGpio(&endstop); // setups endstop gpio

    return &endstop;
}

void endstop_deinit(Endstop *endstop)
{
    HAL_NVIC_DisableIRQ(endstop->irq);
}

void endstop_setupGpio(Endstop *endstop)
{
    GPIO_InitTypeDef gpio;

	gpio.Pin = endstop->pin;
	gpio.Mode = GPIO_MODE_IT_RISING;
	gpio.Pull = GPIO_PULLUP;

	HAL_GPIO_Init(endstop->port, &gpio);

    HAL_NVIC_SetPriority(endstop->irq, 0, 0);
    HAL_NVIC_EnableIRQ(endstop->irq); // enables external interrupt on endstop pin
}

uint8_t endstop_isClicked(Endstop *endstop)
{
    return HAL_GPIO_ReadPin(endstop->port, endstop->pin);
}
//#endif // STSTM32