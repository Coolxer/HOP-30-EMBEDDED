#ifndef DMA_H
#define DMA_H

#include "stm32f4xx_hal.h"

#include "communication/config/communication.h"

typedef struct
{
	uint8_t requestBuffer[MAX_COMMAND_SIZE];

	DMA_HandleTypeDef requestLine;
	DMA_HandleTypeDef responseLine;

	uint16_t receivedCommandSize;

	volatile uint8_t RECEIVED_COMMAND;
	volatile uint8_t TRANSFER_COMPLETE;	 // flag signs after transfer is complete, but response is not cleared
	volatile uint8_t READY_FOR_TRANSFER; // flag signs after transfer is complete, response is cleared, and its ready for next transfer
} DMA;

extern DMA dma;

void dma_structure_init();

#endif // DMA_H
