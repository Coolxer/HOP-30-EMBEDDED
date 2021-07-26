#include "communication/dma/partial/dma_callback.h"

#include "data_assistant.h"

#include "communication/uart.h"
#include "communication/dma/dma.h"
#include "communication/connector.h"

#include "command/request/request_manager.h"

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    huart = huart; // turn of warning

    // add terminate string sign
    dma.requestBuffer[REQUEST_SIZE - 1] = '\0';

    uint8_t *response = request_process(dma.requestBuffer);
    connector_sendResponse(response);

    // clear buffer
    dma.requestBuffer[0] = '\0';

    // start listening to again
    HAL_UART_Receive_DMA(&uart, dma.requestBuffer, REQUEST_SIZE);

    return;
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    huart = huart; // turn of warning

    return;
}