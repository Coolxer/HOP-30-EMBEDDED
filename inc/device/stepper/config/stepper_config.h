#ifndef STEPPER_CONFIG_H
#define STEPPER_CONFIG_H

#include "device/stepper/structure/stepper_hardware.h"
#include "device/stepper/structure/stepper_speed.h"
#include "device/stepper/structure/stepper_acceleration.h"

typedef struct
{
    Hardware hardware;
    Speed speed;
    Acceleration acceleration;
} StepperConfig;

extern StepperConfig X_STEPPER_CONFIG;
extern StepperConfig Y_STEPPER_CONFIG;
extern StepperConfig Z_STEPPER_CONFIG;
extern StepperConfig W_STEPPER_CONFIG;

/* PRIVATE */ //void stepper_x_config();
/* PRIVATE */ //void stepper_y_config();
/* PRIVATE */ //void stepper_z_config();
/* PRIVATE */ //void stepper_w_config();

void stepper_config();

#endif // STEPPER_CONFIG_H