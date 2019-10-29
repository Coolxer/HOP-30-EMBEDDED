#ifndef STEPPER_H
#define STEPPER_H

#include <stdbool.h>

#include "device.h"

// TIM2 and TIM5 are 32-bits
// there are 12 others timers which have 16-bits precision
// decided to use TIM2 and TIM5 in main operation and other(16-bit timers) to each another stepper
// for z axis and y axis beacuse they do not need perfect precision

typedef struct
{
    Device device;

    TIM_HandleTypeDef timer; //timer instance
    uint32_t port;        // port group
    
    uint16_t dir_pin;     // direction(dir) pin
    uint16_t step_pin;    // step pin
    uint16_t enable_pin;  // enable pin

    uint16_t m_pins[3];  // microstepping pins

    uint8_t state;
}Stepper;

Stepper *stepper;

Stepper *stepper_init(uint8_t *_name, TIM_TypeDef *_instance, uint32_t _port, uint16_t _dir_pin, uint16_t _step_pin, uint16_t _enable_pin, uint16_t _m1, uint16_t _m2, uint16_t _m3);
void stepper_deinit();
void stepper_setup_gpio(); // setups gpio pins
void stepper_setup_timer();

bool stepper_set_microstepping(uint8_t *states); // set microstepping of stepper
void stepper_set_speed(uint8_t speed); // set speed of stepper

bool stepper_toggle(); // toggle stepper motor
bool stepper_move(uint8_t steps); // move stepper motor by given number of steps
bool stepper_home(); // move stepper motor by small step count unit signal detected

void TIM3_IRQHandler(void);
void TIM4_IRQHandler(void);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

#endif // STEPPER_H