#ifndef STEPPER_HARDWARE_H
#define STEPPER_HARDWARE_H

#include "stm32f4xx_hal.h"

typedef struct
{
    TIM_HandleTypeDef masterTimer; // master timer (structure)
    TIM_HandleTypeDef slaveTimer;  // slave timer (structure)

    uint8_t alternateFunction; // alternate function of step_pin
    uint32_t channel;          // timer channel to which the step_pin is connected
    uint32_t itr;              // ITR macro (on which "port master sends update to slave; port on slave timer")

    uint8_t irq; // IRQ macro of slave timer

    GPIO_TypeDef *enablePort;
    uint16_t enablePin;

    GPIO_TypeDef *stepPort;
    uint16_t stepPin;

    GPIO_TypeDef *dirPort;
    uint16_t dirPin;
} Hardware;

Hardware stepper_hardware_init(TIM_TypeDef *masterTimer, TIM_TypeDef *slaveTimer, uint8_t alternateFunction, uint32_t channel, uint32_t itr, uint8_t irq,
                               GPIO_TypeDef *enablePort, uint16_t enablePin, GPIO_TypeDef *stepPort, uint16_t stepPin, GPIO_TypeDef *dirPort, uint16_t dirPin);

#endif // STEPPER_HARDWARE_H