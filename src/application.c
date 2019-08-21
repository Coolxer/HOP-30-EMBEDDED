#include "application.h"

#include "uart.h"
#include "device_manager.h"
#include "connector.h"
#include "prepare_functions.h"

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
