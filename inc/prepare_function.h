
#ifndef PREPARE_FUNCTION_H
#define PREPARE_FUNCTION_H

#include "device_manager.h"

uint8_t *prepare_configuration(uint8_t *idx, uint8_t ***args); // set speed

uint8_t *prepare_switch(uint8_t *idx, uint8_t ***args);
uint8_t *prepare_home(uint8_t *idx, uint8_t ***args);
uint8_t *prepare_move(uint8_t *idx, uint8_t ***args);
uint8_t *prepare_process(uint8_t *idx, uint8_t ***args);

uint8_t *prepare_intervention(uint8_t *idx, uint8_t ***args, uint8_t (*fun)(Stepper *)); // pause, resume, stop

#endif // PREPARE_FUNCTION_H