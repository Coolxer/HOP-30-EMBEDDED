#include "communication/dma/partial/dma_callback.h"

#include "data/assistant.h"

#include "communication/uart.h"
#include "communication/dma/dma.h"
#include "communication/connector.h"

#include "command/request/request_manager.h"

#include "command/cmd_manager.h"

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    huart = huart; // turn off warning: unused parameter...

    // add terminate string sign
    dma.requestBuffer[REQUEST_SIZE - 1] = '\0';

    cmd_manager_delive(dma.requestBuffer);

    // clear buffer
    dma.requestBuffer[0] = '\0';

    // start listening to again
    HAL_UART_Receive_DMA(&uart, dma.requestBuffer, REQUEST_SIZE);

    return;
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    huart = huart; // turn off warning: unused parameter...

    return;
}