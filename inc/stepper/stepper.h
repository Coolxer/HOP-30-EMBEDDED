#ifndef STEPPER_H
#define STEPPER_H

#include "stm32f4xx_hal.h"

#include "enum/axis_type.h"
#include "enum/stepper_state.h"
#include "enum/home_step.h"

#include "endstop/endstop.h"

typedef struct
{
    enum AxisType axisType; // axis type [LINEAR or CIRCULAR]
    uint8_t name[2];        // 2-characters name
    uint8_t *index;         // command index
    uint32_t port;          // stepper gpio port group

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

    enum State state;     // 0 - off, 1 - on, 2 - home, 3 - move, 4 - paused
    enum State lastState; // lastState (especially useful in resume function)

    enum HomeStep homeStep;     // 0 - fast, 1 - backward, 2 - precise
    enum HomeStep lastHomeStep; // previos homeStep value to prevent double call same state

    Endstop *minEndstop;
    Endstop *maxEndstop;
} Stepper;

#endif // STEPPER_H