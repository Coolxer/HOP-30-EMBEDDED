#ifndef ENDSTOP_OPERATION_H
#define ENDSTOP_OPERATION_H

#include "device/endstop/endstop.h"

uint8_t endstop_isClicked(Endstop *endstop); // returns the current endstop state

/* PRIVATE */ //void endstop_debounce_init(Endstop *endstop); // starts debounce time

void endstop_debounce(Endstop *endstop); // services endstop debounce

#endif // ENDSTOP_OPERATION_H
