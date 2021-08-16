#include "../inc/communication/uart.h"
#include <output_export.h>



#ifdef __GNUC__
void output_start(unsigned int baudrate __attribute__((unused)))
#else
void output_start(unsigned int baudrate)
#endif
{
    uart_init();
}

void output_char(int c)
{
    uart_write(c);
}

void output_flush(void)
{
    uart_flush();
}

void output_complete(void)
{
   uart_deinit();
}