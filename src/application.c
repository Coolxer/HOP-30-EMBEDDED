//#ifdef STSTM32
#include "application.h"

#include "settings.h"
#include "clock_manager.h"
#include "uart.h"
#include "device_manager.h"

void application_setup()
{
    //SystemCoreClock = 8000000; // sets default system core main clock frequency
    HAL_Init(); // inits HAL library

    clocks_init();

    uart_init(); // inits uart module
    device_manager_init(); // inits device manager kit
}

void application_run()
{
    uart_listen(); // turns on listening on UART communication port

    //uart_send(data); // sends "FINISED" through UART after get "FINISH" command
}

void application_close()
{
    HAL_DeInit(); // deinits HAL library

    clocks_deinit();
    uart_deinit(); // deinits uart module
    device_manager_deinit(); // deinits device manager kit
}

void application_exec()
{
    application_setup(); // calls all setups
    application_run(); // calls main program loop
    application_close(); // calls all deinit's functions
}

void SysTick_Handler() { 
    HAL_IncTick(); // inits main board clock
}

//#endif // STSTM32