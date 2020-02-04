#ifndef UART_MIN_H
#define UART_MIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal.h"      // includes stm32 HAL library

UART_HandleTypeDef uart;        // uart interface 

/* PRIVATE */   //void uart_setup_gpio();         // sets both tx & rx gpio ports to be ready for uart transmission 
/* PRIVATE */   //void uart_setup_interface();    // prepares uart interface (name, baudrate, parity, oversampling settings, etc...) 

void uart_min_init();               // enables -> calls the setup gpio and interface to working as unit test transport 
void uart_write(char c);        // sends one char to uart port 
void uart_flush();              // flushes uart interface 

#ifdef __cplusplus
}
#endif

#endif // UART_MIN_H
