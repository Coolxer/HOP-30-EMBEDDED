#include "device/low_voltage/endstop/structure/endstop_debounce.h"

Debounce endstop_debounce_init()
{
    Debounce debounce = {0};

    debounce.time = 0;
    debounce.counter = 0;

    debounce.CLICKED_FLAG = RESET;
    debounce.DEBOUNCING_FLAG = RESET;

    return debounce;
}