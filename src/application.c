//ifdef STSTM32
#include "application.h"

#include <stdbool.h>

#include "uart.h"
#include "device_manager.h"

void application_setup()
{
    uart_init();
    device_manager_init();
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
    device_manager_deinit();
}

void application_exec()
{
    
}

//#endif // STSTM32