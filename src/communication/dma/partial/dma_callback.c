#include "communication/dma/partial/dma_callback.h"

#include <string.h>

#include "null.h"
#include "data/assistant.h"

#include "communication/uart.h"
#include "communication/dma/dma.h"
#include "communication/connector.h"

#include "command/request/request_manager.h"

#include "command/cmd_manager.h"

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    huart = huart; // turn off warning: unused parameter...

    cmd_manager_delive(dma.requestBuffer);

    // start listening to again
    HAL_UART_Receive_DMA(&uart, dma.requestBuffer, REQUEST_SIZE);
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    huart = huart; // turn off warning: unused parameter...

    TRANSFER_COMPLETE = 1;

    if (!awaitingResponsesAmount)
        return;

    uint8_t i = 1;

    uint8_t res[RESPONSE_SIZE] = {0};

    for (; i < MAX_BUFFER_RESPONSES; i++)
    {
        if (RESPONSES[i][0] == EMPTY_CHARACTER)
            continue;

        strcpy(res, RESPONSES[i]);

        // fully clear single REQUEST container
        uint8_t j = 0;
        for (; j < RESPONSE_SIZE; j++)
            RESPONSES[i][j] = EMPTY_CHARACTER;

        awaitingResponsesAmount--;

        break;
    }

    connector_sendResponse(res);
}