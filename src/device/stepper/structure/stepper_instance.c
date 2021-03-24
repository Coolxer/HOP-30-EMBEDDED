#include "device/stepper/structure/stepper_instance.h"

#include "device/stepper/enum/state.h"
#include "device/stepper/enum/home_step.h"

Instance stepper_instance_init()
{
    Instance instance = {0};

    instance.state = instance.lastState = OFF;
    instance.homeStep = FAST_BACKWARD;

    return instance;
}