#include "command/cmd_manager.h"

#include "data_assistant.h"

void cmd_manager_init()
{
    opt_init();
    key_init();
    val_init();
    err_init();
    res_init();
}

uint8_t cmd_manager_getErrorByKey(uint8_t *key, enum ErrorType errorType)
{
    if (stringEqual(key, KEY.INDEX))
        return errorType == KEY_ERROR ? ERR.NO_INDEX_KEY : ERR.INVALID_INDEX_VALUE;

    else if (stringEqual(key, KEY.OPERATION))
        return errorType == KEY_ERROR ? ERR.NO_OPERATION_KEY : ERR.INVALID_OPERATION_VALUE;

    else if (stringEqual(key, KEY.STEPPER))
        return errorType == KEY_ERROR ? ERR.NO_STEPPER_KEY : ERR.INVALID_STEPPER_VALUE;

    else if (stringEqual(key, KEY.ENDSTOP))
        return errorType == KEY_ERROR ? ERR.NO_ENDSTOP_KEY : ERR.INVALID_ENDSTOP_VALUE;

    else if (stringEqual(key, KEY.SPEED))
        return errorType == KEY_ERROR ? ERR.NO_SPEED_KEY : ERR.INVALID_SPEED_VALUE;

    else if (stringEqual(key, KEY.ACCELERATION))
        return errorType == KEY_ERROR ? ERR.NO_ACCELERATION_KEY : ERR.INVALID_ACCELERATION_VALUE;

    else if (stringEqual(key, KEY.WAY))
        return errorType == KEY_ERROR ? ERR.NO_WAY_KEY : ERR.INVALID_WAY_VALUE;

    else if (stringEqual(key, KEY.STATE))
        return errorType == KEY_ERROR ? ERR.NO_STATE_KEY : ERR.INVALID_STATE_VALUE;

    else if (stringEqual(key, KEY.DIRECTION))
        return errorType == KEY_ERROR ? ERR.NO_DIRECTION_KEY : ERR.INVALID_DIRECTION_VALUE;

    return ERR.NO_ERROR;
}
