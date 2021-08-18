#include "device/low_voltage/stepper/partial/stepper_validator.h"

#include "data/validator.h"
#include "data/assistant.h"

#include "command/partial/err.h"
#include "command/partial/val.h"

#include "device/low_voltage/stepper/partial/stepper_helper.h"

#include "device/low_voltage/endstop/partial/endstop_operation.h"

uint8_t stepper_validateConfigure(Stepper *stepper, uint8_t *speed, uint8_t *acceleration)
{
    if (validate_float(speed) == ERR.UNDEFINED)
        return ERR.INCORRECT_SPEED_VALUE;
    else if (validate_key(VAL.NONE, acceleration) == ERR.UNDEFINED && validate_float(acceleration) == ERR.UNDEFINED)
        return ERR.INCORRECT_ACCELERATION_VALUE;
    else if (stepper_getState(stepper) == MOVING)
        return ERR.STEPPER_ALREADY_RUNNING;
    else if (stepper_getState(stepper) == PAUSED)
        return ERR.STEPPER_ALREADY_PAUSED;

    return CORRECT;
}

uint8_t stepper_validateSwitch(Stepper *stepper, uint8_t *state)
{
    if (validate_boolean(state) == ERR.UNDEFINED)
        return ERR.INCORRECT_STATE_VALUE;

    else if (stepper_getState(stepper) == MOVING)
        return ERR.STEPPER_ALREADY_RUNNING;

    return CORRECT;
}

uint8_t stepper_validateMove(Stepper *stepper, uint8_t *way, uint8_t *direction)
{
    if (validate_key(VAL.LIMIT, way) == ERR.UNDEFINED && validate_float(way) == ERR.UNDEFINED)
        return ERR.INCORRECT_WAY_VALUE;

    else if (validate_boolean(direction) == ERR.UNDEFINED)
        return ERR.INCORRECT_DIRECTION_VALUE;

    else if (!(stepper_getTargetSpeed(stepper) < 0.0f || stepper_getTargetSpeed(stepper) > 0.0f)) // cannot move if speed is not set (0.0f)
        return ERR.STEPPER_SPEED_NOT_SET;

    else if (stepper_getState(stepper) == MOVING) // cannot move if motor is homing or moving or is paused right now
        return ERR.STEPPER_ALREADY_RUNNING;

    else if (stepper_getState(stepper) == PAUSED)
        return ERR.STEPPER_ALREADY_PAUSED;

    else if (stepper->minEndstop && stepper->maxEndstop)
    {
        uint8_t dir = convertStrToBoolean(direction);

        if ((!dir && endstop_isClicked(stepper->minEndstop)) ||
            (dir && endstop_isClicked(stepper->maxEndstop)))
            return ERR.LIMIT_SWITCH_REACHED;
    }

    return CORRECT;
}

uint8_t stepper_validatePause(Stepper *stepper)
{
    if (stepper_getState(stepper) != MOVING)
        return ERR.STEPPER_NOT_RUNNING;

    return CORRECT;
}

uint8_t stepper_validateResume(Stepper *stepper)
{
    if (stepper_getState(stepper) != PAUSED)
        return ERR.STEPPER_NOT_PAUSED;

    return CORRECT;
}

uint8_t stepper_validateStop(Stepper *stepper)
{
    if (stepper_getState(stepper) != MOVING && stepper_getState(stepper) != PAUSED)
        return ERR.STEPPER_NOT_RUNNING_OR_PAUSED;

    return CORRECT;
}
