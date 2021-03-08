#include "device/stepper/config/stepper_calculation.h"

/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! ATTENTION !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
// float values presented below are given with max 7 digits after comma
// they are just given to show order of magnitude concrete variable
// they are not used in calculations, because of precision
// last-level value is high precision, because it's calculated of no-rounded subvalues
// only last-level value is rounded to minimalize calculation ERRs

/************************************* GENERAL ****************************************/

const uint8_t STEPPER_STEPS_PER_REVOLUTION = 200; // given by manufacturer
const uint8_t MICROSTEPPING = 16;                 // set up on stepper driver DIP switch

const uint8_t BIG_GEAR_DIAMETER = 95;
const uint8_t SMALL_GEAR_DIAMETER = 25;
const float GEARS_PROPORTION = 3.8f; // BIG_GEAR_DIAMETER / SMALL_GEAR_DIAMETER

// steps that have to been done by stepper(small gear) to full rotate (360 deg.) itself (around)
const uint16_t SMALL_GEAR_STEPS_PER_REVOLUTION = 3200; // STEPPER_STEPS_PER_REVOLUTION * MICROSTEPPING

// steps that have to been done by stepper(small gear) to full rotate (360 deg.) BIG GEAR
// how many steps need to rotate by 360 deg. on BIG GEAR ? [REAL]
const uint16_t STEPS_PER_REVOLUTION = 12160; // SMALL_GEAR_STEPS_PER_REVOLUTION * GEARS_PROPORTION

/********************************** END OF GENERAL ***********************************/

/******************************** LINEAR COMMON AXIS *********************************/

const float SMALL_GEAR_CIRCUMFERENCE = 78.5398163f; // 2 * PI * R = PI * SMALL_GEAR_DIAMETER

/*
    [how many steps need]           [to move by given mm]
    SMALL_GEAR_STEPS_PER_REVOLUTION <-> SMALL_GEAR_CIRCUMFERENCE
    [full rotate (360 deg. = 3200) makes almost 79mm movement just on SMALL_GEAR]
*/

// how many steps need to move by 1 mm just on SMALL GEAR ?
const float SG_SPM = 40.7436654f; // SMALL_GEAR_STEPS_PER_REVOLUTION / SMALL_GEAR_CIRCUMFERENCE

// how many steps need to move by 1 mm on BIG GEAR ? [REAL]
const float STEPS_PER_MM = 154.8259286f; // SG_SPM * GEARS_PROPORTION

/*************************** END OF LINEAR COMMON AXIS *******************************/

/***************************** CIRCULAR COMMON AXIS  *********************************/

/*
    [how many steps need]           [to move by given degrees]
    SMALL_GEAR_STEPS_PER_REVOLUTION <-> 360 deg.
*/

// how many steps need to rotate by 1 deg. just on SMALL GEAR ?
const float SG_SPD = 8.8888888f; // SMALL_GEAR_STEPS_PER_REVOLUTION / 360

// how many steps need to rotate by 1 deg. on BIG GEAR ? [REAL]
const float STEPS_PER_DEGREE = 33.7777778f; // SG_SPD * GEARS_PROPORTION

/************************** END OF CIRCULAR COMMON AXIS ******************************/