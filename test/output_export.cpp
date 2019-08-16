#include "embedded/test_uart/test_uart.c"
#include <output_export.h>



void output_start(unsigned int baudrate)
{
    test_uart_begin();
}

void output_char(int c)
{
    test_uart_putchar(c);
}

void output_flush(void)
{
    test_uart_flush();
}

void output_complete(void)
{
   test_uart_end();
}