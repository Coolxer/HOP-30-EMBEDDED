#ifndef STEPPER_VALIDATOR_H
#define STEPPER_VALIDATOR_H

#include "device/low_voltage/stepper/stepper.h"

uint8_t stepper_validateConfigure(Stepper *stepper, uint8_t *speed, uint8_t *acceleration);
uint8_t stepper_validateSwitch(Stepper *stepper, uint8_t *state);
uint8_t stepper_validateMove(Stepper *stepper, uint8_t *way, uint8_t *direction);

uint8_t stepper_validatePause(Stepper *stepper);
uint8_t stepper_validateResume(Stepper *stepper);
uint8_t stepper_validateStop(Stepper *stepper);

#endif // STEPPER_VALIDATOR_H