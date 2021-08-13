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

    // after sending is finish i can safety clear Response
    clearString(RESPONSES[justSendedResponseIndex], RESPONSE_SIZE);

    TRANSFER_COMPLETE = 1;
}