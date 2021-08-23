#include "communication/dma/partial/dma_callback.h"

#include "data/assistant.h"

#include "communication/uart.h"
#include "communication/dma/dma.h"
#include "communication/dma/partial./dma_validator.h"

#include "command/request/request_manager.h"

#include "command/cmd_manager.h"
#include "communication/connector.h"
#include "command/response/response_builder.h"

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
    UNUSED(huart); // turn off warning: unused parameter...

    if (dma.RECEIVED_COMMAND)
    {
        connector_sendResponse(response_builder_buildErr(ZERO_INDEX, ERR.REQUESTING_TOO_FAST));
        return;
    }

    dma.receivedCommandSize = Size;
    dma.RECEIVED_COMMAND = 1;
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    UNUSED(huart); // turn off warning: unused parameter...

    dma.TRANSFER_COMPLETE = 1;
}

void receivedCommandCallback()
{
    uint8_t code = validateTransmission();

    if (code == CORRECT)
    {
        if (stringEqual(SHUTDOWN_REQUEST, dma.requestBuffer))
        {
            SHUTDOWN_FLAG = 1;
            return;
        }

        cmd_manager_delive(dma.requestBuffer);
    }
    else // if there was as cmd length or begining or end error
        connector_sendResponse(response_builder_buildErr(ZERO_INDEX, code));

    clearString(dma.requestBuffer, MAX_COMMAND_SIZE);

    // start listening to again
    HAL_UARTEx_ReceiveToIdle_DMA(&uart, dma.requestBuffer, MAX_COMMAND_SIZE);
    __HAL_DMA_DISABLE_IT(&dma.requestLine, DMA_IT_HT);

    dma.RECEIVED_COMMAND = 0;
}

void transferCompletedCallback()
{
    // after sending is finish i can safety clear Response
    clearString(RESPONSES[justSendedResponseIndex], MAX_RESPONSE_SIZE);

    dma.READY_FOR_TRANSFER = 1;
}
