#ifndef UART_H
#define UART_H

#include "stm32f4xx_hal.h"

#include "connector.h"

#include <stdbool.h>

#define DATA_SIZE 64              // communication data size

uint8_t data[DATA_SIZE];          // array using for receiving data and stores messages

void uart_init();                 // calls all UART setups
void uart_deinit();               // frees memmory and disables all periphals in common with UART: timers, etc.

void uart_listen();               // enables listening to connected COM port
void uart_send(uint8_t *message); // sends message through uart interface

bool uart_manage();               // manages received data; returns FALSE if there is FINISH message, otherwise returns TRUE

#endif // UART_H
