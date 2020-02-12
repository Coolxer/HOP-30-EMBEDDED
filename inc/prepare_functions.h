    
#ifndef PREPARE_FUNCTIONS_H
#define PREPARE_FUNCTIONS_H

#include <stdint.h>                                     // includes uint8_t data type

#include "device_manager.h"

uint8_t *prepare_settings(uint8_t ***args, uint8_t size, uint8_t *key, uint8_t (*fun)(Stepper*, uint8_t*)); // speed, microstepping

uint8_t *prepare_switch(uint8_t ***args, uint8_t size);
uint8_t *prepare_home(uint8_t ***args, uint8_t size);   // passes parameters to stepper_home function
uint8_t *prepare_move(uint8_t ***args, uint8_t size);   // passes parameters to stepper_move function

uint8_t *prepare_process(uint8_t ***args, uint8_t size);

uint8_t *prepare_intervention(uint8_t ***args, uint8_t size, uint8_t (*fun)(Stepper*)); // pause, resume, stop

#endif // PREPARE_FUNCTIONS_H