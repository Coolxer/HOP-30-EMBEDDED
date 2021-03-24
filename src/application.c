#include "application.h"

#include "clock_manager.h"
#include "communication/uart.h"
#include "command/cmd_builder.h"
#include "connector.h"

#include "device/device_manager.h"

void application_setup()
{
    HAL_Init(); // inits HAL library

    clock_manager_init(); // inits clocks

    /// enables FPU service
    SCB->CPACR |= ((3 << 10 * 2) | (3 << 11 * 2));

    cmd_builder_init();    // creates opts & keys structures
    uart_init();           // inits uart module
    device_manager_init(); // inits device manager kit
}

void application_close()
{
    device_manager_deinit(); // deinits steppers and endstops
    clock_manager_deinit();  // disables clocks
    HAL_DeInit();            // deinits HAL library
}

void application_loop()
{
    while (1) // while there is not "FINISH" command on uart
    {
        uint8_t *command = uart_listen();

        if (!stringEmpty(command))
        {
            if (stringEqual(command, SHUTDOWN_REQUEST)) // checks if receive command is "FINISH"
                break;

            uart_send(connector_manage(connector_parse(command))); // send feedback through UART port
        }

        manageDevices(); // services endstop and stepper events
    }
}

void application_run()
{
    application_loop();

    uart_send(SHUTDOWN_RESPONSE); // sends "FINISHED" through UART after get "FINISH" command
    application_close();          // close the application
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
