#include "device/stepper/structure/stepper_acceleration.h"

Acceleration stepper_acceleration_init(float min, float max, float homeFastBackward, float homeSlowForward, float homePreciseBackward)
{
    Acceleration acceleration = {0};

    acceleration.min = min;
    acceleration.max = max;

    acceleration.homeFastBackward = homeFastBackward;
    acceleration.homeSlowForward = homeSlowForward;
    acceleration.homePreciseBackward = homePreciseBackward;

    acceleration.current = 0.0f;

    acceleration.stepsNeededToAccelerate = 0;

    return acceleration;
}