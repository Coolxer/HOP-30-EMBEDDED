
#ifndef PREPARE_FUNCTION_H
#define PREPARE_FUNCTION_H

#include "device/device_manager.h"

uint8_t *prepare_configuration(uint8_t *idx, uint8_t ***args); // prepares set up speed function

uint8_t *prepare_switch(uint8_t *idx, uint8_t ***args);  // prepares switch operation
uint8_t *prepare_home(uint8_t *idx, uint8_t ***args);    // prepares home operation
uint8_t *prepare_move(uint8_t *idx, uint8_t ***args);    // prepares move operation
uint8_t *prepare_process(uint8_t *idx, uint8_t ***args); // prepares process

uint8_t *prepare_intervention(uint8_t *idx, uint8_t ***args, void (*intervene)(Stepper *), uint8_t (*validate)(Stepper *)); // pause, resume, stop

#endif // PREPARE_FUNCTION_H