//#ifdef STSTM32
#include "device_manager.h"

#include <stdlib.h>
#include <string.h>

#include "settings.h"

void device_manager_init()
{
    devices[0] = (struct Device*)stepper_init(DIVIDER_NAME, DIVIDER_TIMER, DIVIDER_PORT, DIVIDER_DIR, DIVIDER_STEP, DIVIDER_ENABLE, DIVIDER_M1, DIVIDER_M2, DIVIDER_M3);
    devices[1] = (struct Device*)stepper_init(TABLE_NAME, TABLE_TIMER, TABLE_PORT, TABLE_DIR, TABLE_STEP, TABLE_ENABLE, TABLE_M1, TABLE_M2, TABLE_M3);

    devices[2] = (struct Device*)endstop_init(DIVIDER_MIN_ENDSTOP_NAME, DIVIDER_MIN_ENDSTOP_PORT, DIVIDER_MIN_ENDSTOP_EXT, DIVIDER_MIN_ENDSTOP_PIN);
}

bool device_manager_set_current(uint8_t *name)
{
    uint8_t i;

    for(i = 0; i < DEVICES_COUNT; i++)
    {
        Device * const device = devices[i];

        if(strcmp(device->name, name) == 0)
        {
            if(device->type == STEPPER)
                stepper = device;
                
            else if (device->type == ENDSTOP)
                endstop = device; 

            current = device;
            
            return true;
        }
    }

    return false;
}

void device_manager_deinit()
{
    device_manager_set_current("s1");
    stepper_deinit();
    device_manager_set_current("s2");
    stepper_deinit();
    device_manager_set_current("e1");
    endstop_deinit();
}

//#endif // STSTM32