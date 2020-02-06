#ifndef STEPPER_H
#define STEPPER_H

#include "stm32f4xx_hal.h"

typedef struct
{
    uint8_t name[2];                // 2-characters name
    uint32_t port;                  // stepper gpio port group

    TIM_HandleTypeDef masterTimer;  // master timer (structure)             
    TIM_HandleTypeDef slaveTimer;   // slave timer (structure)

    uint8_t alternateFunction;      // alternate function of step_pin
    uint32_t channel;               // timer channel to which the step_pin is connected    
    uint32_t itr;                   // ITR macro (on which "port master sends update to slave, port on slave timer")
    uint8_t irq;                    // IRQ macro of slave timer

    uint16_t step;                  // step pin
    uint16_t dir;                   // direction(dir) pin
    uint16_t enable;                // enable pin

    uint16_t m[3];                  // microstepping pins   
}Stepper;

Stepper* stepper_init(Stepper* stepper, uint8_t* name, uint32_t port, TIM_TypeDef* masterTimer, TIM_TypeDef* slaveTimer, uint8_t alternateFunction, uint32_t channel, uint32_t itr, uint8_t irq, uint16_t step, uint16_t dir, uint16_t enable, uint16_t m1, uint16_t m2, uint16_t m3);
void stepper_deinit(Stepper* stepper); // stops PWM & disable IRQs

/* PRIVATE */   //void stepper_setup_gpio(Stepper* stepper);            /* setups all pins that are in common with stepper */
/* PRIVATE */   //void stepper_setup_master_timer(Stepper* stepper);    /* setups master timer (with PWM) */
/* PRIVATE */   //void stepper_setup_slave_timer(Stepper* stepper);     /* setups slave timer (that controls number of steps taken) */            
/* PRIVATE */   //void stepper_setup_timers(Stepper* stepper);          /* calls setups timers procedures */

uint8_t stepper_set_microstepping(Stepper* stepper, uint8_t* states);   // sets microstepping of stepper
uint8_t stepper_set_speed(Stepper* stepper, uint8_t* speed);            // sets speed of stepper

uint8_t stepper_switch(Stepper* stepper, uint8_t* state);               // switch stepper motor depend on state value (0 -> OFF, 1 -> ON)
uint8_t stepper_move(Stepper* stepper, uint8_t* steps);                 // moves stepper motor by given number of steps
void stepper_home(Stepper* stepper);                                    // moves stepper motor until endstop signal detected


#endif // STEPPER_H