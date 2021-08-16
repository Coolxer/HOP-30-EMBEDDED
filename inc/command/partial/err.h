#ifndef ERR_H
#define ERR_H

#include <stdint.h>

enum ErrorType
{
    KEY_ERROR = 0,
    VALUE_ERROR = 1
};

typedef struct
{
    uint8_t NO_ERROR,
        ERROR,
        NO_PARAMS,
        ONE_PARAM_ONLY,
        TO_MANY_PARAMS,

        NO_INDEX_KEY,
        INVALID_INDEX_VALUE,

        NO_OPERATION_KEY,
        INVALID_OPERATION_VALUE,

        NO_STEPPER_KEY,
        INVALID_STEPPER_VALUE,

        NO_ENDSTOP_KEY,
        INVALID_ENDSTOP_VALUE,

        NO_SPEED_KEY,
        INVALID_SPEED_VALUE,

        NO_ACCELERATION_KEY,
        INVALID_ACCELERATION_VALUE,

        NO_STATE_KEY,
        INVALID_STATE_VALUE,

        NO_WAY_KEY,
        INVALID_WAY_VALUE,

        NO_DIRECTION_KEY,
        INVALID_DIRECTION_VALUE,

        NO_COOLANT_KEY,
        INVALID_COOLANT_VALUE,

        ENDSTOP_CLICKED,

        OPERATION_NOT_ALLOWED;
} err;

extern err ERR;

void err_init();

#endif // ERR_H