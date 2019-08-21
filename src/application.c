#include "application.h"

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

    }
}

void application_close()
{
    uart_deinit();
    device_manager_deinit();
}
