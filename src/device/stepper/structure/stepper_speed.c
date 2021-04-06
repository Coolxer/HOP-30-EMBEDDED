#include "device/stepper/structure/stepper_speed.h"

Speed stepper_speed_init(float min, float max, float homeFastBackward, float homeSlowForward, float homePreciseBackward)
{
    Speed speed = {0};

    speed.min = min;
    speed.max = max;

    speed.current = 0.0f;
    speed.target = 0.0f;

    speed.homeFastBackward = homeFastBackward;
    speed.homeSlowForward = homeSlowForward;
    speed.homePreciseBackward = homePreciseBackward;

    speed.lastTimeUpdate = 0;

    speed.type = STATIC;

    speed.state = CONSTANT;

    return speed;
}