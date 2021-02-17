#ifndef STEPPER_SPEED_CONSTRAINT
#define STEPPER_SPEED_CONSTRAINT

/* ATTENTION!
    # MIN and MAX speed for LINEAR axis are given in mm/s [millimeters per second]
    # MIN and MAX speed for CIRCULAR axis are given in rpm [rotates per minute]
*/

/**************** X STEPPER  ******************/

#define X_MIN_SPEED 0.1
#define X_MAX_SPEED 100

/************* END OF X STEPPER  **************/

/**************** Y STEPPER  ******************/

#define Y_MIN_SPEED 0.1
#define Y_MAX_SPEED 100

/************* END OF Y STEPPER  **************/

/**************** Z STEPPER  ******************/

#define Z_MIN_SPEED 0.1
#define Z_MAX_SPEED 100

/************* END OF Z STEPPER  **************/

/**************** W STEPPER  ******************/

#define W_MIN_SPEED 1
#define W_MAX_SPEED 100

/************* END OF W STEPPER  **************/

#endif // STEPPER_SPEED_CONSTRAINT