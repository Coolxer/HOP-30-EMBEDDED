#ifndef ADDITIONAL_FEATURES_H
#define ADDITIONAL_FEATURES_H

#include "stm32f4xx_hal.h"

// features that are not implemented yet, but maybe will be (are in GRBLHAL)
// this features required pins so

#define SPINDLE_PWM_PORT GPIOB
#define SPINDLE_PWM_PIN 1

#define SPINDLE_DIR_PORT GPIOC
#define SPINDLE_DIR_PIN 4

// in my case it will be directly to the reset pin (no PORT and no PIN given)
// so there is not software at all

// ping for reset is given to the GRBLHAL
#define RESET_BTN_PORT GPIOA
#define RESET_BTN_PIN 1

#define HOLD_BTN_PORT GPIOA
#define HOLD_BTN_PIN 4

#define START_BTN_PORT GPIOB
#define START_BTN_PIN 0

#define PROBE_PORT GPIOC
#define PROBE_PIN 0

#endif // ADDITIONAL_FEATURES_H