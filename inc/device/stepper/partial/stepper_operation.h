#ifndef STEPPER_OPERATION_H
#define STEPPER_OPERATION_H

#include "device/stepper/stepper.h"
#include "device/stepper/enum/home_step.h"

void stepper_switch(Stepper *stepper, uint8_t state); // switch stepper motor depend on state value (0 -> OFF, 1 -> ON)

void stepper_home(Stepper *stepper, uint8_t step);                 // starts moving stepper motor (can be break by endstop clicked or pause / stop)
void stepper_move(Stepper *stepper, float way, uint8_t direction); // moves stepper motor by given number of steps (can be break by endstop clicked or pause / stop) [way in mm or deg.]

void stepper_run(Stepper *stepper); // runs stepper motor when everything is configured (MOVING or HOMING)

void stepper_process(Stepper *stepper); // manages current stepper movement

#endif // STEPPER_OPERATION_H