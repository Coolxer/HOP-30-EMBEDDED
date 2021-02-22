#ifndef STEPPER_CALCULATION
#define STEPPER_CALCULATION

#include <stdint.h>

/************************************* GENERAL ****************************************/

extern const uint8_t STEPPER_STEPS_PER_REVOLUTION;
extern const uint8_t MICROSTEPPING;

extern const uint8_t BIG_GEAR_DIAMETER;
extern const uint8_t SMALL_GEAR_DIAMETER;
extern const float GEARS_PROPORTION;

extern const uint16_t SMALL_GEAR_STEPS_PER_REVOLUTION;

extern const uint16_t STEPS_PER_REVOLUTION;

/********************************** END OF GENERAL ***********************************/

/******************************** LINEAR COMMON AXIS *********************************/

extern const float SMALL_GEAR_CIRCUMFERENCE;

extern const float SG_SPM;

extern const float STEPS_PER_MM;

/*************************** END OF LINEAR COMMON AXIS *******************************/

/***************************** CIRCULAR COMMON AXIS  *********************************/

extern const float SG_SPD;

extern const float STEPS_PER_DEGREE;

/************************** END OF CIRCULAR COMMON AXIS ******************************/

#endif // STEPPER_CALCULATION