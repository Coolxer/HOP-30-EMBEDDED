#ifndef DMA_OPERATION_H
#define DMA_OPERATION_H

#include "communication/dma/dma.h"

uint8_t dma_isReady();     // checks if DMA is ready to read, 1 - yes, 0 - no
/* PRIVATE */              //uint8_t dma_getChar(); 	   // returns one char from DMA
uint8_t *dma_getCommand(); // returns command from DMA

void dma_processData(uint8_t length); // processes incoming data

#endif // DMA_OPERATION_H