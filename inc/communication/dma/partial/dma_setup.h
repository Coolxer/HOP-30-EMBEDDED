#ifndef DMA_SETUP_H
#define DMA_SETUP_H

#include "communication/dma/dma.h"

/* PRIVATE */ //void dma_setupInterface();  // setups interface of DMA
/* PRIVATE */ //void dma_setupInterrupts(); // turns on USART2 interrupt and DMA RX stream channel interrupt

void dma_init(); // calls setups of interface and interruptshandler
void dma_deinit();

#endif // DMA_SETUP_H