#ifdef STSTM32
#include "device_manager.h"

#include <stdlib.h>
#include <string.h>

void device_manager_init()
{
    stepper_init(&devices[0], "s1", GPIO_PIN_5, 0, 0, 0, 0, 0, 0); // set for "s1" stepper
    stepper_init(&devices[1], "s2", 0, 0, 0, 0, 0, 0, 0); // set for "s2" stepper

    current = (struct Stepper *) malloc(sizeof(struct Stepper)); // reserve memory for current device
}

void device_manager_deinit()
{
    free(current); // free memory for current
}

void device_manager_set_current(uint8_t *name)
{
    uint8_t i;

    for(i = 0; i < DEVICES_COUNT; i++)
        if(strcmp(devices[i].name, name) == 0)
                current = &devices[i];
}

struct Stepper *device_manager_current()
{
    return current;
}

#endif // STSTM32