#include "device/stepper/partial/stepper_validator.h"

#include "validator.h"
#include "command/partial/err.h"
#include "command/partial/data_assistant.h"

#include "device/stepper/partial/stepper_state_manager.h"

uint8_t validate_setSpeed(Stepper *stepper, uint8_t *speed)
{
    if (validate_float(speed) == ERR.ERROR)
        return ERR.INVALID_SPEED_VALUE;

    float _speed = convertStrToFloat(speed);

    if (_speed < stepper->info.minSpeed || _speed > stepper->info.maxSpeed) // checks if speed is in range
        return ERR.INVALID_SPEED_VALUE;

    return ERR.NO_ERROR;
}

uint8_t validate_switch(Stepper *stepper, uint8_t *state)
{
    if (validate_boolean(state) == ERR.ERROR)
        return ERR.INVALID_STATE_VALUE;

    else if (stepper_isState(stepper, HOMING) || stepper_isState(stepper, MOVING)) // cannot switch motor if stepper is homing or moving
        return ERR.OPERATION_NOT_ALLOWED;

    return ERR.NO_ERROR;
}

uint8_t validate_home(Stepper *stepper)
{
    if (stepper_isState(stepper, HOMING) || stepper_isState(stepper, MOVING) || stepper_isState(stepper, PAUSED)) // cannot home if motor is homing or moving right now or also paused
        return ERR.OPERATION_NOT_ALLOWED;

    return ERR.NO_ERROR;
}

uint8_t validate_move(Stepper *stepper, uint8_t *way, uint8_t *direction)
{
    if (validate_float(way) == ERR.ERROR)
        return ERR.INVALID_WAY_VALUE;
    else if (validate_boolean(direction) == ERR.ERROR)
        return ERR.INVALID_DIRECTION_VALUE;
    else if (stepper_isState(stepper, HOMING) || stepper_isState(stepper, MOVING) || stepper_isState(stepper, PAUSED)) // cannot move if motor is homing or moving or is paused right now
        return ERR.OPERATION_NOT_ALLOWED;

    return ERR.NO_ERROR;
}

uint8_t validate_pause(Stepper *stepper)
{
    if ((!stepper_isState(stepper, HOMING) && !stepper_isState(stepper, MOVING)) || stepper_isState(stepper, PAUSED)) // cannot pause if stepper is not homing, not moving or if it is already paused
        return ERR.OPERATION_NOT_ALLOWED;

    return ERR.NO_ERROR;
}

uint8_t validate_resume(Stepper *stepper)
{
    if (!stepper_isState(stepper, PAUSED)) // cannot resume stepper if it's not paused
        return ERR.OPERATION_NOT_ALLOWED;

    return ERR.NO_ERROR;
}

uint8_t validate_stop(Stepper *stepper)
{
    if (!stepper_isState(stepper, HOMING) && !stepper_isState(stepper, MOVING) && !stepper_isState(stepper, PAUSED)) // cannot stop motor if its not homing, moving or not paused
        return ERR.OPERATION_NOT_ALLOWED;

    return ERR.NO_ERROR;
}
