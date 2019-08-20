    
#ifndef PREPARE_FUNCTIONS_H
#define PREPARE_FUNCTIONS_H

#include <stdint.h> // includes uint8_t data type

#include "stepper.h"

struct Stepper s1, s2, *current;

void prepare_steppers(); //initialize steppers structures

/* prepare functions */

void prepare_turn(uint8_t ***args, uint8_t *size);


#endif // PREPARE_FUNCTIONS_H