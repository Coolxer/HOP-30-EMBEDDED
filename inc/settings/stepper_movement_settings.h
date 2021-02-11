#ifndef STEPPER_MOVEMENT_SETTINGS
#define STEPPER_MOVEMENT_SETTINGS

/************************************* GENERAL ****************************************/

#define STEPPER_STEPS_PER_REVOLUTION 200
#define MICROSTEPPING 8

#define SMALL_GEAR_DIAMETER 25
#define BIG_GEAR_DIAMETER 95
#define GEARS_PROPORTION 3.8 // BIG_GEAR_DIAMETER / SMALL_GEAR_DIAMETER

#define BIG_GEAR_STEPS_PER_REVOLUTION 6080 // STEPPER_STEPS_PER_REVOLUTION * MICROSTEPPIONG * GEARS_PROPORTION

/********************************** END OF GENERAL ***********************************/

/******************************** LINEAR COMMON AXIS *********************************/

#define BIG_GEAR_CIRCUMFERENCE 298.451302091 // 2 * PI * R = PI * BIG_GEAR_DIAMETER

/*
    [how many steps need]           [to move by given mm]
    BIG_GEAR_STEPS_PER_REVOLUTION <-> BIG_GEAR_CIRCUMFERENCE
    [full rotate (360 deg. = 6080 steps) makes almost 300mm movement]
*/

// how many steps steps need to move by 1 mm ?
#define STEPS_PER_MM 20.371832716 // BIG_GEAR_STEPS_PER_REVOLUTION / BIG_GEAR_CIRCUMFERENCE

// ATTENTION!
// MIN and MAX speed presented below are given in mm/s

/*************************** END OF LINEAR COMMON AXIS *******************************/

/***************************** CIRCULAR COMMON AXIS  *********************************/

/*
    [how many steps need]           [to move by given degrees]
    BIG_GEAR_STEPS_PER_REVOLUTION <-> 360 deg.
*/

#define STEPS_PER_DEGREE 16.888888889 // BIG_GEAR_STEPS_PER_REVOLUTION / 360

// ATTENTION!
// MIN and MAX speed presented below are given in rps [rotate per second]

/************************** END OF CIRCULAR COMMON AXIS ******************************/

/************************** INDIVIDUAL STEPPER SETTINGS ******************************/

/**************** X STEPPER  ******************/
#define X_MIN_SPEED 1
#define X_MAX_SPEED 8
/************* END OF X STEPPER  **************/

/**************** Y STEPPER  ******************/
#define Y_MIN_SPEED 1
#define Y_MAX_SPEED 849
/************* END OF Y STEPPER  **************/

/**************** Z STEPPER  ******************/
#define Z_MIN_SPEED 1
#define Z_MAX_SPEED 849
/************* END OF Z STEPPER  **************/

/**************** W STEPPER  ******************/
#define W_MIN_SPEED 1
#define W_MAX_SPEED 849
/************* END OF W STEPPER  **************/

#endif // STEPPER_MOVEMENT_SETTINGS