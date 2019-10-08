//#ifdef STSTM32
#include "device_manager.h"

#include "divider_stepper.h"
#include "table_stepper.h"

#include <stdlib.h>
#include <string.h>

void device_manager_init()
{
    devices[0] = create_divider_stepper();
    devices[1] = create_table_stepper();
}

bool device_manager_set_current(uint8_t *name)
{
    uint8_t i;

    for(i = 0; i < DEVICES_COUNT; i++)
    {
        if(strcmp(devices[i]->name, name) == 0)
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

void device_manager_deinit()
{
    release_divider_stepper();
    release_table_stepper();
}

//#endif // STSTM32