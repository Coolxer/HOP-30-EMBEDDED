#ifndef DMA_H
#define DMA_H

#include "stm32f4xx_hal.h"

DMA_HandleTypeDef hdma_usart2_rx; // dma uart rx channel
DMA_HandleTypeDef hdma_usart2_tx; // dma uart tx channel

//#define DMA_BUFFER_SIZE 64	 // dma buffer size
//#define UART_BUFFER_SIZE 256 // uart buffer size

enum
{
	DMA_BUFFER_SIZE = 64,
	UART_BUFFER_SIZE = 256
};

typedef struct
{
	UART_HandleTypeDef *uart; // pointer to UART structure

	uint8_t dma_buffer[DMA_BUFFER_SIZE];   // dma buffer
	uint8_t uart_buffer[UART_BUFFER_SIZE]; // uart buffer

	uint16_t head, tail;	// head, tail indexes
	uint8_t commands_count; // number of commands

	uint8_t empty; // informs if data come
} DMA;

/* PRIVATE */ uint8_t tcReady; // flag that informs if transfer is complete TC

DMA dma;
UART_HandleTypeDef *huart;

#endif // DMA_H
