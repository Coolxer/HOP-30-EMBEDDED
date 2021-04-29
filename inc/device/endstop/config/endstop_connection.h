#ifndef ENDSTOP_CONNECTION_H
#define ENDSTOP_CONNECTION_H

#include "stm32f4xx_hal.h"

// PIN is NO (Normally Open)
// Second one is connected to GND

/*********** X STEPPER ENDSTOPS ***************/

/***** MIN ENDSTOP *****/

#define XL_PORT GPIOC
#define XL_PIN GPIO_PIN_10
#define XL_IRQ EXTI0_IRQn

/** END OF MIN ENDSTOP */

/**** MAX ENDSTOP *****/

#define XR_PORT GPIOC
#define XR_PIN GPIO_PIN_12
#define XR_IRQ EXTI1_IRQn

/* END OF MAX ENDSTOP */

/******** END OF X STEPPER ENDSTOPS ***********/

/*********** Y STEPPER ENDSTOPS ***************/

/***** MIN ENDSTOP *****/

#define YL_PORT GPIOB
#define YL_PIN GPIO_PIN_7
#define YL_IRQ EXTI2_IRQn

/** END OF MIN ENDSTOP */

/**** MAX ENDSTOP *****/

#define YR_PORT GPIOC
#define YR_PIN GPIO_PIN_13
#define YR_IRQ EXTI3_IRQn

/* END OF MAX ENDSTOP */

/******** END OF Y STEPPER ENDSTOPS ***********/

/*********** Z STEPPER ENDSTOPS ***************/

/***** MIN ENDSTOP *****/

#define ZL_PORT GPIOC
#define ZL_PIN GPIO_PIN_2
#define ZL_IRQ EXTI4_IRQn

/** END OF MIN ENDSTOP */

/**** MAX ENDSTOP *****/

#define ZR_PORT GPIOC
#define ZR_PIN GPIO_PIN_3
#define ZR_IRQ EXTI9_5_IRQn

/* END OF MAX ENDSTOP */

/******** END OF Z STEPPER ENDSTOPS ***********/

#endif // ENDSTOP_CONNECTION_H