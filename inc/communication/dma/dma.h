#ifndef DMA_H
#define DMA_H

#include "stm32f4xx_hal.h"

#include "communication/config/communication.h"

typedef struct
{
	uint8_t requestBuffer[MAX_COMMAND_SIZE];

	DMA_HandleTypeDef requestLine;
	DMA_HandleTypeDef responseLine;
} DMA;

extern DMA dma;

extern volatile uint8_t TRANSFER_COMPLETE;

#endif // DMA_H
