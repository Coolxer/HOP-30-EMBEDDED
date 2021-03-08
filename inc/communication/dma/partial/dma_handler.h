#ifndef DMA_HANDLER_H
#define DMA_HANDLER_H

#include <stdint.h>

uint8_t BUFFER_IS_EMPTY(); // returns TRUE if buffer is empty (depend on FLAG)

/* PRIVATE */ //void dma_uartHandler(); 			  // own implementation of uart interrupt handler
/* PRIVATE */ //void dma_dmaHandler(); 			      // own implementation of dma interrupt handler

/* PRIVATE */ //void USART2_IRQHandler(void); 	  // USART2 irq handler
/* PRIVATE */ //void DMA1_Stream5_IRQHandler(void); // DMA1 RX irq handler

#endif // DMA_HANDLER_H