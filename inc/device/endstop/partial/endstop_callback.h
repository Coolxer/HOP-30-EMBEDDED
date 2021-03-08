#ifndef ENDSTOP_CALLBACK_H
#define ENDSTOP_CALLBACK_H

#include "device/endstop/endstop.h"

/* PRIVATE */                                  //uint8_t endstop_homeCallback(Stepper *stepper);
void endstopClickedCallback(Endstop *endstop); // endstop clicked callback

#endif // ENDSTOP_CALLBACK_H