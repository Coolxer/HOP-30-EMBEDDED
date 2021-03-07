#include "device/stepper/structure/stepper_instance.h"

#include "enum/type.h"

Instance stepper_instance_init()
{
    Instance instance = {0};

    instance.movement = stepper_movement_init();
    instance.state = instance.lastState = OFF;
    instance.homeStep = FAST;
    instance.FINISHED_FLAG = RESET;

    return instance;
}