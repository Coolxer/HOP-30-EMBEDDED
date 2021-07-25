#ifndef REQUEST_H
#define REQUEST_H

#define MAX_REQUIRED_KEYS_AMOUNT 3

#include "command/request/structure/type.h"

#include "device/high_voltage/hvd.h"
#include "device/low_voltage/stepper/stepper.h"

typedef struct
{
    enum RequestType type;

    uint8_t *requiredKeys[MAX_REQUIRED_KEYS_AMOUNT];
    uint8_t requiredKeysAmount;

    uint8_t (*validateFunction)();
    void (*executeFunction)();

    uint8_t numberOfValues;

    Stepper *stepper;
    HVD *hvd;
} Request;

Request request_init(enum RequestType type, uint8_t *req1, uint8_t *req2, uint8_t *req3, uint8_t requiredKeysAmount, uint8_t (*validateFunction)(), void (*executeFunction)(), uint8_t numberOfValues, Stepper *stepper, HVD *hvd);

#endif // REQUEST_H