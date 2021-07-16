#include "communication/dma/partial/dma_setup.h"

#include "communication/dma/dma.h"

void dma_setupInterface()
{
    dma.commandLine.Instance = DMA1_Stream5;
    dma.commandLine.Init.Channel = DMA_CHANNEL_4;
    dma.commandLine.Init.Direction = DMA_PERIPH_TO_MEMORY;
    dma.commandLine.Init.PeriphInc = DMA_PINC_DISABLE;
    dma.commandLine.Init.MemInc = DMA_MINC_ENABLE;
    dma.commandLine.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    dma.commandLine.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    dma.commandLine.Init.Mode = DMA_NORMAL;
    dma.commandLine.Init.Priority = DMA_PRIORITY_LOW;
    dma.commandLine.Init.FIFOMode = DMA_FIFOMODE_DISABLE;

    HAL_DMA_Init(&dma.commandLine);

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
    dma_setupInterface();
    dma_setupInterrupts();
}

void dma_deinit()
{
    HAL_DMA_DeInit(&dma.commandLine);
    HAL_DMA_DeInit(&dma.responseLine);

    HAL_NVIC_DisableIRQ(USART2_IRQn);
    HAL_NVIC_DisableIRQ(DMA1_Stream5_IRQn);
    HAL_NVIC_DisableIRQ(DMA1_Stream6_IRQn);
}