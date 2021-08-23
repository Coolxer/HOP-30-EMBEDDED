#include "command/cmd_manager.h"

#include <string.h>
#include <stdlib.h>

#include "null.h"
#include "data/assistant.h"

#include "communication/connector.h"
#include "command/request/request_manager.h"
#include "command/response/response_builder.h"

#include "communication/dma/partial/dma_callback.h"

// REQUESTS
uint8_t REQUESTS[MAX_BUFFER_REQUESTS + 1][MAX_REQUEST_SIZE] = {0};
uint8_t registeredRequestsAmount = 0;
uint8_t justRegisteredRequestIndex = 0;
uint8_t justProcessedRequestIndex = 0;

// RESPONSES
uint8_t RESPONSES[MAX_BUFFER_RESPONSES + 1][MAX_RESPONSE_SIZE] = {0};
uint8_t awaitingResponsesAmount = 0;
uint8_t justRegisteredCallbackResponseIndex = MAX_BUFFER_REQUESTS + 1; // starts fo 11 (using only for callback)
uint8_t justSendedResponseIndex = 0;

volatile uint8_t SHUTDOWN_FLAG = 0;

void cmd_manager_init()
{
    opt_init();
    key_init();
    val_init();
    err_init();
    res_init();

    uint8_t i = 0;

    for (i = 0; i < MAX_BUFFER_REQUESTS; i++)
        clearString(REQUESTS[i], MAX_REQUEST_SIZE);

    for (i = 0; i < MAX_BUFFER_RESPONSES; i++)
        clearString(RESPONSES[i], MAX_RESPONSE_SIZE);
}

void cmd_manager_delive(uint8_t *cmd)
{
    uint16_t index = 1; //  starts with 1 to discard  COMMAND_BEGIN_TERMINATOR
    uint8_t tempIndex = 0;
    uint8_t tempRequest[MAX_REQUEST_SIZE] = {0};

    // size -1 to discard COMMAND_END_TERMINATOR
    for (; index < dma.receivedCommandSize - 1; index++)
    {
        if (cmd[index] != SENTENCE_END_TERMINATOR)
        {
            if ((tempIndex == 0 && cmd[index] != 'i') || tempIndex >= MAX_REQUEST_SIZE)
                break;

            tempRequest[tempIndex] = cmd[index];
            tempIndex++;
        }
        else // if(cmd[index] == SENTENCE_END_TERMINATOR)
        {
            // find next slot index to place request in queue. Check for overfill (this is circular)
            uint8_t requestIndex = (justRegisteredRequestIndex < MAX_BUFFER_REQUESTS) ? justRegisteredRequestIndex + 1 : 1;

            // check if next slot is free. If it is then use it.
            if (REQUESTS[requestIndex][0] == EMPTY_CHARACTER)
            {
                strcpy((void *)REQUESTS[requestIndex], (void *)tempRequest);
                justRegisteredRequestIndex = requestIndex;
                registeredRequestsAmount++;
            }
            else       // (if there is not free slot in queue)
                break; // QUEUE IS FULL

            // clear temporary request container
            clearString(tempRequest, tempIndex);

            // clear single temporary request index
            tempIndex = 0;
        }
    }

    if (!registeredRequestsAmount)
        connector_sendResponse(response_builder_buildErr(ZERO_INDEX, ERR.COMMAND_INCORRECT_CONTENT));
}

void cmd_manager_manage_requests()
{
    uint8_t i = justProcessedRequestIndex;

    while (registeredRequestsAmount)
    {
        i = (i < MAX_BUFFER_REQUESTS) ? i + 1 : 1;

        if (REQUESTS[i][0] == EMPTY_CHARACTER)
            continue;

        uint8_t *feedback = request_process(REQUESTS[i]);

        // clear Request
        clearString(REQUESTS[i], MAX_REQUEST_SIZE);
        registeredRequestsAmount--;

        // save Response
        strcpy((void *)RESPONSES[i], (void *)feedback);
        awaitingResponsesAmount++;

        justProcessedRequestIndex = i;

        break; // break here to start using devices in main loop, not starting all requests at all
    }
}

void cmd_manager_manage_responses()
{
    uint8_t i = justSendedResponseIndex;

    while (awaitingResponsesAmount)
    {
        i = (i < MAX_BUFFER_RESPONSES) ? i + 1 : 1;

        if (RESPONSES[i][0] == EMPTY_CHARACTER)
            continue;

        if (!dma.READY_FOR_TRANSFER)
            break;

        justSendedResponseIndex = i;
        awaitingResponsesAmount--;

        connector_sendResponse(RESPONSES[justSendedResponseIndex]);

        break; // break here to start using devices in main loop, not blocking too much time
    }
}

void cmd_manager_process()
{
    if (dma.RECEIVED_COMMAND)
        receivedCommandCallback();
    cmd_manager_manage_requests();

    cmd_manager_manage_responses();
    if (dma.TRANSFER_COMPLETE && !dma.READY_FOR_TRANSFER)
        transferCompletedCallback();
}

uint8_t cmd_manager_getStructureErrorByKey(uint8_t *key, enum ErrorType errorType)
{
    if (stringEqual(key, KEY.INDEX))
        return errorType == KEY_ERROR ? ERR.NO_INDEX_KEY : ERR.INCORRECT_INDEX_VALUE;

    else if (stringEqual(key, KEY.OPERATION))
        return errorType == KEY_ERROR ? ERR.NO_OPERATION_KEY : ERR.INCORRECT_OPERATION_VALUE;

    else if (stringEqual(key, KEY.STEPPER))
        return errorType == KEY_ERROR ? ERR.NO_STEPPER_KEY : ERR.INCORRECT_STEPPER_VALUE;

    else if (stringEqual(key, KEY.ENDSTOP))
        return errorType == KEY_ERROR ? ERR.NO_ENDSTOP_KEY : ERR.INCORRECT_ENDSTOP_VALUE;

    else if (stringEqual(key, KEY.SPEED))
        return errorType == KEY_ERROR ? ERR.NO_SPEED_KEY : ERR.INCORRECT_SPEED_VALUE;

    else if (stringEqual(key, KEY.ACCELERATION))
        return errorType == KEY_ERROR ? ERR.NO_ACCELERATION_KEY : ERR.INCORRECT_ACCELERATION_VALUE;

    else if (stringEqual(key, KEY.WAY))
        return errorType == KEY_ERROR ? ERR.NO_WAY_KEY : ERR.INCORRECT_WAY_VALUE;

    else if (stringEqual(key, KEY.STATE))
        return errorType == KEY_ERROR ? ERR.NO_STATE_KEY : ERR.INCORRECT_STATE_VALUE;

    else if (stringEqual(key, KEY.DIRECTION))
        return errorType == KEY_ERROR ? ERR.NO_DIRECTION_KEY : ERR.INCORRECT_DIRECTION_VALUE;

    else if (stringEqual(key, KEY.COOLANT))
        return errorType == KEY_ERROR ? ERR.NO_COOLANT_KEY : ERR.INCORRECT_COOLANT_VALUE;

    return CORRECT;
}
