#include "device/stepper/structure/stepper_speed_acceleration.h"

SpeedAcceleration stepper_speedAcceleration_init(float minSpeed, float minAcceleration, float maxSpeed, float maxAcceleration, float homeFastBackwardSpeed, float homeFastBackwardAcceleration, float homeSlowForwardSpeed, float homeSlowForwardAcceleration, float homePreciseBackwardSpeed, float homePreciseBackwardAcceleration)
{
    SpeedAcceleration speedAcceleration = {0};

    speedAcceleration.speed = stepper_speed_init(minSpeed, maxSpeed, homeFastBackwardSpeed, homeSlowForwardSpeed, homePreciseBackwardSpeed);
    speedAcceleration.acceleration = stepper_acceleration_init(minAcceleration, maxAcceleration, homeFastBackwardAcceleration, homeSlowForwardAcceleration, homePreciseBackwardAcceleration);

    return speedAcceleration;
}