#ifndef REQUEST_OPERATOR_H
#define REQUEST_OPERATOR_H

#include "command/request/request.h"

#include "device/high_voltage/hvd.h"
#include "device/low_voltage/stepper/stepper.h"

Request request_operate(uint8_t *operation);

#endif // REQUEST_OPERATOR_H