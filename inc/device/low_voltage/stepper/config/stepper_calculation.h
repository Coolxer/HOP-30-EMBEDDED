#ifndef STEPPER_CALCULATION_H
#define STEPPER_CALCULATION_H

#include <stdint.h>

/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! ATTENTION !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
// float values presented below are given with max 7 digits after comma
// they are just given to show order of magnitude concrete variable
// they are not used in calculations, because of precision
// last-level value is high precision, because it's calculated of no-rounded subvalues
// only last-level value is rounded to minimalize calculation ERRs

/************************************* GENERAL ****************************************/

//#define DEFAULT_STEPS_PER_REVOLUTION 200;
//#define MICROSTEPPING 16;

//#define BIG_GEAR_DIAMETER 95;
//#define SMALL_GEAR_DIAMETER 25;
//#define GEARS_PROPORTION 3.8;

/********************************** END OF GENERAL ***********************************/

#define A_STEPS_PER_DEGREE 80.000
#define X_STEPS_PER_MM 77.000
#define Y_STEPS_PER_MM 77.000
#define Z_STEPS_PER_MM 4600.000

#endif // STEPPER_CALCULATION_H
