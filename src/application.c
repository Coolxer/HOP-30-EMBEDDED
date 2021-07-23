#include "application.h"

#include "null.h"

#include "communication/connector.h"
#include "command/cmd_manager.h"

#include "clock_manager.h"
#include "device/device_manager.h"

//#include "command/response_builder.h"

void application_setup()
{
    HAL_Init(); // inits HAL library

    clock_manager_init(); // inits clocks

    /// enables FPU service
    //SCB->CPACR |= ((3 << 10 * 2) | (3 << 11 * 2));

    cmd_manager_init();    // creates opts & keys structures
    connector_init();      // inits connector (uart + dma) module
    device_manager_init(); // inits device manager kit
}

void application_close()
{
    connector_deinit();      // deinits connector
    device_manager_deinit(); // deinits steppers and endstops
    clock_manager_deinit();  // disables clocks
    HAL_DeInit();            // deinits HAL library
}

void application_loop()
{
    /*
    while (1) // while there is not "FINISH" command on uart
    {
        manageDevices(); // services endstop and stepper events

        uint8_t *cmd = uart_listen();

        if (!stringEqual(cmd, EMPTY))
            cmd_manage(cmd);
    }
    */

    while (1)                           // while there is not "FINISH" command on uart
        device_manager_manageDevices(); // services endstop and stepper events
}

void application_run()
{
    application_loop();

    //uart_send(SHUTDOWN_RESPONSE); // sends "FINISHED" through UART after get "FINISH" command
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
