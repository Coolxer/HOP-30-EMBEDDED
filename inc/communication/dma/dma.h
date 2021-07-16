#ifndef DMA_H
#define DMA_H

#include "stm32f4xx_hal.h"

#include "communication/config/communication.h"

typedef struct
{
	uint8_t commandBuffer[COMMAND_SIZE];
	uint8_t responseBuffer[RESPONSE_SIZE];

	DMA_HandleTypeDef commandLine;
	DMA_HandleTypeDef responseLine;
} DMA;

extern DMA dma;

#endif // DMA_H
