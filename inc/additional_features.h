#ifndef ADDITIONAL_FEATURES_H
#define ADDITIONAL_FEATURES_H

#include "stm32f4xx_hal.h"

// features that are not implemented yet, but maybe will be (are in GRBLHAL)
// this features required pins so

// TIMER 1
#define SPINDLE_PWM_PORT GPIOB
#define SPINDLE_PWM_PIN GPIO_PIN_1

#define SPINDLE_DIR_PORT GPIOC
#define SPINDLE_DIR_PIN GPIO_PIN_4

// in my case it will be directly to the reset pin (no PORT and no PIN given)
// so there is not software at all

// ping for reset is given to the GRBLHAL
#define RESET_BTN_PORT GPIOA
#define RESET_BTN_PIN GPIO_PIN_1

#define HOLD_BTN_PORT GPIOA
#define HOLD_BTN_PIN GPIO_PIN_4

#define START_BTN_PORT GPIOB
#define START_BTN_PIN GPIO_PIN_0

#define PROBE_PORT GPIOC
#define PROBE_PIN GPIO_PIN_0

#define SAFETY_DOOR_PORT GPIOC
#define SAFETY_DOOR_PIN 8

#endif // ADDITIONAL_FEATURES_H