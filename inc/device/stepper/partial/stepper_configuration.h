#ifndef STEPPER_CONFIGURATION_H
#define STEPPER_CONFIGURATION_H

#include "device/stepper/stepper.h"

void stepper_configure(Stepper *stepper, float speed, float acceleration); // sets speed [in mm/s or obr/min.] and acceleration [in mm/s^2 or obr/s^2.]

void stepper_updateSpeed(Stepper *stepper, float speed); // sets speed of stepper [speed in mm/s or obr/min.]
void stepper_accelerate(Stepper *stepper);               // accelerates stepper

void stepper_setDirection(Stepper *stepper, uint8_t directon); // setups stepper motor direction

void stepper_changeDirectionImmediately(Stepper *stepper); //changes direction with not required delay (helpful in process to synchronize)
void stepper_changeDirection(Stepper *stepper);            // changes direction with required 5us delay

#endif // STEPPER_CONFIGURATION_H