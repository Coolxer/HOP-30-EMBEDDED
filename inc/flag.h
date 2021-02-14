#ifndef FLAG_H
#define FLAG_H

#include <stdint.h>

uint8_t ENDSTOP_CLICKED;
uint8_t STEPPER_FINISHED;

uint8_t PROCESS_FORWARD;

void flag_init(); // set default flags states

#endif // FLAG_H