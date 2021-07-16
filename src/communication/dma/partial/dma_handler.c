#include "communication/dma/partial/dma_handler.h"

#include "communication/uart.h"
#include "communication/dma/dma.h"

void USART2_IRQHandler(void)
{
    HAL_UART_IRQHandler(&uart);
}

void DMA1_Stream5_IRQHandler(void)
{
    HAL_DMA_IRQHandler(&dma.commandLine);
}

void DMA1_Stream6_IRQHandler(void)
{
    HAL_DMA_IRQHandler(&dma.responseLine);
}