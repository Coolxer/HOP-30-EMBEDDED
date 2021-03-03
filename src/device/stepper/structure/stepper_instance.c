#include "device/stepper/structure/stepper_instance.h"

Instance stepper_instance_init()
{
    Instance instance = {0};

    instance.movement = stepper_movement_init();

    instance.state = instance.lastState = OFF;
    instance.homeStep = instance.lastHomeStep = FAST;

    return instance;
}