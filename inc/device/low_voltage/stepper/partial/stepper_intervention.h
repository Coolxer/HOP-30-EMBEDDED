#ifndef STEPPER_SETUP_H
#define STEPPER_SETUP_H

#include "device/low_voltage/stepper/stepper.h"

void stepper_pause(Stepper *stepper);  // pauses stepper and saves timer parameters to easy resume
void stepper_resume(Stepper *stepper); // resumes stepper motor, after it was paused
void stepper_stop(Stepper *stepper);   // stop stepper motor (no saving timer parameters)

#endif // STEPPER_SETUP_H