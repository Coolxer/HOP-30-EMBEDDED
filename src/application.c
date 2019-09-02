//#ifdef STSTM32
#include "application.h"

#include "stm32f4xx_hal.h"

#include "uart.h"

#include "device_manager.h"

void application_setup()
{
    HAL_Init();
    uart_init();
    device_manager_init();
}

void application_run()
{
    uart_read();

    uart_write(data);
}

void application_close()
{
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