#ifndef ENDSTOP_OPERATION_H
#define ENDSTOP_OPERATION_H

#include "device/endstop/endstop.h"

uint8_t endstop_isClicked(Endstop *endstop); // returns the current endstop state

void endstop_debounce(Endstop *endstop);

#endif // ENDSTOP_OPERATION_H
