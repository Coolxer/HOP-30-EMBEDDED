//#ifdef STSTM32
#include "application.h"

#include <stdbool.h> // includes uint8_t data type

#include "uart.h"

void application_setup()
{
    uart_init();
}

void application_run()
{
    while(1)
    {
        if(end_flag)
            break;
    }
}

void application_close()
{
    uart_deinit();
}

void application_exec()
{
    application_setup();
    application_run();
    application_close();
}

//#endif  // STSTM32