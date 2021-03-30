#include "device/stepper/config/stepper_config.h"

#include "null.h"

#include "device/stepper/config/stepper_connection.h"
#include "device/stepper/config/stepper_speed_acceleration_constraint.h"

StepperConfig X_STEPPER_CONFIG = {0};
StepperConfig Y_STEPPER_CONFIG = {0};
StepperConfig Z_STEPPER_CONFIG = {0};
StepperConfig W_STEPPER_CONFIG = {0};

void stepper_x_config()
{
    Hardware hardware = stepper_hardware_init(X_PORT, X_MASTER_TIMER, X_SLAVE_TIMER, X_ALTERNATE_FUNCTION,
                                              X_CHANNEL, X_ITR, X_IRQ, X_STEP, X_DIR, X_ENABLE);

    Speed speed = stepper_speed_init(X_MIN_SPEED, X_MAX_SPEED, X_HOME_FAST_BACKWARD_SPEED, X_HOME_SLOW_FORWARD_SPEED, X_HOME_PRECISE_BACKWARD_SPEED);

    Acceleration acceleration = stepper_acceleration_init(X_MIN_ACCELERATION, X_MAX_ACCELERATION, X_HOME_FAST_BACKWARD_ACCELERATION,
                                                          X_HOME_SLOW_FORWARD_ACCELERATION, X_HOME_PRECISE_BACKWARD_ACCELERATION);

    X_STEPPER_CONFIG.hardware = hardware;
    X_STEPPER_CONFIG.speed = speed;
    X_STEPPER_CONFIG.acceleration = acceleration;
}

void stepper_y_config()
{
    Hardware hardware = stepper_hardware_init(Y_PORT, Y_MASTER_TIMER, Y_SLAVE_TIMER, Y_ALTERNATE_FUNCTION,
                                              Y_CHANNEL, Y_ITR, Y_IRQ, Y_STEP, Y_DIR, Y_ENABLE);

    Speed speed = stepper_speed_init(Y_MIN_SPEED, Y_MAX_SPEED, Y_HOME_FAST_BACKWARD_SPEED, Y_HOME_SLOW_FORWARD_SPEED, Y_HOME_PRECISE_BACKWARD_SPEED);

    Acceleration acceleration = stepper_acceleration_init(Y_MIN_ACCELERATION, Y_MAX_ACCELERATION, Y_HOME_FAST_BACKWARD_ACCELERATION,
                                                          Y_HOME_SLOW_FORWARD_ACCELERATION, Y_HOME_PRECISE_BACKWARD_ACCELERATION);

    Y_STEPPER_CONFIG.hardware = hardware;
    Y_STEPPER_CONFIG.speed = speed;
    Y_STEPPER_CONFIG.acceleration = acceleration;
}

void stepper_z_config()
{
    Hardware hardware = stepper_hardware_init(Z_PORT, Z_MASTER_TIMER, Z_SLAVE_TIMER, Z_ALTERNATE_FUNCTION,
                                              Z_CHANNEL, Z_ITR, Z_IRQ, Z_STEP, Z_DIR, Z_ENABLE);

    Speed speed = stepper_speed_init(Z_MIN_SPEED, Z_MAX_SPEED, Z_HOME_FAST_BACKWARD_SPEED, Z_HOME_SLOW_FORWARD_SPEED, Z_HOME_PRECISE_BACKWARD_SPEED);

    Acceleration acceleration = stepper_acceleration_init(Z_MIN_ACCELERATION, Z_MAX_ACCELERATION, Z_HOME_FAST_BACKWARD_ACCELERATION,
                                                          Z_HOME_SLOW_FORWARD_ACCELERATION, Z_HOME_PRECISE_BACKWARD_ACCELERATION);

    Z_STEPPER_CONFIG.hardware = hardware;
    Z_STEPPER_CONFIG.speed = speed;
    Z_STEPPER_CONFIG.acceleration = acceleration;
}

void stepper_w_config()
{
    Hardware hardware = stepper_hardware_init(W_PORT, W_MASTER_TIMER, W_SLAVE_TIMER, W_ALTERNATE_FUNCTION,
                                              W_CHANNEL, W_ITR, W_IRQ, W_STEP, W_DIR, W_ENABLE);

    Speed speed = stepper_speed_init(W_MIN_SPEED, W_MAX_SPEED, 0.0f, 0.0f, 0.0f);

    Acceleration acceleration = stepper_acceleration_init(W_MIN_ACCELERATION, W_MAX_ACCELERATION, 0.0f, 0.0f, 0.0f);

    W_STEPPER_CONFIG.hardware = hardware;
    W_STEPPER_CONFIG.speed = speed;
    W_STEPPER_CONFIG.acceleration = acceleration;
}

void stepper_config()
{
    stepper_x_config();
    stepper_y_config();
    stepper_z_config();
    stepper_w_config();
}