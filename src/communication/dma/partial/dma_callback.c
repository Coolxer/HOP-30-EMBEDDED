#include "communication/dma/partial/dma_callback.h"

#include "data/assistant.h"

#include "communication/uart.h"
#include "communication/dma/dma.h"
#include "communication/dma/partial./dma_validator.h"

#include "command/request/request_manager.h"

#include "command/cmd_manager.h"

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    UNUSED(huart); // turn off warning: unused parameter...

    if (validateTransmission())
    {
        if (stringEqual(SHUTDOWN_REQUEST, dma.requestBuffer))
        {
            SHUTDOWN_FLAG = 1;
            return;
        }

        cmd_manager_delive(dma.requestBuffer);
    }
    else
        clearString(dma.requestBuffer, REQUEST_SIZE);

    // start listening to again
    HAL_UART_Receive_DMA(&uart, dma.requestBuffer, REQUEST_SIZE);
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    UNUSED(huart); // turn off warning: unused parameter...

    // after sending is finish i can safety clear Response
    clearString(RESPONSES[justSendedResponseIndex], RESPONSE_SIZE);

    TRANSFER_COMPLETE = 1;
}
