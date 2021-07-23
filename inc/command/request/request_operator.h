#ifndef REQUEST_OPERATOR_H
#define REQUEST_OPERATOR_H

#include "command/partial/type.h"

#include "device/high_voltage/hvd.h"
#include "device/low_voltage/stepper/stepper.h"

extern enum RequestType requestType;

extern uint8_t **requiredRequestKeys;
extern uint8_t requiredRequestKeysAmount;

extern uint8_t (*validateRequestFunction)(Stepper *, uint8_t *, uint8_t *);
extern void (*executeRequestFunction)(Stepper *, uint8_t *, uint8_t *);

extern Stepper *stepper;
extern HVD *hvd;

uint8_t *request_operate(uint8_t *index, uint8_t *operation);

#endif // REQUEST_OPERATOR_H