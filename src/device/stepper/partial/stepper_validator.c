#include "device/stepper/partial/stepper_validator.h"

#include "validator.h"
#include "command/partial/err.h"
#include "command/partial/val.h"

#include "command/partial/data_assistant.h"
#include "device/stepper/partial/stepper_helper.h"

uint8_t validate_configure(Stepper *stepper, uint8_t *speed, uint8_t *acceleration)
{
    if (validate_float(speed) == ERR.ERROR)
        return ERR.INVALID_SPEED_VALUE;
    else if (validate_key(VAL.NONE, acceleration) == ERR.ERROR && validate_float(acceleration) == ERR.ERROR)
        return ERR.INVALID_ACCELERATION_VALUE;
    else if (stepper_getState(stepper) == MOVING || stepper_getState(stepper) == PAUSED)
        return ERR.OPERATION_NOT_ALLOWED;

    return ERR.NO_ERROR;
}

uint8_t validate_switch(Stepper *stepper, uint8_t *state)
{
    if (validate_boolean(state) == ERR.ERROR)
        return ERR.INVALID_STATE_VALUE;

    else if (stepper_getState(stepper) == MOVING)
        return ERR.OPERATION_NOT_ALLOWED;

    return ERR.NO_ERROR;
}

uint8_t validate_move(Stepper *stepper, uint8_t *way, uint8_t *direction)
{
    if (validate_key(VAL.LIMIT, way) == ERR.ERROR && validate_float(way) == ERR.ERROR)
        return ERR.INVALID_WAY_VALUE;
    else if (validate_boolean(direction) == ERR.ERROR)
        return ERR.INVALID_DIRECTION_VALUE;
    else if (stepper_getState(stepper) == MOVING || stepper_getState(stepper) == PAUSED) // cannot move if motor is homing or moving or is paused right now
        return ERR.OPERATION_NOT_ALLOWED;

    return ERR.NO_ERROR;
}

uint8_t validate_pause(Stepper *stepper)
{
    if (stepper_getState(stepper) == MOVING)
        return ERR.NO_ERROR;

    return ERR.OPERATION_NOT_ALLOWED;
}

uint8_t validate_resume(Stepper *stepper)
{
    if (stepper_getState(stepper) == PAUSED)
        return ERR.NO_ERROR;

    return ERR.OPERATION_NOT_ALLOWED;
}

uint8_t validate_stop(Stepper *stepper)
{
    if (stepper_getState(stepper) == MOVING || stepper_getState(stepper) == PAUSED)
        return ERR.NO_ERROR;

    return ERR.OPERATION_NOT_ALLOWED;
}
