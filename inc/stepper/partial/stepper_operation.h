#ifndef STEPPER_OPERATION_H
#define STEPPER_OPERATION_H

#include "stepper/stepper.h"

uint8_t stepper_switch(Stepper *stepper, uint8_t *state);                 // switch stepper motor depend on state value (0 -> OFF, 1 -> ON)
uint8_t stepper_home(Stepper *stepper, uint8_t *direction);               // starts moving stepper motor (can be break by endstop clicked or pause / stop) with given direction
uint8_t stepper_move(Stepper *stepper, uint8_t *way, uint8_t *direction); // moves stepper motor by given number of steps (can be break by endstop clicked or pause / stop) [way in mm or deg.]

void stepper_run(Stepper *stepper); // runs stepper motor to move immediately (no given steps)

#endif // STEPPER_OPERATION_H