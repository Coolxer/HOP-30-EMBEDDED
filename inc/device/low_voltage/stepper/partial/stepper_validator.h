#ifndef STEPPER_VALIDATOR_H
#define STEPPER_VALIDATOR_H

#include "device/low_voltage/stepper/stepper.h"

uint8_t validate_configure(Stepper *stepper, uint8_t *speed, uint8_t *acceleration);
uint8_t validate_switch(Stepper *stepper, uint8_t *state, uint8_t *);
uint8_t validate_move(Stepper *stepper, uint8_t *way, uint8_t *direction);

uint8_t validate_pause(Stepper *stepper, uint8_t *, uint8_t *);
uint8_t validate_resume(Stepper *stepper, uint8_t *, uint8_t *);
uint8_t validate_stop(Stepper *stepper, uint8_t *, uint8_t *);

#endif // STEPPER_VALIDATOR_H