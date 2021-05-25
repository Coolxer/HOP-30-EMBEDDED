#include "command/cmd_helper.h"

#include "command/builder/partial/key.h"
#include "command/builder/partial/val.h"
#include "command/builder/partial/err.h"

uint8_t cmd_getSteppersAmount(uint8_t *value)
{
    if (stringEqual(value, VAL.PROCESS))
        return 2;
    else if (stringEqual(value, VAL.ALL))
        return 4;
    else if (device_manager_getStepper(value))
        return 1;

    return 0;
}

uint8_t cmd_getSteppersAmount(uint8_t *value)
{
    if (stringEqual(value, VAL.ALL))
        return 6;
    else if (device_manager_getEndstop(value))
        return 1;

    return 0;
}

uint8_t cmd_getErrorByKey(uint8_t *key, enum ErrorType et)
{
    if (stringEqual(key, KEY.INDEX))
        return et == KEY_ERROR ? ERR.NO_INDEX_KEY : ERR.INVALID_INDEX_VALUE;

    else if (stringEqual(key, KEY.OPERATION))
        return et == KEY_ERROR ? ERR.NO_OPERATION_KEY : ERR.INVALID_OPERATION_VALUE;

    else if (stringEqual(key, KEY.STEPPER))
        return et == KEY_ERROR ? ERR.NO_STEPPER_KEY : ERR.INVALID_STEPPER_VALUE;

    else if (stringEqual(key, KEY.ENDSTOP))
        return et == KEY_ERROR ? ERR.NO_ENDSTOP_KEY : ERR.INVALID_ENDSTOP_VALUE;

    else if (stringEqual(key, KEY.SPEED))
        return et == KEY_ERROR ? ERR.NO_SPEED_KEY : ERR.INVALID_SPEED_VALUE;

    else if (stringEqual(key, KEY.ACCELERATION))
        return et == KEY_ERROR ? ERR.NO_ACCELERATION_KEY : ERR.INVALID_ACCELERATION_VALUE;

    else if (stringEqual(key, KEY.WAY))
        return et == KEY_ERROR ? ERR.NO_WAY_KEY : ERR.INVALID_WAY_VALUE;

    else if (stringEqual(key, KEY.STATE))
        return et == KEY_ERROR ? ERR.NO_STATE_KEY : ERR.INVALID_STATE_VALUE;

    else if (stringEqual(key, KEY.DIRECTION))
        return et == KEY_ERROR ? ERR.NO_DIRECTION_KEY : ERR.INVALID_DIRECTION_VALUE;
}
