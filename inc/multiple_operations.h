
#ifndef MULTIPLE_OPERATIONS_H
#define MULTIPLE_OPERATIONS_H

#include "device/device_manager.h"

// returns number of steppers affected by the command (0 if error)
uint8_t getCommandSteppersAmount(uint8_t *value); // value is possible stepper value (PRO / ALL / (W, X, Y, Z)) but not sure yet

// validates if the correct key and value was given and returns result,
// if everything is ok then updates steppersCount by pointer and returns null string (no error)
// additionaly if steppersCount == 1, then updates stepperIndex by pointer
// if there was invalid key or value then returns error feedbacks
uint8_t *validateSteppers(uint8_t *idx, uint8_t *key, uint8_t *value, uint8_t *steppersAmount, uint8_t *stepperIndex); // key should be SPP
                                                                                                                       // value should be PRO, ALL, (W, X, Y, Z)
                                                                                                                       // steppersCount and stepperIndex are pointers to modify concrete value

// validates other configuration/operation/intervention conditions
// if steppersCount != 1 then stepperIndex should be 9 (does not matter)
// otherwise if steppersCount is 1 then stepperIndex points to single stepper index
// function is universal because have pointers to validate and process functions
uint8_t *operate(uint8_t *idx, uint8_t *value1, uint8_t *value2, uint8_t steppersAmount, uint8_t stepperIndex,
                 uint8_t (*validate)(Stepper *, uint8_t *, uint8_t *), void (*operate)(Stepper *, uint8_t *, uint8_t *));

#endif // MULTIPLE_OPERATIONS_H