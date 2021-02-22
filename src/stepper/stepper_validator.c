#include "stepper/partial/stepper_validator.h"

#include "validator.h"
#include "command/partial/err.h"

uint8_t setSpeed_validator(uint8_t *speed)
{
    if (validate_float(speed) == ERR.ERROR)
        return ERR.INVALID_SPEED_VALUE;

    return ERR.NO_ERROR;
}

uint8_t switch_validator(Stepper *stepper, uint8_t *state)
{
    if (validate_boolean(state) == ERR.ERROR)
        return ERR.INVALID_STATE_VALUE;
    else if (stepper->state == HOMING || stepper->state == MOVING) // cannot switch motor if stepper is homing or moving
        return ERR.OPERATION_NOT_ALLOWED;

    return ERR.NO_ERROR;
}

uint8_t home_validator(Stepper *stepper, uint8_t *direction)
{
    if (validate_boolean(direction) == ERR.ERROR)
        return ERR.INVALID_DIRECTION_VALUE;
    else if (((stepper->state == HOMING || stepper->state == MOVING) && stepper->homeStep == stepper->lastHomeStep) || stepper->state == PAUSED) // cannot home if motor is homing or moving right now or also paused
        return ERR.OPERATION_NOT_ALLOWED;

    return ERR.NO_ERROR;
}

uint8_t move_validator(Stepper *stepper, uint8_t *way, uint8_t *direction)
{
    if (validate_float(way) == ERR.ERROR)
        return ERR.INVALID_WAY_VALUE;
    else if (validate_boolean(direction) == ERR.ERROR)
        return ERR.INVALID_DIRECTION_VALUE;
    else if (stepper->state == HOMING || stepper->state == MOVING || stepper->state == PAUSED) // cannot move if motor is homing or moving or is paused right now
        return ERR.OPERATION_NOT_ALLOWED;

    return ERR.NO_ERROR;
}

uint8_t pause_validator(Stepper *stepper)
{
    if ((stepper->state != HOMING && stepper->state != MOVING) || stepper->state == PAUSED) // cannot pause if stepper is not homing, not moving or if it is already paused
        return ERR.OPERATION_NOT_ALLOWED;

    return ERR.NO_ERROR;
}

uint8_t resume_validator(Stepper *stepper)
{
    if (stepper->state != PAUSED) // cannot resume stepper if it's not paused
        return ERR.OPERATION_NOT_ALLOWED;

    return ERR.NO_ERROR;
}

uint8_t stop_validator(Stepper *stepper)
{
    if (stepper->state != HOMING && stepper->state != MOVING && stepper->state != PAUSED) // cannot stop motor if its not homing, moving or not paused
        return ERR.OPERATION_NOT_ALLOWED;

    return ERR.NO_ERROR;
}
