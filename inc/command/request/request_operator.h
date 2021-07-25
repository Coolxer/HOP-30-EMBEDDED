#ifndef REQUEST_OPERATOR_H
#define REQUEST_OPERATOR_H

#define MAX_REQUIRED_KEYS_AMOUNT 3

#include "command/partial/type.h"

#include "device/high_voltage/hvd.h"
#include "device/low_voltage/stepper/stepper.h"

extern enum RequestType requestType;

extern uint8_t *requiredKeys[MAX_REQUIRED_KEYS_AMOUNT];
extern uint8_t requiredKeysAmount;

extern uint8_t (*validateRequestFunction)();
extern void (*executeRequestFunction)();

extern uint8_t numberOfValuesToValidate;

extern Stepper *stepper;
extern HVD *hvd;

uint8_t *request_operate(uint8_t *index, uint8_t *operation);

#endif // REQUEST_OPERATOR_H