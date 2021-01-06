
#ifndef PREPARE_FUNCTIONS_H
#define PREPARE_FUNCTIONS_H

#include <stdint.h>

#include "device_manager.h"

uint8_t *prepare_settings(uint8_t *idx, uint8_t ***args); // set speed
uint8_t *prepare_getEndstopState(uint8_t *idx, uint8_t ***args);

uint8_t *prepare_switch(uint8_t *idx, uint8_t ***args);
uint8_t *prepare_home(uint8_t *idx, uint8_t ***args);
uint8_t *prepare_move(uint8_t *idx, uint8_t ***args);
uint8_t *prepare_process(uint8_t *idx, uint8_t ***args);

uint8_t *prepare_intervention(uint8_t *idx, uint8_t ***args, uint8_t (*fun)(Stepper *)); // pause, resume, stop

#endif // PREPARE_FUNCTIONS_H