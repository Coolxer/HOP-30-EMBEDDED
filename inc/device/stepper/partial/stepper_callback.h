#ifndef STEPPER_CALLBACK
#define STEPPER_CALLBACK

#include "device/stepper/stepper.h"

uint8_t stepper_homeProcedureOnEndstopClicked();
void stepper_homeProcedureOnStepperFinished();

#endif // STEPPER_CALLBACK
