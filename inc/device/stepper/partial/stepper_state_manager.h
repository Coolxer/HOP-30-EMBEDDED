#ifndef STEPPER_STATE_MANAGER_H
#define STEPPER_STATE_MANAGER_H

#include "device/stepper/stepper.h"

uint8_t stepper_getLastState(Stepper *stepper);             // returns last stepper state
uint8_t stepper_isState(Stepper *stepper, uint8_t state);   // checks if stepper is in given state, returns true if it is
void stepper_setState(Stepper *stepper, uint8_t state);     // updates stepper state
void stepper_updateStates(Stepper *stepper, uint8_t state); // updates state and lastState
void stepper_updateLastState(Stepper *stepper);             // updates last state

void stepper_setHomeStep(Stepper *stepper, uint8_t step);   // updates stepper state
uint8_t stepper_isHomeStep(Stepper *stepper, uint8_t step); // checks if stepper is in given home step, returns tru if it is

#endif // STEPPER_STATE_MANAGER_H
