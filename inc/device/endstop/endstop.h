#ifndef ENDSTOP_H
#define ENDSTOP_H

#include "stm32f4xx_hal.h"

typedef struct
{
    GPIO_TypeDef *port;
    uint16_t pin;
    uint8_t irq; // external interrupt name pointer

    uint32_t time; // current time (for DEBOUNCE)

    volatile uint8_t CLICKED_FLAG;    // endstop clicked flag
    volatile uint8_t DEBOUNCING_FLAG; // endstop currently in debounce mode flag
} Endstop;

#endif // ENDSTOP_H
