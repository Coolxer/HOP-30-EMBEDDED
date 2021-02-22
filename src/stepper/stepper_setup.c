#include "stepper/partial/stepper_setup.h"

#include <stddef.h> // includes NULL value
#include <string.h>

#include "stepper/partial/stepper_peripheral.h"

void stepper_init(Stepper *stepper, enum AxisType axisType, uint8_t *name, GPIO_TypeDef *port, TIM_TypeDef *masterTimer, TIM_TypeDef *slaveTimer, uint8_t alternateFunction, uint32_t channel, uint32_t itr, uint8_t irq, uint16_t step, uint16_t dir, uint16_t enable, float minSpeed, float maxSpeed)
{
    stepper->axisType = axisType;
    strcpy((void *)stepper->name, (void *)name);

    stepper->port = port;

    stepper->masterTimer.Instance = masterTimer;
    stepper->slaveTimer.Instance = slaveTimer;

    stepper->alternateFunction = alternateFunction;
    stepper->channel = channel;
    stepper->itr = itr;
    stepper->irq = irq;

    stepper->step = step;
    stepper->dir = dir;
    stepper->enable = enable;

    stepper->lastState = stepper->state = OFF; // reset stepper state
    stepper->homeStep = FAST;
    stepper->lastHomeStep = PRECISE; // init value antything, just different than homeStep

    stepper->minSpeed = minSpeed;
    stepper->maxSpeed = maxSpeed;

    stepper->minEndstop = stepper->maxEndstop = NULL;

    stepper->state = OFF;

    stepper_setup_peripherals(stepper);
}

void stepper_assignEndstops(Stepper *stepper, Endstop *min, Endstop *max)
{
    stepper->minEndstop = min;
    stepper->maxEndstop = max;
}

void stepper_deinit(Stepper *stepper)
{
    HAL_TIM_PWM_Stop(&stepper->masterTimer, stepper->channel);
    HAL_TIM_Base_Stop_IT(&stepper->slaveTimer);
    HAL_NVIC_DisableIRQ(stepper->irq);
}