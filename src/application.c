//#ifdef STSTM32
#include "application.h"

#include "settings.h"

#include "uart.h"

void application_setup()
{
    //SystemCoreClock = 8000000; // sets default system core main clock frequency
    HAL_Init(); // inits HAL library

    __HAL_RCC_GPIOA_CLK_ENABLE();  // enables port A clock, where divider motor is connected 
    __HAL_RCC_GPIOB_CLK_ENABLE();  // enables port B clock, where table motor is connected 

    uart_init(); // inits uart module
    device_manager_init(); // inits device manager kit
}

void application_run()
{
    uart_listen(); // turns on listening on UART communication port

    uart_send(data); // sends "FINISED" through UART after get "FINISH" command
}

void application_close()
{
    __HAL_RCC_GPIOA_CLK_DISABLE(); // disables port A clock
    __HAL_RCC_GPIOB_CLK_DISABLE(); // disables port A clock

    HAL_DeInit(); // deinits HAL library
    uart_deinit(); // deinits uart module
    device_manager_deinit(); // deinits device manager kit
}

void application_exec()
{
    application_setup(); // calls all setups
    application_run(); // calls main program loop
    application_close() // calls all deinit's functions
}

void SysTick_Handler() { 
    HAL_IncTick(); // inits main board clock
}

//#endif // STSTM32