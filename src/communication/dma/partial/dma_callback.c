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
    uint8_t code = validateTransmission(Size);

    if (code == CORRECT)
    {
        if (stringEqual(SHUTDOWN_REQUEST, dma.requestBuffer))
        {
            SHUTDOWN_FLAG = 1;
            return;
        }

        cmd_manager_delive(dma.requestBuffer, Size);
    }
    else // if there was as cmd length or begining or end error
        connector_sendResponse(response_builder_buildErr(ZERO_INDEX, code));

    clearString(dma.requestBuffer, MAX_COMMAND_SIZE);

    // start listening to again
    HAL_UARTEx_ReceiveToIdle_DMA(huart, dma.requestBuffer, MAX_COMMAND_SIZE);
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    UNUSED(huart); // turn off warning: unused parameter...

    // after sending is finish i can safety clear Response
    clearString(RESPONSES[justSendedResponseIndex], MAX_RESPONSE_SIZE);

    TRANSFER_COMPLETE = 1;
}
