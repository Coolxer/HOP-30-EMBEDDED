#ifndef DMA_H
#define DMA_H

#include "stm32f4xx_hal.h"

DMA_HandleTypeDef hdma_usart2_rx;

#define DMA_BUFFER_SIZE 64 // dma buffer size
#define UART_BUFFER_SIZE 256 // uart buffer size

struct DMA
{
	UART_HandleTypeDef* uart; // pointer to UART structure

	uint8_t dma_buffer[DMA_BUFFER_SIZE]; // dma buffer
	uint8_t uart_buffer[UART_BUFFER_SIZE]; // uart buffer

	uint16_t head, tail; // head, tail indexes
	uint8_t commands_count; // number of commands
};

struct DMA dma; // create structure instance

/* *********************** SETUP FUNCTIONS *********************** */

void dma_init(UART_HandleTypeDef* uart); // inits structure, enables interrupts

void dma_setup(); // calls setups of interface and interrupts
void dma_setup_interface(); // setups interface of DMA
void dma_setup_interrupts(); // turns on USART2 interrupt and DMA RX stream channel interrupt

/* ******************* OPERATIONAL FUNCTIONS *************** ***** */

uint8_t dma_isReady(); // checks if DMA is ready to read, 1 - yes, 0 - no

uint8_t dma_getChar(); // gets one char from DMA
uint8_t* dma_getCommand(); // gets command from DMA

/* ************************ HANDLERS ***************************** */

void dma_uart_handler(); // own implementation of uart interrupt handler
void dma_dma_handler(); // own implementation of dma interrupt handler

void USART2_IRQHandler(void); // USART2 irq handler
void DMA1_Stream5_IRQHandler(void); // DMA1 RX irq handler

#endif // DMA_H
