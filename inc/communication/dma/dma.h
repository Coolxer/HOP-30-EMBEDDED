#ifndef DMA_H
#define DMA_H

#include "stm32f4xx_hal.h"

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

extern DMA_HandleTypeDef hdma_usart2_rx; // dma uart rx channel
extern DMA_HandleTypeDef hdma_usart2_tx; // dma uart tx channel

/* PRIVATE */ //uint8_t tcReady; // flag that informs if transfer is complete TC
extern uint8_t tcReady;

extern UART_HandleTypeDef *huart;
extern DMA dma;

#endif // DMA_H
