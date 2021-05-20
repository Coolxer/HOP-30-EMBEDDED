#include "device/low_voltage/stepper/structure/stepper_acceleration.h"

Acceleration stepper_acceleration_init()
{
    Acceleration acceleration = {0};

    acceleration.current = 0.0f;
    acceleration.stepsNeededToAccelerate = 0;

    return acceleration;
}