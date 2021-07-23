#include "process/partial/process_validator.h"

#include "process/process.h"
#include "device/device_manager.h"

#include "validator.h"
#include "command/partial/err.h"

#include "device/low_voltage/stepper/partial/stepper_helper.h"

uint8_t process_validateConfigure(uint8_t *direction)
{
    if (validate_boolean(direction) == ERR.ERROR)
        return ERR.INVALID_DIRECTION_VALUE;

    else if (stepper_getState(X_STEPPER) == MOVING || stepper_getState(W_STEPPER) == MOVING)
        return ERR.OPERATION_NOT_ALLOWED;

    return ERR.NO_ERROR;
}

uint8_t process_validatePause()
{
    if (PROCESS_STATE == FORWARD || PROCESS_STATE == BACKWARD)
        return ERR.NO_ERROR;

    return ERR.OPERATION_NOT_ALLOWED;
}

uint8_t process_validateResume()
{
    if (PROCESS_STATE == HALTED)
        return ERR.NO_ERROR;

    return ERR.OPERATION_NOT_ALLOWED;
}

uint8_t process_validateStop()
{
    if (PROCESS_STATE != NONE)
        return ERR.NO_ERROR;

    return ERR.OPERATION_NOT_ALLOWED;
}