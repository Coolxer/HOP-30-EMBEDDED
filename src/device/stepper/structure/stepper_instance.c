#include "device/stepper/structure/stepper_instance.h"

#include "device/stepper/enum/state.h"
#include "device/stepper/enum/home_step.h"

Instance stepper_instance_init()
{
    Instance instance = {0};

    instance.movement = stepper_movement_init();
    instance.state = instance.lastState = OFF;
    instance.homeStep = FAST_BACKWARD;
    instance.FINISHED_FLAG = RESET;

    return instance;
}