#ifndef UART_H
#define UART_H

#include "stm32f4xx_hal.h"

/* defined consts */
const uint16_t usart2_tx = GPIO_PIN_2; /* usart2 tx gpio (PIN 2) */
const uint16_t usart2_rx = GPIO_PIN_3; /* usart2 rx gpio (PIN 3) */
const uint8_t data_size = 30;  /* size of data transmission */

uint8_t data[data_size]; /* array of uint8_t using for keep in received data */

DMA_HandleTypeDef hdma_uart_rx; /* rx interface */
DMA_HandleTypeDef hdma_uart_tx; /* tx interface */
UART_HandleTypeDef uart; /* uart interface */

void uart_setup_gpio(); /* sets both tx & rx gpio ports to be ready for uart transmission */
void uart_setup_dma(); /* prepares tx & rx interface to work in DMA mode */
void uart_setup_uart(); /* prepares uart interface */
void uart_setup_nvic(); /* sets the nvic interrupts priorities */

void uart_init(); /* calls all setups and turns on the listening on usart2 */
void uart_deinit(); /* disables all uart peripherals */

void HAL_UART_RxCpltCallback(UART_HandleTypeDef* usart); /* calls if there is any data on rx receiving buffer (only if buffer has its own defined size -> @data_size) */

#endif // UART_H
