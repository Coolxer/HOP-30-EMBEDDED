#include "endstop/partial/endstop_setup.h"

#include <string.h>

void endstop_setupGpio(Endstop *endstop)
{
    GPIO_InitTypeDef gpio = {0};

    gpio.Pin = endstop->pin;
    gpio.Mode = GPIO_MODE_IT_RISING;
    gpio.Pull = GPIO_PULLUP;

    HAL_GPIO_Init((GPIO_TypeDef *)endstop->port, &gpio);

    HAL_NVIC_SetPriority(endstop->irq, 0, 0); // set priority of endstop interrupt
    HAL_NVIC_EnableIRQ(endstop->irq);         // enables external interrupt on endstop pin
}

void endstop_init(Endstop *endstop, uint8_t *name, GPIO_TypeDef *port, uint16_t pin, uint8_t irq)
{
    strcpy((void *)endstop->name, (void *)name);

    endstop->port = port;
    endstop->pin = pin;
    endstop->irq = irq;

    endstop_setupGpio(endstop); // setups endstop gpio
}

void endstop_deinit(Endstop *endstop)
{
    HAL_NVIC_DisableIRQ(endstop->irq);
}
