#ifndef STEPPER_SPEED_ACCELERATION_CONSTRAINT
#define STEPPER_SPEED_ACCELERATION_CONSTRAINT

/* ATTENTION!
    # Speed for LINEAR axis are given in mm/s [millimeters per second]
    # Speed for CIRCULAR axis are given in rpm [rotates per minute]
*/

/**************** X STEPPER  ******************/
const float X_MIN_SPEED = 0.1f;
const float X_MAX_SPEED = 100.0f;

const float X_MIN_ACCELERATION = 0.1f;
const float X_MAX_ACCELERATION = 100.0f;

const float X_HOME_FAST_BACKWARD_SPEED = 10.0f;
const float X_HOME_FAST_BACKWARD_ACCELERATION = 5.0f;

const float X_HOME_SLOW_FORWARD_SPEED = 5.0f;
const float X_HOME_SLOW_FORWARD_ACCELERATION = 5.0f;

const float X_HOME_PRECISE_BACKWARD_SPEED = 1.0f;
const float X_HOME_PRECISE_BACKWARD_ACCELERATION = 1.0f;

/************* END OF X STEPPER  **************/

/**************** Y STEPPER  ******************/

const float Y_MIN_SPEED = 0.1f;
const float Y_MAX_SPEED = 100.0f;

const float Y_MIN_ACCELERATION = 0.1f;
const float Y_MAX_ACCELERATION = 100.0f;

const float Y_HOME_FAST_BACKWARD_SPEED = 10.0f;
const float Y_HOME_FAST_BACKWARD_ACCELERATION = 5.0f;

const float Y_HOME_SLOW_FORWARD_SPEED = 5.0f;
const float Y_HOME_SLOW_FORWARD_ACCELERATION = 5.0f;

const float Y_HOME_PRECISE_BACKWARD_SPEED = 1.0f;
const float Y_HOME_PRECISE_BACKWARD_ACCELERATION = 1.0f;
;

/************* END OF Y STEPPER  **************/

/**************** Z STEPPER  ******************/

const float Z_MIN_SPEED = 0.1f;
const float Z_MAX_SPEED = 100.0f;

const float Z_MIN_ACCELERATION = 0.1f;
const float Z_MAX_ACCELERATION = 100.0f;

const float Z_HOME_FAST_BACKWARD_SPEED = 10.0f;
const float Z_HOME_FAST_BACKWARD_ACCELERATION = 5.0f;

const float Z_HOME_SLOW_FORWARD_SPEED = 5.0f;
const float Z_HOME_SLOW_FORWARD_ACCELERATION = 5.0f;

const float Z_HOME_PRECISE_BACKWARD_SPEED = 1.0f;
const float Z_HOME_PRECISE_BACKWARD_ACCELERATION = 1.0f;

/************* END OF Z STEPPER  **************/

/**************** W STEPPER  ******************/

const float W_MIN_SPEED = 1.0f;
const float W_MAX_SPEED = 100.0f;

const float W_MIN_ACCELERATION = 0.1f;
const float W_MAX_ACCELERATION = 100.0f;

/************* END OF W STEPPER  **************/

#endif // STEPPER_SPEED_ACCELERATION_CONSTRAINT