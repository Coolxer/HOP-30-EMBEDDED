#include "device/stepper/structure/stepper_speed.h"

Speed stepper_speed_init(float min, float max, float homeFastBackward, float homeSlowForward, float homePreciseBackward)
{
    Speed speed = {0};

    speed.min = min;
    speed.max = max;

    speed.homeFastBackward = homeFastBackward;
    speed.homeSlowForward = homeSlowForward;
    speed.homePreciseBackward = homePreciseBackward;

    return speed;
}