#ifndef REQUEST_VALIDATOR_H
#define REQUEST_VALIDATOR_H

#include <stdint.h>

uint8_t request_checkGeneralThings(uint8_t ***args, uint8_t records);
uint8_t request_validateRequestKeys(uint8_t ***args, uint8_t *requiredKeys[], uint8_t requiredKeysAmount);

#endif // REQUEST_VALIDATOR_H