#ifndef STEPPER_H
#define STEPPER_H

#include <stdint.h> // includes uint8_t, uint16_t data types
#include <stdbool.h>
#include "stm32f4xx_hal.h"

// TIM2 and TIM5 are 32-bits
// there are 12 others timers which have 16-bits precision
// decided to use TIM2 and TIM5 in main operation and other(16-bit timers) to each another stepper
// for z axis and y axis beacuse they do not need perfect precision

struct Stepper
{
    uint8_t name[2];      // 2-character stepper name (id)

    TIM_HandleTypeDef timer; //timer instance
    uint32_t port;        // port group
    
    uint16_t dir_pin;     // direction(dir) pin
    uint16_t step_pin;    // step pin
    uint16_t enable_pin;  // enable pin

    uint16_t m_pins[3];  // microstepping pins

    uint16_t endstop_pin; // associated endstop pin
};

void stepper_init(struct Stepper *s, uint8_t *_name, TIM_TypeDef *_instance, uint32_t _port, uint16_t _dir_pin, uint16_t _step_pin, uint16_t _enable_pin, uint16_t _m1, uint16_t _m2, uint16_t _m3, uint16_t _endstop_pin);
void stepper_setup_gpio(struct Stepper *s); // setups gpio pins
void stepper_setup_timer(struct Stepper *s);


bool stepper_set_microstepping(struct Stepper *s, uint8_t *states); // set microstepping of stepper
void stepper_set_speed(struct Stepper *s, uint8_t speed); // set speed of stepper

bool stepper_toggle(struct Stepper *s); // toggle stepper motor
bool stepper_move_by_steps(uint8_t steps); // move stepper motor by given number of steps
bool stepper_move_until(); // move stepper motor by small step count unit signal detected


#endif // STEPPER_H