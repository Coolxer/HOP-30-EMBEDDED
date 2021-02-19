#include "stepper/partial/stepper_configuration.h"

#include <stdlib.h>

#include "counter.h"
#include "stepper/partial/stepper_validator.h"
#include "stepper/partial/stepper_calculator.h"

uint8_t stepper_setSpeed(Stepper *stepper, uint8_t *speedStr)
{
    Speed regs = {0};
    float speed = 0;

    // in 16-bit timer max Period value can reach 65535 if there is need to be LONGER period between steps
    // you need to use change Prescaler too

    // normally greater speed means faster, but there is otherwise, beacuse "speed" meaning period of time
    // so we need to cast this, but not this moment, because it's need to set up clocks frequency
    // and see in real time, what speed we need

    if (!set_speed_validator(stepper, speedStr))
        return 0;

    //sscanf((void *)speedStr, "%f", &speed);
    speed = strtof((void *)speedStr, NULL);

    if (speed < stepper->minSpeed || speed > stepper->maxSpeed) // checks if speed is in range
        return 0;

    regs = calculate_speed(stepper, speed);

    __HAL_TIM_SET_PRESCALER(&stepper->masterTimer, regs.psc);
    __HAL_TIM_SET_AUTORELOAD(&stepper->masterTimer, regs.arr);
    __HAL_TIM_SET_COMPARE(&stepper->masterTimer, stepper->channel, regs.pul); // set pulse width

    return 1;
}

void stepper_setDirection(Stepper *stepper, uint8_t dir)
{
    HAL_GPIO_WritePin((GPIO_TypeDef *)stepper->port, stepper->dir, dir);
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