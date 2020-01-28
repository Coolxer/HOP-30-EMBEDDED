#ifndef UART_H
#define UART_H

#include "stm32f4xx_hal.h"

#include "connector.h"

void uart_init();                 // calls all UART setups
void uart_deinit();               // frees memmory and disables all periphals in common with UART: timers, etc.

void uart_listen();               // enables listening to connected COM port
void uart_send(uint8_t *message); // sends message through uart interface

uint8_t uart_manage();               // manages received data; returns FALSE if there is FINISH message, otherwise returns TRUE

#endif // UART_H
