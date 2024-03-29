#include "communication/connector.h"

#include "data/assistant.h"

#include "communication/dma/partial/dma_setup.h"

void connector_init()
{
    uart_init();
    dma_init();

    __HAL_LINKDMA(&uart, hdmarx, dma.requestLine);
    __HAL_LINKDMA(&uart, hdmatx, dma.responseLine);

    HAL_UARTEx_ReceiveToIdle_DMA(&uart, dma.commandBuffer, MAX_COMMAND_SIZE);
    __HAL_DMA_DISABLE_IT(&dma.requestLine, DMA_IT_HT);
}

void connector_deinit()
{
    uart_deinit();
    dma_deinit();
}

void connector_sendResponse(uint8_t *response)
{
    dma.TRANSFER_COMPLETE = 0;
    dma.READY_FOR_TRANSFER = 0;

    HAL_UART_Transmit_DMA(&uart, (uint8_t *)response, stringLength(response));
}