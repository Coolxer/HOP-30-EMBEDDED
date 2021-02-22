#include "stepper/partial/stepper_configuration.h"

#include <stdlib.h>
#include <string.h>

#include "counter.h"
#include "command/partial/err.h"

#include "stepper/partial/stepper_validator.h"
#include "stepper/partial/stepper_calculator.h"

uint8_t stepper_setSpeed(Stepper *stepper, uint8_t *speed)
{
    Speed regs = {0};
    float _speed = 0;

    // in 16-bit timer max Period value can reach 65535 if there is need to be LONGER period between steps
    // you need to use change Prescaler too

    // normally greater speed means faster, but there is otherwise, beacuse "speed" meaning period of time
    // so we need to cast this, but not this moment, because it's need to set up clocks frequency
    // and see in real time, what speed we need

    uint8_t invalid = setSpeed_validator(speed);

    if (invalid)
        return invalid;

    _speed = strtof((void *)speed, NULL);

    if (_speed < stepper->minSpeed || _speed > stepper->maxSpeed) // checks if speed is in range
        return ERR.INVALID_SPEED_VALUE;

    regs = calculate_speed(stepper, _speed);

    __HAL_TIM_SET_PRESCALER(&stepper->masterTimer, regs.psc);
    __HAL_TIM_SET_AUTORELOAD(&stepper->masterTimer, regs.arr);
    __HAL_TIM_SET_COMPARE(&stepper->masterTimer, stepper->channel, regs.pul); // set pulse width

    return ERR.NO_ERROR;
}

void stepper_setDirection(Stepper *stepper, uint8_t *direction)
{
    HAL_GPIO_WritePin((GPIO_TypeDef *)stepper->port, stepper->dir, strcmp((void *)direction, "0") == 0 ? 0 : 1);
    counter_count(5); // need wait minimum 5us after set direction before go
}

void stepper_changeDirection(Stepper *stepper)
{
    HAL_GPIO_TogglePin((GPIO_TypeDef *)stepper->port, stepper->dir);
    counter_count(5); // need wait minimum 5us after change direction before go
}

void stepper_stopTimers(Stepper *stepper)
{
    HAL_TIM_PWM_Stop(&stepper->masterTimer, stepper->channel); // stop masterTimer

    if (stepper->state == MOVING)                   // check if stepper is in MOVING state i need to stop slaveTimer too
        HAL_TIM_Base_Stop_IT(&stepper->slaveTimer); // stop slaveTimer

    stepper_reset(stepper); // reset stepper
}

void stepper_reset(Stepper *stepper)
{
    stepper->state = ON; // reset state of motor

    __HAL_TIM_SET_COUNTER(&stepper->slaveTimer, 0);  // reset slaveTimer counter
    __HAL_TIM_SET_COUNTER(&stepper->masterTimer, 0); // reset masterTimer counter

    __HAL_TIM_CLEAR_FLAG(&stepper->slaveTimer, TIM_SR_UIF);  // clear interrupt flag
    __HAL_TIM_CLEAR_IT(&stepper->slaveTimer, TIM_IT_UPDATE); // clear update_flag
}