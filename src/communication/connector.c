#include "communication/connector.h"

#include "data/assistant.h"

#include "communication/dma/partial/dma_setup.h"

void connector_init()
{
    uart_init();
    dma_init();

    __HAL_LINKDMA(&uart, hdmarx, dma.requestLine);
    __HAL_LINKDMA(&uart, hdmatx, dma.responseLine);

    HAL_UART_Receive_DMA(&uart, dma.requestBuffer, REQUEST_SIZE);
}

void connector_deinit()
{
    uart_deinit();
    dma_deinit();
}

void connector_sendResponse(uint8_t *response)
{
    TRANSFER_COMPLETE = 0;
    HAL_UART_Transmit_DMA(&uart, (uint8_t *)response, RESPONSE_SIZE);
}