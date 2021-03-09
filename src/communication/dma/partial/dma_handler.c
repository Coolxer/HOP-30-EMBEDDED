#include "communication/dma/partial/dma_handler.h"

#include "communication/dma/dma.h"
#include "communication/dma/partial/dma_interrupt.h"
#include "communication/dma/partial/dma_operation.h"

volatile uint8_t BUFFER_EMPTY = SET;

typedef struct
{
    __IO uint32_t ISR; // DMA interrupt status register
    __IO uint32_t Reserved0;
    __IO uint32_t IFCR; // DMA interrupt flag clear register
} Dma_registers;

uint8_t BUFFER_IS_NOT_EMPTY()
{
    if (!BUFFER_EMPTY)
    {
        BUFFER_EMPTY = SET;
        return 1;
    }

    return 0;
}

void dma_uartHandler()
{
    if (dma.uart->Instance->SR & UART_FLAG_IDLE) // check if idle flag is set
    {
        volatile uint32_t tmp;
        tmp = dma.uart->Instance->SR;                   // Read status register
        tmp = dma.uart->Instance->DR;                   // Read data register
        dma.uart->hdmarx->Instance->CR &= ~DMA_SxCR_EN; // Disable DMA -> force Transfer Complete interrupt

        UNUSED(tmp); // For unused warning
    }
}

void dma_dmaHandler()
{
    DMA_HandleTypeDef *hdma = dma.uart->hdmarx;
    Dma_registers *regs = (Dma_registers *)hdma->StreamBaseAddress; // get base address of registers

    if (__HAL_DMA_GET_IT_SOURCE(hdma, DMA_IT_TC) != RESET)
    {
        regs->IFCR = DMA_FLAG_TCIF0_4 << hdma->StreamIndex; // Clear Transfer Complete flag
        BUFFER_EMPTY = RESET;                               // set empty flag to 0 means that dma is not empty

        dma_processData((uint8_t)(DMA_BUFFER_SIZE - hdma->Instance->NDTR));

        regs->IFCR = 0x3FU << hdma->StreamIndex;         // clear all interrupts that are in common with transport
        hdma->Instance->M0AR = (uint32_t)dma.dma_buffer; // set address for dma buffer again
        hdma->Instance->NDTR = DMA_BUFFER_SIZE;          // set length of response
        hdma->Instance->CR |= DMA_SxCR_EN;               // start DMA transfer
    }
}

void USART2_IRQHandler(void)
{
    dma_uartHandler();

    uint32_t isrflags = READ_REG(dma.uart->Instance->SR);
    uint32_t cr1its = READ_REG(dma.uart->Instance->CR1);

    /* UART in mode Transmitter ------------------------------------------------*/
    if (((isrflags & USART_SR_TXE) != RESET) && ((cr1its & USART_CR1_TXEIE) != RESET))
    {
        dma_transmit_interrupt(dma.uart);
        return;
    }

    /* UART in mode Transmitter end --------------------------------------------*/
    if (((isrflags & USART_SR_TC) != RESET) && ((cr1its & USART_CR1_TCIE) != RESET))
    {
        dma_end_transmit_interrupt(dma.uart);
        return;
    }
}

void DMA1_Stream5_IRQHandler(void)
{
    dma_dmaHandler();
}

void DMA1_Stream6_IRQHandler(void)
{
    HAL_DMA_IRQHandler(&hdma_usart2_tx);
    /*
    huart->gState = HAL_UART_STATE_READY;
	hdma_usart2_tx.State = HAL_DMA_STATE_READY;
	__HAL_DMA_CLEAR_FLAG(&hdma_usart2_tx, DMA_FLAG_TCIF2_6);
	__HAL_DMA_CLEAR_FLAG(&hdma_usart2_tx, DMA_FLAG_HTIF2_6);
	__HAL_DMA_CLEAR_FLAG(&hdma_usart2_tx, DMA_FLAG_FEIF2_6);
	__HAL_UNLOCK(&hdma_usart2_tx);
	*/
}