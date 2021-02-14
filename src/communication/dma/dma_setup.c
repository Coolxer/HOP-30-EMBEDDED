#include "communication/dma/partial/dma_setup.h"

void dma_setup(UART_HandleTypeDef *uart)
{
    dma.uart = uart;

    __HAL_UART_ENABLE_IT(dma.uart, UART_IT_IDLE);     // enable UART IDLE interrupt
    __HAL_DMA_ENABLE_IT(dma.uart->hdmarx, DMA_IT_TC); // enable DMA TC (transfer complete) interrupt

    HAL_UART_Receive_DMA(dma.uart, dma.dma_buffer, DMA_BUFFER_SIZE); // start listening by DMA and to DMA buffer

    dma.uart->hdmarx->Instance->CR &= ~DMA_SxCR_HTIE; // for sure, disable HC (half-transfer complete) interrupt

    dma.head = dma.tail = 0; // reset head and tail (means the positions in buffer)
    dma.commands_count = 0;  // reset number of commands ready to process

    dma.empty = 1; // set the state of dma (if data come this will be set to 0)

    huart = uart; // set pointer to uart (using by DMA1_Stream6 -> for TX transfer with DMA)

    tcReady = 1;
}

void dma_setupInterface()
{
    hdma_usart2_rx.Instance = DMA1_Stream5;
    hdma_usart2_rx.Init.Channel = DMA_CHANNEL_4;
    hdma_usart2_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_usart2_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart2_rx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart2_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart2_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart2_rx.Init.Mode = DMA_CIRCULAR;
    hdma_usart2_rx.Init.Priority = DMA_PRIORITY_LOW;
    hdma_usart2_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;

    HAL_DMA_Init(&hdma_usart2_rx);

    hdma_usart2_tx.Instance = DMA1_Stream6;
    hdma_usart2_tx.Init.Channel = DMA_CHANNEL_4;
    hdma_usart2_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_usart2_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart2_tx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart2_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart2_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart2_tx.Init.Mode = DMA_NORMAL;
    hdma_usart2_tx.Init.Priority = DMA_PRIORITY_LOW;
    hdma_usart2_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;

    HAL_DMA_Init(&hdma_usart2_tx);
}

void dma_setupInterrupts()
{
    /* USART2 interrupt Init */
    HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART2_IRQn);

    /* DMA1_Stream5_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(DMA1_Stream5_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(DMA1_Stream5_IRQn);

    HAL_NVIC_SetPriority(DMA1_Stream6_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(DMA1_Stream6_IRQn);
}

void dma_init()
{
    dma_setupInterface();
    dma_setupInterrupts();
}