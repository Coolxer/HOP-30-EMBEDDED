#ifndef UART_MIN_H
#define UART_MIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal.h"      // includes stm32 HAL library

#define USART2_TX GPIO_PIN_2    // define uart tx pin as 2 (send)
#define USART2_RX GPIO_PIN_3    // define uart rx pins as 3 (receive)

UART_HandleTypeDef uart;        // uart interface 

void uart_setup_gpio();         // sets both tx & rx gpio ports to be ready for uart transmission 
void uart_setup_interface();    // prepares uart interface 

void uart_start();              // enables -> calls the setup gpio and interface to working as unit test transport 
void uart_write(char c);        // sends one char to uart port 
void uart_flush();              // flushes uart interface 
void uart_end();                // disables all peripherals related to uart 

#ifdef __cplusplus
}
#endif

#endif // UART_MIN_H
