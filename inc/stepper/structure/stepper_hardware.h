#ifndef STEPPER_HARDWARE_H
#define STEPPER_HARDWARE_H

#include "stm32f4xx_hal.h"

typedef struct
{
    GPIO_TypeDef *port; // stepper gpio port group

    TIM_HandleTypeDef masterTimer; // master timer (structure)
    TIM_HandleTypeDef slaveTimer;  // slave timer (structure)

    uint8_t alternateFunction; // alternate function of step_pin
    uint32_t channel;          // timer channel to which the step_pin is connected
    uint32_t itr;              // ITR macro (on which "port master sends update to slave; port on slave timer")
    uint8_t irq;               // IRQ macro of slave timer

    uint16_t step;   // step pin
    uint16_t dir;    // direction(dir) pin
    uint16_t enable; // enable pin
} Hardware;

Hardware stepper_hardware_init(GPIO_TypeDef *port, TIM_TypeDef *masterTimer, TIM_TypeDef *slaveTimer, uint8_t alternateFunction, uint32_t channel, uint32_t itr, uint8_t irq, uint16_t step, uint16_t dir, uint16_t enable);

#endif // STEPPER_HARDWARE_H