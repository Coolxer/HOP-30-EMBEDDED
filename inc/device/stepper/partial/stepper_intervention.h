#ifndef STEPPER_SETUP_H
#define STEPPER_SETUP_H

#include "device/stepper/stepper.h"

void stepper_pause(Stepper *stepper, uint8_t *, uint8_t *);  // pauses stepper and saves timer parameters to easy resume
void stepper_resume(Stepper *stepper, uint8_t *, uint8_t *); // resumes stepper motor, after it was paused
void stepper_stop(Stepper *stepper, uint8_t *, uint8_t *);   // stop stepper motor (no saving timer parameters)

#endif // STEPPER_SETUP_H