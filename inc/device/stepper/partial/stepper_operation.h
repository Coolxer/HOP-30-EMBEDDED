#ifndef STEPPER_OPERATION_H
#define STEPPER_OPERATION_H

#include "device/stepper/stepper.h"

void stepper_switch(Stepper *stepper, uint8_t state); // switch stepper motor depend on state value (0 -> OFF, 1 -> ON)

void stepper_move(Stepper *stepper, float way, uint8_t direction); // moves stepper motor by given number of steps (can be break by endstop clicked or pause / stop) [way in mm or deg.]
                                                                   // if way is 0 it moves until endstop clicked

void stepper_run(Stepper *stepper);      // runs stepper motor when everything is configured (starts moving)
void stepper_watchdog(Stepper *stepper); // manages current stepper movement (acceleration)

#endif // STEPPER_OPERATION_H