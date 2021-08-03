#include "command/request/request.h"

#include <string.h>

Request request_init(enum RequestType type, uint8_t *req1, uint8_t *req2, uint8_t *req3, uint8_t requiredKeysAmount, uint8_t (*validateFunction)(), void (*executeFunction)(), uint8_t numberOfValues, Stepper *stepper, HVD *hvd)
{
    Request request = {0};
    request.type = type;

    request.requiredKeys[0] = req1;
    request.requiredKeys[1] = req2;
    request.requiredKeys[2] = req3;

    request.requiredKeysAmount = requiredKeysAmount;

    request.validateFunction = validateFunction;
    request.executeFunction = executeFunction;

    request.numberOfValues = numberOfValues;

    request.stepper = stepper;
    request.hvd = hvd;

    return request;
}