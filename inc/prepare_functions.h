    
#ifndef PREPARE_FUNCTIONS_H
#define PREPARE_FUNCTIONS_H

#include <stdint.h>                                                    // includes uint8_t data type

uint8_t i;
uint8_t* feedback;

uint8_t *prepare_switch(uint8_t ***args, uint8_t size); // passes parameters to stepper_enable function
uint8_t *prepare_set(uint8_t ***args, uint8_t size);  // passes parameters to stepper_set_microstepping function

uint8_t *prepare_home(uint8_t ***args, uint8_t size); // passes parameters to stepper_home function
uint8_t *prepare_move(uint8_t ***args, uint8_t size); // passes parameters to stepper_move function

#endif // PREPARE_FUNCTIONS_H