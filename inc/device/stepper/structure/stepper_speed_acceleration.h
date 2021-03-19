#ifndef STEPPER_SPEED_ACCELERATION_H
#define STEPPER_SPEED_ACCELERATION_H

#include "device/stepper/structure/stepper_speed.h"
#include "device/stepper/structure/stepper_acceleration.h"

typedef struct
{
    Speed speed;
    Acceleration acceleration;
} SpeedAcceleration;

SpeedAcceleration stepper_speedAcceleration_init(float minSpeed, float minAcceleration, float maxSpeed, float maxAcceleration, float homeFastBackwardSpeed, float homeFastBackwardAcceleration, float homeSlowForwardSpeed, float homeSlowForwardAcceleration, float homePreciseBackwardSpeed, float homePreciseBackwardAcceleration);

#endif // STEPPER_SPEED_ACCELERATION_H