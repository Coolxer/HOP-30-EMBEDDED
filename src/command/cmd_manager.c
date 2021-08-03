#include "command/cmd_manager.h"

#include <string.h>

#include "null.h"
#include "data/assistant.h"

#include "communication/connector.h"
#include "command/request/request_manager.h"

uint8_t REQUESTS[MAX_BUFFER_REQUESTS + 1][MAX_SINGLE_REQUEST_SIZE] = {""};

uint8_t registeredRequestsAmount = 0;
uint8_t previousRegisteredRequestIndex = 0;

void cmd_manager_init()
{
    opt_init();
    key_init();
    val_init();
    err_init();
    res_init();
}

void cmd_manager_delive(uint8_t *cmd)
{
    uint8_t *request = (uint8_t *)strtok((void *)cmd, "\n");

    while (request != NULL && request[0] != '|')
    {
        // find next slot index to place request in queue. Check for overfill (this is circular)
        uint8_t registeredRequestIndex = (previousRegisteredRequestIndex < MAX_BUFFER_REQUESTS - 1) ? previousRegisteredRequestIndex + 1 : 1;

        // check if next slot is free. If it is then use it.
        if (!stringLength(REQUESTS[registeredRequestIndex]))
        {
            strcpy((void *)REQUESTS[registeredRequestIndex], (void *)request);
            previousRegisteredRequestIndex = registeredRequestIndex;
            registeredRequestsAmount++;
        }
        else // (if there is not free slot in queue)
            return;
        // QUEUE IS FULL

        request = (uint8_t *)strtok(NULL, "\n");
    }
}

void cmd_manager_manage()
{
    uint8_t i = 0;

    if (!registeredRequestsAmount)
        return;

    for (; i < MAX_BUFFER_REQUESTS; i++)
    {
        if (stringLength(REQUESTS[i]))
        {
            uint8_t *feedback = request_process(REQUESTS[i]);
            connector_sendResponse(feedback);

            strcpy((void *)REQUESTS[i], EMPTY);
            registeredRequestsAmount--;

            break; // break here to start using devices in main loop, not starting all requests at all
        }
    }
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
