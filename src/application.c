//#ifdef STSTM32
#include "application.h"

#include "settings.h"

#include "uart.h"

void application_setup()
{
    HAL_Init();

    SystemCoreClock = CLOCK_SPEED; // set default system core main clock frequency

    __HAL_RCC_GPIOA_CLK_ENABLE();  // init port A, where divider motor is connected 
    __HAL_RCC_GPIOC_CLK_ENABLE();  // init port C, where table motor is connected 

    uart_init();
    device_manager_init();
}

void application_run()
{
    uart_listen();

    uart_send(data);
}

void application_close()
{
    __HAL_RCC_GPIOA_CLK_DISABLE();
    __HAL_RCC_GPIOC_CLK_DISABLE();

    HAL_DeInit();
    uart_deinit();
}

void application_exec()
{
    application_setup();
    application_run();
    application_close();
}

void SysTick_Handler() {
    HAL_IncTick();
}

//#endif // STSTM32