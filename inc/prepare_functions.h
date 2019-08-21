    
#ifndef PREPARE_FUNCTIONS_H
#define PREPARE_FUNCTIONS_H

#include <stdint.h> // includes uint8_t data type

#include "device_manager.h"

/* prepare functions */

void prepare_turn(uint8_t ***args, uint8_t *size); // passing the parameters to stepper_enable function

#endif // PREPARE_FUNCTIONS_H