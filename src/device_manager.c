//#ifdef STSTM32
#include "device_manager.h"

#include <stdlib.h>
#include <string.h>

void device_manager_init()
{
    SystemCoreClock = 8000000; // set default system core main clock frequency

    __HAL_RCC_GPIOA_CLK_ENABLE(); // pins should be read from and depend on it the correct RCC_GPIOX should be turn on
    __HAL_RCC_GPIOC_CLK_ENABLE();

    stepper_init(&devices[0], "s1", GPIOC, TIM3, 0, 0, 0, GPIO_PIN_9, GPIO_PIN_8, GPIO_PIN_6, 0); // set for "s1" stepper
    stepper_init(&devices[1], "s2", GPIOA, TIM4, GPIO_PIN_5, 0, 0, 0, 0, 0, 0); // set for "s2" stepper
}

bool device_manager_set_current(uint8_t *name)
{
    uint8_t i;

    for(i = 0; i < DEVICES_COUNT; i++)
    {
        if(strcmp(devices[i].name, name) == 0)
        {
            current = devices[i];
            return true; 
        }
    }
    return false;
}

struct Stepper *device_manager_current()
{
    return &current;
}

//#endif // STSTM32