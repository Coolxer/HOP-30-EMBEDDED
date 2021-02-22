#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <stdint.h> // includes uint8_t data type"
#include <string.h>

uint8_t validate_boolean(uint8_t *value);
uint8_t validate_float(uint8_t *value);

#endif // VALIDATOR_H