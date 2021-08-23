#include "communication/dma/partial/dma_setup.h"

#include "communication/dma/dma.h"

void dma_setupInterface()
{
    dma.requestLine.Instance = DMA1_Stream5;
    dma.requestLine.Init.Channel = DMA_CHANNEL_4;
    dma.requestLine.Init.Direction = DMA_PERIPH_TO_MEMORY;
    dma.requestLine.Init.PeriphInc = DMA_PINC_DISABLE;
    dma.requestLine.Init.MemInc = DMA_MINC_ENABLE;
    dma.requestLine.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    dma.requestLine.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    dma.requestLine.Init.Mode = DMA_NORMAL;
    dma.requestLine.Init.Priority = DMA_PRIORITY_LOW;
    dma.requestLine.Init.FIFOMode = DMA_FIFOMODE_DISABLE;

    HAL_DMA_Init(&dma.requestLine);

    dma.responseLine.Instance = DMA1_Stream6;
    dma.responseLine.Init.Channel = DMA_CHANNEL_4;
    dma.responseLine.Init.Direction = DMA_MEMORY_TO_PERIPH;
    dma.responseLine.Init.PeriphInc = DMA_PINC_DISABLE;
    dma.responseLine.Init.MemInc = DMA_MINC_ENABLE;
    dma.responseLine.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    dma.responseLine.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    dma.responseLine.Init.Mode = DMA_NORMAL;
    dma.responseLine.Init.Priority = DMA_PRIORITY_LOW;
    dma.responseLine.Init.FIFOMode = DMA_FIFOMODE_DISABLE;

    HAL_DMA_Init(&dma.responseLine);
}

void dma_setupInterrupts()
{
    /* USART2 interrupt Init */
    HAL_NVIC_SetPriority(USART2_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(USART2_IRQn);

    /* DMA1_Stream5_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(DMA1_Stream5_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(DMA1_Stream5_IRQn);

    /* DMA1_Stream6_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(DMA1_Stream6_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(DMA1_Stream6_IRQn);
}

void dma_init()
{
    dma_structure_init();
    dma_setupInterface();
    dma_setupInterrupts();
}

void dma_deinit()
{
    HAL_DMA_DeInit(&dma.requestLine);
    HAL_DMA_DeInit(&dma.responseLine);

    HAL_NVIC_DisableIRQ(USART2_IRQn);
    HAL_NVIC_DisableIRQ(DMA1_Stream5_IRQn);
    HAL_NVIC_DisableIRQ(DMA1_Stream6_IRQn);
}