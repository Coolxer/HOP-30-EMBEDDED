#ifndef STEPPER_CONFIG_H
#define STEPPER_CONFIG_H

#include "device/stepper/structure/stepper_hardware.h"
#include "device/stepper/structure/stepper_speed.h"
#include "device/stepper/structure/stepper_acceleration.h"

// X STEPPER
extern uint8_t *X_NAME;
extern Hardware X_HARDWARE;
extern Speed X_SPEED;
extern Acceleration X_ACCELERATION;

// Y STEPPER
extern uint8_t *Y_NAME;
extern Hardware Y_HARDWARE;
extern Speed Y_SPEED;
extern Acceleration Y_ACCELERATION;

// Z STEPPER
extern uint8_t *Z_NAME;
extern Hardware Z_HARDWARE;
extern Speed Z_SPEED;
extern Acceleration Z_ACCELERATION;

// W STEPPER
extern uint8_t *W_NAME;
extern Hardware W_HARDWARE;
extern Speed W_SPEED;
extern Acceleration W_ACCELERATION;

/* PRIVATE */ //void stepper_x_config();
/* PRIVATE */ //void stepper_y_config();
/* PRIVATE */ //void stepper_z_config();
/* PRIVATE */ //void stepper_w_config();

void stepper_config();

#endif // STEPPER_CONFIG_H