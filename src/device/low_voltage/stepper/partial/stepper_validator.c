#include "device/low_voltage/stepper/partial/stepper_validator.h"

#include "data/validator.h"
#include "data/assistant.h"

#include "command/partial/err.h"
#include "command/partial/val.h"

#include "device/low_voltage/stepper/partial/stepper_helper.h"

#include "device/low_voltage/endstop/partial/endstop_operation.h"

uint8_t stepper_validateConfigure(Stepper *stepper, uint8_t *speed, uint8_t *acceleration)
{
    if (validate_float(speed) == ERR.ERROR)
        return ERR.INVALID_SPEED_VALUE;
    else if (validate_key(VAL.NONE, acceleration) == ERR.ERROR && validate_float(acceleration) == ERR.ERROR)
        return ERR.INVALID_ACCELERATION_VALUE;
    else if (stepper_getState(stepper) == MOVING || stepper_getState(stepper) == PAUSED)
        return ERR.OPERATION_NOT_ALLOWED;

    return ERR.NO_ERROR;
}

uint8_t stepper_validateSwitch(Stepper *stepper, uint8_t *state)
{
    if (validate_boolean(state) == ERR.ERROR)
        return ERR.INVALID_STATE_VALUE;

    else if (stepper_getState(stepper) == MOVING)
        return ERR.OPERATION_NOT_ALLOWED;

    return ERR.NO_ERROR;
}

uint8_t stepper_validateMove(Stepper *stepper, uint8_t *way, uint8_t *direction)
{
    if (validate_key(VAL.LIMIT, way) == ERR.ERROR && validate_float(way) == ERR.ERROR)
        return ERR.INVALID_WAY_VALUE;

    else if (validate_boolean(direction) == ERR.ERROR)
        return ERR.INVALID_DIRECTION_VALUE;

    else if (!(stepper_getTargetSpeed(stepper) < 0.0f || stepper_getTargetSpeed(stepper) > 0.0f)) // cannot move if speed is not set (0.0f)
        return ERR.OPERATION_NOT_ALLOWED;

    else if (stepper_getState(stepper) == MOVING || stepper_getState(stepper) == PAUSED) // cannot move if motor is homing or moving or is paused right now
        return ERR.OPERATION_NOT_ALLOWED;

    else if (stringEqual(VAL.LIMIT, way) && stepper_getName(stepper) == 'w') // w stepper cannot be hommed
        return ERR.OPERATION_NOT_ALLOWED;

    else if (stepper->minEndstop != NULL && stepper->maxEndstop != NULL)
    {
        uint8_t dir = convertStrToBoolean(direction);

        if ((!dir && endstop_isClicked(stepper->minEndstop)) ||
            (dir && endstop_isClicked(stepper->maxEndstop)))
            return ERR.ENDSTOP_CLICKED;
    }

    return ERR.NO_ERROR;
}

uint8_t stepper_validatePause(Stepper *stepper)
{
    if (stepper_getState(stepper) == MOVING)
        return ERR.NO_ERROR;

    return ERR.OPERATION_NOT_ALLOWED;
}

uint8_t stepper_validateResume(Stepper *stepper)
{
    if (stepper_getState(stepper) == PAUSED)
        return ERR.NO_ERROR;

    return ERR.OPERATION_NOT_ALLOWED;
}

uint8_t stepper_validateStop(Stepper *stepper)
{
    if (stepper_getState(stepper) == MOVING || stepper_getState(stepper) == PAUSED)
        return ERR.NO_ERROR;

    return ERR.OPERATION_NOT_ALLOWED;
}
