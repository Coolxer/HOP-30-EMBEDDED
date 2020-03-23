//#ifdef STSTM32
#include "endstop.h"
#include <string.h>

void endstop_init(Endstop *endstop, uint8_t *name, Stepper *parentStepper, uint32_t port, uint16_t pin, uint8_t irq)
{
    strcpy((void *)endstop->name, (void *)name);

    endstop->parentStepper = parentStepper;

    endstop->port = port;
    endstop->pin = pin;

    endstop->irq = irq;

    endstop_setupGpio(endstop); // setups endstop gpio

    endstop->clicked = HAL_GPIO_ReadPin((GPIO_TypeDef*)endstop->port, endstop->pin); // read actual endstop pin
}

void endstop_deinit(Endstop *endstop)
{
    HAL_NVIC_DisableIRQ(endstop->irq);
}

void endstop_setupGpio(Endstop *endstop)
{
    GPIO_InitTypeDef gpio;

	gpio.Pin = endstop->pin;
	gpio.Mode = GPIO_MODE_IT_RISING_FALLING;
	gpio.Pull = GPIO_NOPULL;

	HAL_GPIO_Init((GPIO_TypeDef*)endstop->port, &gpio);

    HAL_NVIC_SetPriority(endstop->irq, 0, 0); // set priority of endstop interrupt
    HAL_NVIC_EnableIRQ(endstop->irq); // enables external interrupt on endstop pin
}

uint8_t* endstop_isClicked(Endstop *endstop)
{
    if(!HAL_GPIO_ReadPin((GPIO_TypeDef*)endstop->port, endstop->pin))
        return "0";

    return "1";
}

//#endif // STSTM32