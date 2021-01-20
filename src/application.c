//#ifdef STSTM32
#include "application.h"

#include <stdlib.h>
#include <string.h>

#include "settings.h"
#include "flags.h"
#include "cmd_builder.h"
#include "clock_manager.h"
#include "connector.h"
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

void application_loop()
{
    while (1)
    {
        if (uart_listen()) // turns on listening on UART communication port
        {
            if (strcmp((void *)command, "FINISH|||||||||||||||") == 0) // checks if receive command is "FINISH"
                break;
            else
                feedback = connector_manage(connector_parse(command)); // passes transmission data to connector manage function where it will be processed

            uart_send(feedback); // send feedback through UART port
        }

        if (ENDSTOP_CLICKED)
            device_manager_endstopClickedCallback();

        if (STEPPER_FINISHED)
            device_manager_stepperFinishedCallback();
    }
}

void application_run()
{
    application_loop();

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