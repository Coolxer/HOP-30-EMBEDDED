#ifndef STEPPER_H
#define STEPPER_H

#include <stdbool.h>

#include "device.h"

typedef struct
{
    Device device;                               // device instance

    TIM_HandleTypeDef timer;                     // timer instance
    uint8_t alternate;                           // alternate function of step_pin
    uint32_t channel;                            // timer channel to which the step_pin is connected
    uint32_t port;                               // stepper gpio port group
    
    uint16_t dir_pin;                            // direction(dir) pin
    uint16_t step_pin;                           // step pin
    uint16_t enable_pin;                         // enable pin

    uint16_t m_pins[3];                          // microstepping pins

    GPIO_PinState state;                         // stepper current power state
   
}Stepper;

Stepper *stepper;                               // stepper pointer, using to make operations on actual selected stepper

Stepper *stepper_init(uint8_t *_name, TIM_TypeDef *_timer, uint8_t _alternate, uint32_t _channel, uint32_t _port, uint16_t _dir_pin, uint16_t _step_pin, uint16_t _enable_pin, uint16_t _m1, uint16_t _m2, uint16_t _m3); // stepper "constructor" function

/* PRIVATE */   //void stepper_setup_gpio();                       // setups gpio pins
/* PRIVATE */   //void stepper_setup_master_timer();   
/* PRIVATE */   //void stepper_setup_slave_timer();            
/* PRIVATE */   //void stepper_setup_timers();

bool stepper_set_microstepping(uint8_t *states); // sets microstepping of stepper
void stepper_set_speed(uint8_t speed);           // sets speed of stepper

bool stepper_switch(uint8_t *state);             // switch stepper motor depend on state value (0 -> OFF, 1 -> ON)
void stepper_move(uint8_t steps);                // moves stepper motor by given number of steps
void stepper_home();                             // moves stepper motor unit endstop signal detected

#endif // STEPPER_H