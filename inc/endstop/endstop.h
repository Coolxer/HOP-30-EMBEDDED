#ifndef ENDSTOP_H
#define ENDSTOP_H

#include "stm32f4xx_hal.h"

typedef struct
{
    uint8_t name[2]; // 2-characters name

    GPIO_TypeDef *port; // gpio port
    uint16_t pin;       // endstop pin
    uint8_t irq;        // external interrupt name pointer
} Endstop;

Endstop *endstop; // endstop pointer, using to make operations on actual selected endstop

#endif // ENDSTOP_H
