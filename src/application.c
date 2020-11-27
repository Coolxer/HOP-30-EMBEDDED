//#ifdef STSTM32
#include "application.h"

#include "settings.h"
#include "cmd_builder.h"
#include "clock_manager.h"
#include "uart.h"
#include "device_manager.h"

void application_setup()
{
    HAL_Init(); // inits HAL library

    clocks_init(); // enables clocks

    cmd_builder_init();    // creates opts & keys structures
    uart_init();           // inits uart module
    device_manager_init(); // inits device manager kit
}

void application_close()
{
    device_manager_deinit(); // deinits steppers and endstops
    clocks_deinit();         // disables clocks
    HAL_DeInit();            // deinits HAL library
}

void application_run()
{
    uart_listen();                    // turns on listening on UART communication port
    uart_send((uint8_t *)"FINISHED"); // sends "FINISHED" through UART after get "FINISH" command

    HAL_Delay(5);        // wait a litte bit to finish sending response
    application_close(); // close the application
}

void application_exec()
{
    application_setup(); // calls all setups
    application_run();   // calls main program loop
    application_close(); // calls all deinit's functions
}

void SysTick_Handler()
{
    HAL_IncTick(); // inits main board clock
}

//#endif // STSTM32