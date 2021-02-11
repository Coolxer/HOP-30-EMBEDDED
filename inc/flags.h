#ifndef FLAGS_H
#define FLAGS_H

#include "stm32f4xx_hal.h"

uint8_t ENDSTOP_CLICKED;
uint8_t STEPPER_FINISHED;

uint8_t PROCESS_FORWARD;

void flags_init(); // set default flags states

#endif // FLAGS_H