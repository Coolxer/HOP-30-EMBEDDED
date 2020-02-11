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

    uint16_t cnt;                   // current slaveTimer counter value
    uint16_t target;                // slaveTimer period

    uint8_t stEnabled;
}Stepper;

Stepper* stepper_init(Stepper *stepper, uint8_t *name, uint32_t port, TIM_TypeDef *masterTimer, TIM_TypeDef *slaveTimer, uint8_t alternateFunction, uint32_t channel, uint32_t itr, uint8_t irq, uint16_t step, uint16_t dir, uint16_t enable, uint16_t m1, uint16_t m2, uint16_t m3);
void stepper_deinit(Stepper *stepper); // stops PWM & disable IRQs

/* PRIVATE */   //void stepper_setupGpio(Stepper* stepper);            /* setups all pins that are in common with stepper */
/* PRIVATE */   //void stepper_setupMasterTimer(Stepper* stepper);    /* setups master timer (with PWM) */
/* PRIVATE */   //void stepper_setupSlaveTimer(Stepper* stepper);     /* setups slave timer (that controls number of steps taken) */            
/* PRIVATE */   //void stepper_setupTimers(Stepper* stepper);          /* calls setups timers procedures */

uint8_t stepper_setMicrostepping(Stepper *stepper, uint8_t *states);    // sets microstepping of stepper
uint8_t stepper_setSpeed(Stepper *stepper, uint8_t *speed);             // sets speed of stepper

uint8_t stepper_switch(Stepper *stepper, uint8_t *state);               // switch stepper motor depend on state value (0 -> OFF, 1 -> ON)
void stepper_home(Stepper *stepper);                                    // moves stepper motor until endstop signal detected
uint8_t stepper_move(Stepper *stepper, uint8_t *steps);                 // moves stepper motor by given number of steps

uint8_t stepper_setDirection(Stepper *stepper, uint8_t *dir);               // setups stepper motor direction
void stepper_changeDirection(Stepper *stepper);                         // changes stepper motor 

void stepper_run(Stepper *stepper);                                     // runs stepper motor to move immediately (no given steps)

uint8_t stepper_pause(Stepper *stepper, uint8_t *mode);                     // pauses stepper and saves timer parameters to easy resume
uint8_t stepper_resume(Stepper *stepper, uint8_t *mode);                    // resumes stepper motor, after it was paused
uint8_t stepper_stop(Stepper *stepper, uint8_t *mode);                      // stop stepper motor (no saving timer parameters)

#endif // STEPPER_H