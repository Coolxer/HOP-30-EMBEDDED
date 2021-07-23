#ifndef REQUEST_VALIDATOR_H
#define REQUEST_VALIDATOR_H

#include <stdint.h>

uint8_t *request_checkMinLength(uint8_t *request);
uint8_t *request_checkGeneralThings(uint8_t ***args, uint8_t records);

uint8_t *request_validateRequestKeys(uint8_t ***args, uint8_t *index, uint8_t **requiredRequestKeys, uint8_t requiredRequestKeysAmount);

#endif // REQUEST_VALIDATOR_H