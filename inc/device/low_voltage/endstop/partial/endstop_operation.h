#ifndef ENDSTOP_OPERATION_H
#define ENDSTOP_OPERATION_H

#include "device/low_voltage/endstop/endstop.h"

uint8_t endstop_isClicked(Endstop *endstop); // returns the current endstop state
void endstop_debounce(Endstop *endstop);     // services endstop debounce

#endif // ENDSTOP_OPERATION_H
