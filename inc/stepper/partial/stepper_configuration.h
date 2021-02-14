#ifndef STEPPER_CONFIGURATION_H
#define STEPPER_CONFIGURATION_H

#include "stepper/stepper.h"

uint8_t stepper_setSpeed(Stepper *stepper, uint8_t *speed); // sets speed of stepper

void stepper_setDirection(Stepper *stepper, uint8_t dir); // setups stepper motor direction
void stepper_changeDirection(Stepper *stepper);           // changes stepper motor

void stepper_stopTimers(Stepper *stepper); // stop timers
void stepper_reset(Stepper *stepper);      // reset timersEndstop *min, Endstop *max); // setups endstops to the axis

#endif // STEPPER_CONFIGURATION_H