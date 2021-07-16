#ifndef UART_H
#define UART_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "stm32f4xx_hal.h"

    extern UART_HandleTypeDef uart; // uart interface

    /* PRIVATE */ //void uart_setupGpio();         // sets both tx & rx gpio ports to be ready for uart transmission
    /* PRIVATE */ //void uart_setupInterface();    // prepares uart interface (name, baudrate, parity, oversampling settings, etc...)

    void uart_init();
    void uart_deinit();

    void uart_write(char c); // [unit test]
    void uart_send(uint8_t *message);

    void uart_flush(); // [unit test]

#ifdef __cplusplus
}
#endif

#endif // UART_H
