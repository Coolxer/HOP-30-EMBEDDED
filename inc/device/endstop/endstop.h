#ifndef ENDSTOP_H
#define ENDSTOP_H

#include "stm32f4xx_hal.h"

typedef struct
{
    uint8_t name[2]; // 2-characters name

    GPIO_TypeDef *port; // gpio port
    uint16_t pin;       // endstop pin
    uint8_t irq;        // external interrupt name pointer

    uint8_t state;
    uint8_t lastState;
} Endstop;

#endif // ENDSTOP_H
