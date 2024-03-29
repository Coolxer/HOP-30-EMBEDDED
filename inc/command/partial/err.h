#ifndef ERR_H
#define ERR_H

#include <stdint.h>

#define CORRECT 0

enum ErrorType
{
    KEY_ERROR = 0,
    VALUE_ERROR = 1
};

typedef struct
{
    // STRUCTURE ERRORS

    uint8_t
        UNDEFINED,

        COMMAND_TOO_SHORT,
        COMMAND_TOO_LONG,
        COMMAND_INCORRECT_BEGINING,
        COMMAND_INCORRECT_CONTENT,
        COMMAND_INCORRECT_END,

        NO_PARAMS,
        ONE_PARAM_ONLY,
        TO_MANY_PARAMS,

        NO_INDEX_KEY,
        INCORRECT_INDEX_VALUE,

        NO_OPERATION_KEY,
        INCORRECT_OPERATION_VALUE,

        NO_STEPPER_KEY,
        INCORRECT_STEPPER_VALUE,

        NO_ENDSTOP_KEY,
        INCORRECT_ENDSTOP_VALUE,

        NO_SPEED_KEY,
        INCORRECT_SPEED_VALUE,

        NO_ACCELERATION_KEY,
        INCORRECT_ACCELERATION_VALUE,

        NO_STATE_KEY,
        INCORRECT_STATE_VALUE,

        NO_WAY_KEY,
        INCORRECT_WAY_VALUE,

        NO_DIRECTION_KEY,
        INCORRECT_DIRECTION_VALUE,

        NO_COOLANT_KEY,
        INCORRECT_COOLANT_VALUE,

        // ENVIRONMENT STATE ERRORS

        LIMIT_SWITCH_REACHED,

        STEPPER_SPEED_NOT_SET,
        STEPPER_NOT_RUNNING,
        STEPPER_NOT_PAUSED,
        STEPPER_NOT_RUNNING_OR_PAUSED,

        STEPPER_ALREADY_RUNNING,
        STEPPER_ALREADY_PAUSED,

        PROCESS_NOT_CONFIGURED,
        PROCESS_NOT_HALTED,
        PROCESS_NOT_RUNNING,
        PROCESS_ALREADY_RUNNING,

        OPERATION_NOT_ALLOWED,

        // OTHERS
        REQUESTING_TOO_FAST;
} err;

extern err ERR;

void err_init();

#endif // ERR_H