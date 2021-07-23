#ifndef PROCESS_VALIDATOR_H
#define PROCESS_VALIDATOR_H

#include <stdint.h>

uint8_t process_validateConfigure(uint8_t *direction);

uint8_t process_validatePause();
uint8_t process_validateResume();
uint8_t process_validateStop();

#endif // PROCESS_VALIDATOR_H