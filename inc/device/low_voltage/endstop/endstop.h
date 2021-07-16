#ifndef ENDSTOP_H
#define ENDSTOP_H

#include "stm32f4xx_hal.h"

#include "device/low_voltage/endstop/structure/endstop_hardware.h"
#include "device/low_voltage/endstop/structure/endstop_debounce.h"

typedef struct
{
    uint8_t *name;

    Hardwaree hardware;
    Debounce debounce;

} Endstop;

#endif // ENDSTOP_H
