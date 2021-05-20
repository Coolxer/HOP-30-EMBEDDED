#ifndef ENDSTOP_DEBOUNCE_H
#define ENDSTOP_DEBOUNCE_H

#include "stm32f4xx_hal.h"

typedef struct
{
    uint32_t time;   // current time (for DEBOUNCE)
    uint8_t counter; // number of accepted clicks

    volatile uint8_t CLICKED_FLAG;    // endstop clicked flag
    volatile uint8_t DEBOUNCING_FLAG; // endstop currently in debounce mode flag
} Debounce;

Debounce endstop_debounce_init();

#endif // ENDSTOP_DEBOUNCE_H