#ifndef UART_H
#define UART_H

#include "stm32f4xx_hal.h"

DMA_HandleTypeDef hdma_uart_rx; // rx interface 
DMA_HandleTypeDef hdma_uart_tx; // tx interface 

void uart_setup_dma(); // prepares tx & rx interface to work in DMA mode 
void uart_setup_nvic(); // sets the nvic interrupts priorities 

void uart_init(); // calls all setups and turns on the listening on usart2 
void uart_deinit(); // frees memmory and disables all periphals in common, timers etc.

void uart_enable();
void uart_disable();

void uart_send(uint8_t *message);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef* usart); // calls if there is any data on rx receiving buffer (only if buffer has its own defined size -> @data_size) 

#endif // UART_H
