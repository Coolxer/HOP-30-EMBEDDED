    
#ifndef PREPARE_FUNCTIONS_H
#define PREPARE_FUNCTIONS_H

#include <stdint.h> // includes uint8_t data type

/* prepare functions */
uint8_t *prepare_turn(uint8_t ***args, uint8_t size, uint8_t dt_size); // passing the parameters to stepper_enable function
uint8_t *prepare_set(uint8_t ***args, uint8_t size, uint8_t dt_size); // passing the parameters to stepper_set_microstepping function

uint8_t *prepare_home(uint8_t ***args, uint8_t size, uint8_t dt_size); // passing the parameters to stepper_home function
uint8_t *prepare_move(uint8_t ***args, uint8_t size, uint8_t dt_size); // passing the parameters to stepper_move function

#endif // PREPARE_FUNCTIONS_H