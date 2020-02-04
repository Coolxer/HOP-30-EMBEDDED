#ifndef DMA_H
#define DMA_H

#include "stm32f4xx_hal.h"

DMA_HandleTypeDef hdma_usart2_rx;

#define DMA_BUFFER_SIZE 64 // dma buffer size
#define UART_BUFFER_SIZE 256 // uart buffer size

typedef struct
{
	UART_HandleTypeDef* uart; // pointer to UART structure

	uint8_t dma_buffer[DMA_BUFFER_SIZE]; // dma buffer
	uint8_t uart_buffer[UART_BUFFER_SIZE]; // uart buffer

	uint16_t head, tail; // head, tail indexes
	uint8_t commands_count; // number of commands
}DMA;

DMA dma; // create structure instance

/* *********************** SETUP FUNCTIONS *********************** */

void dma_setup(UART_HandleTypeDef* uart); // inits structure, enables interrupts

/* PRIVATE */   //void dma_setup_interface(); // setups interface of DMA
/* PRIVATE */   //void dma_setup_interrupts(); // turns on USART2 interrupt and DMA RX stream channel interrupt

void dma_init(); // calls setups of interface and interrupts
void dma_deinit(); // disables DMA clock

/* ******************* OPERATIONAL FUNCTIONS *************** ***** */

uint8_t dma_isReady(); // checks if DMA is ready to read, 1 - yes, 0 - no
uint8_t dma_getChar(); // gets one char from DMA
uint8_t* dma_getCommand(); // gets command from DMA

/* ************************ HANDLERS ***************************** */

/* PRIVATE */   //void dma_uart_handler(); // own implementation of uart interrupt handler
/* PRIVATE */   //void dma_dma_handler(); // own implementation of dma interrupt handler

/* PRIVATE */   //void USART2_IRQHandler(void); // USART2 irq handler
/* PRIVATE */   //void DMA1_Stream5_IRQHandler(void); // DMA1 RX irq handler

#endif // DMA_H
