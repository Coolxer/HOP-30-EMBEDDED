#include "device/endstop/partial/endstop_setup.h"

#include <string.h>

void endstop_setupGpio(Endstop *endstop)
{
    GPIO_InitTypeDef gpio = {0};

    gpio.Pin = endstop->pin;
    gpio.Mode = GPIO_MODE_IT_RISING;
    gpio.Pull = GPIO_PULLUP;

    HAL_GPIO_Init((GPIO_TypeDef *)endstop->port, &gpio);

    HAL_NVIC_SetPriority(endstop->irq, 0, 0); // set priority of endstop interrupt [MOST IMPORTANT]
    HAL_NVIC_EnableIRQ(endstop->irq);         // enables external interrupt on endstop pin
}

void endstop_init(Endstop *endstop, GPIO_TypeDef *port, uint16_t pin, uint8_t irq)
{
    endstop->port = port;
    endstop->pin = pin;
    endstop->irq = irq;

    endstop->time = 0;

    endstop->CLICKED_FLAG = RESET;
    endstop->DEBOUNCING_FLAG = RESET;

    endstop_setupGpio(endstop);
}

void endstop_deinit(Endstop *endstop)
{
    HAL_NVIC_DisableIRQ(endstop->irq);
}
