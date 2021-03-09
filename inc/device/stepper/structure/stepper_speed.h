#ifndef STEPPER_SPEED_H
#define STEPPER_SPEED_H

typedef struct
{
    float min,
        max,

        homeFastBackward,
        homeSlowForward,
        homePreciseBackward;
} Speed;

Speed stepper_speed_init(float min, float max, float homeFastBackward, float homeSlowForward, float homePreciseBackward);

#endif // STEPPER_SPEED_H