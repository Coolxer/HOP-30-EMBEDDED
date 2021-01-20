#ifndef STEPPER_H
#define STEPPER_H

#include "stm32f4xx_hal.h"
#include "endstop.h"

enum State
{
    OFF = 0,
    ON = 1,
    HOMING = 2,
    MOVING = 3,
    PAUSED = 4
};

enum HomeStep
{
    FAST = 0,
    BACKWARD = 1,
    PRECISE = 2
};

typedef struct
{
    uint8_t name[2]; // 2-characters name
    uint8_t *index;  // command index
    uint32_t port;   // stepper gpio port group

    TIM_HandleTypeDef masterTimer; // master timer (structure)
    TIM_HandleTypeDef slaveTimer;  // slave timer (structure)

    uint8_t alternateFunction; // alternate function of step_pin
    uint32_t channel;          // timer channel to which the step_pin is connected
    uint32_t itr;              // ITR macro (on which "port master sends update to slave; port on slave timer")
    uint8_t irq;               // IRQ macro of slave timer

    uint16_t step;   // step pin
    uint16_t dir;    // direction(dir) pin
    uint16_t enable; // enable pin

    uint16_t cnt;    // current slaveTimer counter value
    uint16_t target; // slaveTimer period

    uint16_t minSpeed; // minimum speed of stepper (individually for each axis)
    uint16_t maxSpeed; // maximimum speed of stepper (individually for each axis)

    enum State lastState; // lastState (especially useful in resume function)
    enum State state;     // 0 - off, 1 - on, 2 - home, 3 - move, 4 - paused

    enum HomeStep homeStep;     // 0 - fast, 1 - backward, 2 - precise
    enum HomeStep lastHomeStep; // previos homeStep value to prevent double call same state

    Endstop *minEndstop;
    Endstop *maxEndstop;
} Stepper;

void stepper_init(Stepper *stepper, uint8_t *name, uint32_t port, TIM_TypeDef *masterTimer, TIM_TypeDef *slaveTimer, uint8_t alternateFunction, uint32_t channel, uint32_t itr, uint8_t irq, uint16_t step, uint16_t dir, uint16_t enable, uint16_t minSpeed, uint16_t maxSpeed);
void stepper_assignEndstops(Stepper *stepper, Endstop *min, Endstop *max); // setups endstops to the axis
void stepper_deinit(Stepper *stepper);                                     // stops PWM & disable IRQs

/* PRIVATE */ //void stepper_setupGpio(Stepper* stepper);           /* setups all pins that are in common with stepper */
/* PRIVATE */ //void stepper_setupMasterTimer(Stepper* stepper);    /* setups master timer (with PWM) */
/* PRIVATE */ //void stepper_setupSlaveTimer(Stepper* stepper);     /* setups slave timer (that controls number of steps taken) */
/* PRIVATE */ //void stepper_setupTimers(Stepper* stepper);         /* calls setups timers procedures */

uint8_t stepper_setSpeed(Stepper *stepper, uint8_t *speed); // sets speed of stepper

uint8_t stepper_switch(Stepper *stepper, uint8_t state);   // switch stepper motor depend on state value (0 -> OFF, 1 -> ON)
uint8_t stepper_emergency_shutdown(Stepper *stepper);      // function that allow easily to only TURN OFF all steppers, without condition
uint8_t stepper_home(Stepper *stepper, uint8_t direction); // starts moving stepper motor (can be break by endstop clicked or pause / stop) with given direction
uint8_t stepper_move(Stepper *stepper, uint8_t *steps);    // moves stepper motor by given number of steps (can be break by endstop clicked or pause / stop)

void stepper_setDirection(Stepper *stepper, uint8_t dir); // setups stepper motor direction
void stepper_changeDirection(Stepper *stepper);           // changes stepper motor
void stepper_run(Stepper *stepper);                       // runs stepper motor to move immediately (no given steps)

uint8_t stepper_pause(Stepper *stepper);  // pauses stepper and saves timer parameters to easy resume
uint8_t stepper_resume(Stepper *stepper); // resumes stepper motor, after it was paused
uint8_t stepper_stop(Stepper *stepper);   // stop stepper motor (no saving timer parameters)

void stepper_stopTimers(Stepper *stepper); // stop timers
void stepper_reset(Stepper *stepper);      // reset timers

#endif // STEPPER_H