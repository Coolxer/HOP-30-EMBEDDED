#ifndef STEPPER_SPEED_CONSTRAINT
#define STEPPER_SPEED_CONSTRAINT

/* ATTENTION!
    # MIN and MAX speed for LINEAR axis are given in mm/s [millimeters per second]
    # MIN and MAX speed for CIRCULAR axis are given in rpm [rotates per minute]
*/

/**************** X STEPPER  ******************/
const float X_MIN_SPEED = 0.1f;
const float X_MAX_SPEED = 100.0f;

/************* END OF X STEPPER  **************/

/**************** Y STEPPER  ******************/

const float Y_MIN_SPEED = 0.1f;
const float Y_MAX_SPEED = 100.0f;

/************* END OF Y STEPPER  **************/

/**************** Z STEPPER  ******************/

const float Z_MIN_SPEED = 0.1f;
const float Z_MAX_SPEED = 100.0f;

/************* END OF Z STEPPER  **************/

/**************** W STEPPER  ******************/

const float W_MIN_SPEED = 1.0f;
const float W_MAX_SPEED = 100.0f;

/************* END OF W STEPPER  **************/

#endif // STEPPER_SPEED_CONSTRAINT