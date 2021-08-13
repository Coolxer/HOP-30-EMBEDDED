#include "command/cmd_manager.h"

#include <string.h>
#include <stdlib.h>

#include "null.h"
#include "data/assistant.h"

#include "communication/connector.h"
#include "command/request/request_manager.h"

uint8_t RESPONSES[MAX_BUFFER_RESPONSES + 1][RESPONSE_SIZE] = {""};
uint8_t awaitingResponsesAmount = 0;

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
    uint8_t generalIndex = 0;
    uint8_t tempIndex = 0;
    uint8_t tempRequest[MAX_SINGLE_REQUEST_SIZE] = {0};

    for (; generalIndex < REQUEST_SIZE; generalIndex++)
    {
        if (cmd[generalIndex] != COMMAND_END_TERMINATOR)
        {
            if (tempIndex == 0 && (cmd[generalIndex] != 'i' && cmd[generalIndex + 1] != 'd' && cmd[generalIndex + 2] != 'x'))
                break;

            else if (tempIndex >= MAX_SINGLE_REQUEST_SIZE)
                break;

            tempRequest[tempIndex] = cmd[generalIndex];
            tempIndex++;
        }
        else // if(cmd[generalIndex] == COMMAND_END_TERMINATOR)
        {
            // find next slot index to place request in queue. Check for overfill (this is circular)
            uint8_t nextIndex = (previousRegisteredRequestIndex < MAX_BUFFER_REQUESTS) ? previousRegisteredRequestIndex + 1 : 1;

            // check if next slot is free. If it is then use it.
            if (REQUESTS[nextIndex][0] == EMPTY_CHARACTER)
            {
                strcpy((void *)REQUESTS[nextIndex], (void *)tempRequest);
                previousRegisteredRequestIndex = nextIndex;
                registeredRequestsAmount++;
            }
            else       // (if there is not free slot in queue)
                break; // QUEUE IS FULL

            // fully clear single temporary REQUEST container
            uint8_t j = 0;
            for (; j <= tempIndex; j++)
                tempRequest[j] = EMPTY_CHARACTER;

            // clear single temporary request index
            tempIndex = 0;
        }
    }
    generalIndex = 0;
}

void cmd_manager_manage()
{
    if (!registeredRequestsAmount)
        return;

    uint8_t i = 1;

    for (; i <= MAX_BUFFER_REQUESTS; i++)
    {
        if (REQUESTS[i][0] == EMPTY_CHARACTER)
            continue;

        uint8_t *feedback = request_process(REQUESTS[i]);

        if (TRANSFER_COMPLETE)
            connector_sendResponse(feedback);
        else
        {
            strcpy((void *)RESPONSES[i], (void *)feedback);
            awaitingResponsesAmount++;
        }

        // fully clear single REQUEST container
        uint8_t j = 0;
        for (; j < MAX_SINGLE_REQUEST_SIZE; j++)
            REQUESTS[i][j] = EMPTY_CHARACTER;

        registeredRequestsAmount--;

        break; // break here to start using devices in main loop, not starting all requests at all
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
