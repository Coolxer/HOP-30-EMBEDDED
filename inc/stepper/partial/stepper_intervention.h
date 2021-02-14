#ifndef STEPPER_SETUP_H
#define STEPPER_SETUP_H

#include "stepper/stepper.h"

uint8_t stepper_pause(Stepper *stepper);              // pauses stepper and saves timer parameters to easy resume
uint8_t stepper_resume(Stepper *stepper);             // resumes stepper motor, after it was paused
uint8_t stepper_stop(Stepper *stepper);               // stop stepper motor (no saving timer parameters)
uint8_t stepper_emergency_shutdown(Stepper *stepper); // function that allow easily to only TURN OFF all steppers, without condition

#endif // STEPPER_SETUP_H