#include "device/low_voltage/stepper/structure/stepper_speed.h"

Speed stepper_speed_init()
{
    Speed speed = {0};

    speed.current = 0.0f;
    speed.target = 0.0f;

    speed.lastTimeUpdate = 0;

    speed.type = DYNAMIC;
    speed.state = CONSTANT;

    return speed;
}