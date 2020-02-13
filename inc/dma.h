#ifndef DMA_H
#define DMA_H

#include "stm32f4xx_hal.h"
DMA_HandleTypeDef hdma_usart2_rx;          // dma uart rx channel
DMA_HandleTypeDef hdma_usart2_tx;		   // dma uart tx channel

#define DMA_BUFFER_SIZE 64 				   // dma buffer size
#define UART_BUFFER_SIZE 256			   // uart buffer size

typedef struct
{
	UART_HandleTypeDef *uart; 		       // pointer to UART structure

	uint8_t dma_buffer[DMA_BUFFER_SIZE];   // dma buffer
	uint8_t uart_buffer[UART_BUFFER_SIZE]; // uart buffer

	uint16_t head, tail; 				   // head, tail indexes
	uint8_t commands_count; 			   // number of commands

	uint8_t empty;						   // informs if data come
}DMA;

/* *********************** SETUP FUNCTIONS *********************** */

void dma_setup(UART_HandleTypeDef *uart); 	   // inits structure, enables interrupts

/* PRIVATE */   //void dma_setupInterface();  // setups interface of DMA
/* PRIVATE */   //void dma_setupInterrupts(); // turns on USART2 interrupt and DMA RX stream channel interrupt

void dma_init(); 							   // calls setups of interface and interrupts

/* ******************* OPERATIONAL FUNCTIONS *************** ***** */

uint8_t dma_isEmpty();
void dma_clear();

uint8_t dma_isReady(); 						   // checks if DMA is ready to read, 1 - yes, 0 - no
/* PRIVATE */	//uint8_t dma_getChar(); 	   // returns one char from DMA
uint8_t* dma_getCommand(); 					   // returns command from DMA

/* ************************ HANDLERS ***************************** */

/* PRIVATE */   //void dma_uartHandler(); 			  // own implementation of uart interrupt handler
/* PRIVATE */   //void dma_dmaHandler(); 			  // own implementation of dma interrupt handler

/* PRIVATE */   //void USART2_IRQHandler(void); 	  // USART2 irq handler
/* PRIVATE */   //void DMA1_Stream5_IRQHandler(void); // DMA1 RX irq handler

#endif // DMA_H
