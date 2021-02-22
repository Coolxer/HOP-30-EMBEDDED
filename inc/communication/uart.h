#ifndef UART_H
#define UART_H

#include <stdint.h>

extern uint8_t *command;
extern uint8_t *feedback;

void uart_init(); // calls all UART setups

uint8_t uart_listen();            // enables listening to connected COM port, returns 1 if there is properly command length, otherwise 0
void uart_send(uint8_t *message); // sends message through uart interface

#endif // UART_H
