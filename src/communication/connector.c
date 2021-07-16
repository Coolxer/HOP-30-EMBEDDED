#include "communication/connector.h"

#include "communication/dma/partial/dma_setup.h"

void connector_init()
{
    uart_init();
    dma_init();

    __HAL_LINKDMA(&uart, hdmarx, dma.commandLine);
    __HAL_LINKDMA(&uart, hdmatx, dma.responseLine);

    HAL_UART_Receive_DMA(&uart, dma.commandBuffer, COMMAND_SIZE);
}

void connector_deinit()
{
    uart_deinit();
    dma_deinit();
}

void connector_sendMessage(uint8_t *message)
{
    return;
    //if (TRANSFER_IS_COMPLETE())
    //    HAL_UART_Transmit_DMA(&uart, (uint8_t *)message, (uint16_t)stringLength(message));
}