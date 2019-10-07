//#ifdef STSTM32
#include "device_manager.h"

#include <stdlib.h>
#include <string.h>

void device_manager_init()
{
    //void stepper_init( Stepper *s,  *_name, TIM_TypeDef *_instance,  _port,  _enable_pin,  _dir_pin,  _step_pin,  _m1,  _m2,  _m3,  _endstop_pin);
    stepper_init(&devices[0], "s1", DIVIDER_TIMER, DIVIDER_PORT, DIVIDER_DIR, DIVIDER_STEP, DIVIDER_ENABLE, DIVIDER_M1, DIVIDER_M2, DIVIDER_M3, 0, 0); // set for "s1" stepper
    stepper_init(&devices[1], "s2", TABLE_TIMER, TABLE_PORT, TABLE_DIR, TABLE_STEP, TABLE_ENABLE, TABLE_M1, TABLE_M2, TABLE_M3, TABLE_MIN_ENDSTOP, TABLE_MAX_ENDSTOP); // set for "s2" stepper

    DIVIDER_TIMER_INIT();
    TABLE_TIMER_INIT()
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

void device_manager_deinit()
{
    DIVIDER_TIMER_DEINIT();
    TABLE_TIMER_DEINIT();
}

//#endif // STSTM32