#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <stdint.h>
#include <string.h>

uint8_t validate_boolean(uint8_t *value); // validates boolean variable, returns error code, 0 if no error
uint8_t validate_float(uint8_t *value);   // validates float variable, returns error code, 0 if no error

uint8_t validate_key(uint8_t *expected, uint8_t *current); // validate key, returns error code, 0 if no error

#endif // VALIDATOR_H