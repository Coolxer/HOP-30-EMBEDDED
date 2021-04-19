#ifndef ENDSTOP_CONNECTION_H
#define ENDSTOP_CONNECTION_H

#include "stm32f4xx_hal.h"

/*********** X STEPPER ENDSTOPS ***************/

/***** LEFT ENDSTOP *****/

#define XL_PORT GPIOC
#define XL_PIN GPIO_PIN_0
#define XL_IRQ EXTI0_IRQn

/** END OF LEFT ENDSTOP */

/**** RIGHT ENDSTOP *****/

#define XR_PORT GPIOC
#define XR_PIN GPIO_PIN_1
#define XR_IRQ EXTI1_IRQn

/* END OF RIGHT ENDSTOP */

/******** END OF X STEPPER ENDSTOPS ***********/

/*********** Y STEPPER ENDSTOPS ***************/

/***** LEFT ENDSTOP *****/

#define YL_PORT GPIOC
#define YL_PIN GPIO_PIN_2
#define YL_IRQ EXTI2_IRQn

/** END OF LEFT ENDSTOP */

/**** RIGHT ENDSTOP *****/

#define YR_PORT GPIOC
#define YR_PIN GPIO_PIN_3
#define YR_IRQ EXTI3_IRQn

/* END OF RIGHT ENDSTOP */

/******** END OF Y STEPPER ENDSTOPS ***********/

/*********** Z STEPPER ENDSTOPS ***************/

/***** LEFT ENDSTOP *****/

#define ZL_PORT GPIOC
#define ZL_PIN GPIO_PIN_10
#define ZL_IRQ EXTI4_IRQn

/** END OF LEFT ENDSTOP */

/**** RIGHT ENDSTOP *****/

#define ZR_PORT GPIOC
#define ZR_PIN GPIO_PIN_11
#define ZR_IRQ EXTI9_5_IRQn

/* END OF RIGHT ENDSTOP */

/******** END OF Z STEPPER ENDSTOPS ***********/

#endif // ENDSTOP_CONNECTION_H