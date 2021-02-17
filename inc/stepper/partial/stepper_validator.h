#ifndef STEPPER_VALIDATOR_H
#define STEPPER_VALIDATOR_H

#include "stepper/stepper.h"

uint8_t set_speed_validator(Stepper *stepper, uint8_t *speed);

uint8_t switch_validator(Stepper *stepper);
uint8_t home_validator(Stepper *stepper);
uint8_t move_validator(Stepper *stepper, uint8_t *way);

uint8_t pause_validator(Stepper *stepper);
uint8_t resume_validator(Stepper *stepper);
uint8_t stop_validator(Stepper *stepper);

#endif // STEPPER_VALIDATOR_H