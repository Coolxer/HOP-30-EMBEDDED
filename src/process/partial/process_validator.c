#include "process/partial/process_validator.h"

#include "process/process.h"
#include "device/device_manager.h"

#include "data/validator.h"
#include "command/partial/err.h"

#include "device/low_voltage/stepper/partial/stepper_helper.h"

uint8_t process_validateConfigure(uint8_t *direction, uint8_t *coolant)
{
    if (validate_boolean(direction) == ERR.UNDEFINED)
        return ERR.INCORRECT_DIRECTION_VALUE;

    else if (validate_boolean(coolant) == ERR.UNDEFINED)
        return ERR.INCORRECT_COOLANT_VALUE;

    else if (PROCESS_STATE != NONE)
        return ERR.PROCESS_ALREADY_RUNNING;

    uint8_t i = 0;

    for (; i < STEPPERS_AMOUNT; i++)
    {
        if (stepper_getState(&steppers[i]) == MOVING)
            return ERR.STEPPER_ALREADY_RUNNING;
    }

    return CORRECT;
}

uint8_t process_validateInit()
{
    if (!PROCESS_CONFIGURED)
        return ERR.PROCESS_NOT_CONFIGURED;

    return CORRECT;
}

uint8_t process_validatePause()
{
    if (PROCESS_STATE != FORWARD && PROCESS_STATE != BACKWARD)
        return ERR.PROCESS_NOT_RUNNING;

    return CORRECT;
}

uint8_t process_validateResume()
{
    if (PROCESS_STATE != HALTED)
        return ERR.PROCESS_NOT_HALTED;

    return CORRECT;
}

uint8_t process_validateStop()
{
    if (PROCESS_STATE == NONE)
        return ERR.PROCESS_NOT_RUNNING;

    return CORRECT;
}