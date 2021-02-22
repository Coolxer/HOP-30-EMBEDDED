#ifndef UART_MIN_H
#define UART_MIN_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "stm32f4xx_hal.h"

    extern UART_HandleTypeDef uart; // uart interface

    /* PRIVATE */ //void uart_setupGpio();         // sets both tx & rx gpio ports to be ready for uart transmission
    /* PRIVATE */ //void uart_setupInterface();    // prepares uart interface (name, baudrate, parity, oversampling settings, etc...)

    void uart_min_init();    // enables -> calls the setup gpio and interface to working as unit test transport
    void uart_write(char c); // sends one char to uart port (used only in unit tests)
    void uart_flush();       // flushes uart interface (unit tests only)
    void uart_min_end();     // (unit tests only)

#ifdef __cplusplus
}
#endif

#endif // UART_MIN_H
