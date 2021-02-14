#ifndef DMA_SETUP_H
#define DMA_SETUP_H

#include "communication/dma/dma.h"

void dma_setup(UART_HandleTypeDef *uart); // inits structure, enables interrupts

/* PRIVATE */ //void dma_setupInterface();  // setups interface of DMA
/* PRIVATE */ //void dma_setupInterrupts(); // turns on USART2 interrupt and DMA RX stream channel interrupt

void dma_init(); // calls setups of interface and interruptsdler

#endif // DMA_SETUP_H