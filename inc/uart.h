#ifndef UART_H
#define UART_H

#include "stm32f4xx_hal.h"
#include "uart_min.h"

const uint8_t data_size = 64;  /* size of data transmission */

uint8_t *data; /* array of uint8_t using for keep in received data */

DMA_HandleTypeDef hdma_uart_rx; /* rx interface */
DMA_HandleTypeDef hdma_uart_tx; /* tx interface */

void uart_setup_dma(); /* prepares tx & rx interface to work in DMA mode */
void uart_setup_nvic(); /* sets the nvic interrupts priorities */

void uart_extend(); /* calls all setups and turns on the listening on usart2 */

void HAL_UART_RxCpltCallback(UART_HandleTypeDef* usart); /* calls if there is any data on rx receiving buffer (only if buffer has its own defined size -> @data_size) */

#endif // UART_H
