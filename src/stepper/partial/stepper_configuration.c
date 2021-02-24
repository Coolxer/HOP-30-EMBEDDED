#include "stepper/partial/stepper_configuration.h"

#include <stdlib.h>
#include <string.h>

#include "counter.h"
#include "command/partial/err.h"

#include "stepper/partial/stepper_validator.h"
#include "stepper/partial/stepper_calculator.h"

uint8_t stepper_setSpeed(Stepper *stepper, uint8_t *speed)
{
    // in 16-bit timer max Period value can reach 65535 if there is need to be LONGER period between steps
    // you need to use change Prescaler too

    // normally greater speed means faster, but there is otherwise, beacuse "speed" meaning period of time
    // so we need to cast this, but not this moment, because it's need to set up clocks frequency
    // and see in real time, what speed we need

    uint8_t invalid = validate_setSpeed(stepper, speed);

    if (invalid)
        return invalid;

    float _speed = strtof((void *)speed, NULL);

    stepper_setSpeedEssential(stepper, _speed);

    return ERR.NO_ERROR;
}

void stepper_setSpeedEssential(Stepper *stepper, float speed)
{
    Speed regs = calculate_speed(stepper->info.axisType, speed);

    __HAL_TIM_SET_PRESCALER(&stepper->hardware.masterTimer, regs.psc);
    __HAL_TIM_SET_AUTORELOAD(&stepper->hardware.masterTimer, regs.arr);
    __HAL_TIM_SET_COMPARE(&stepper->hardware.masterTimer, stepper->hardware.channel, regs.pul); // set pulse width
}

void stepper_setDirection(Stepper *stepper, uint8_t *direction)
{
    HAL_GPIO_WritePin((GPIO_TypeDef *)stepper->hardware.port, stepper->hardware.dir, strcmp((void *)direction, "0") == 0 ? 0 : 1);
    counter_count(5); // need wait minimum 5us after set direction before go
}

void stepper_changeDirection(Stepper *stepper)
{
    HAL_GPIO_TogglePin((GPIO_TypeDef *)stepper->hardware.port, stepper->hardware.dir);
    counter_count(5); // need wait minimum 5us after change direction before go
}

void stepper_stopTimers(Stepper *stepper)
{
    HAL_TIM_PWM_Stop(&stepper->hardware.masterTimer, stepper->hardware.channel); // stop masterTimer

    if (stepper->instance.state == MOVING)                   // check if stepper is in MOVING state i need to stop slaveTimer too
        HAL_TIM_Base_Stop_IT(&stepper->hardware.slaveTimer); // stop slaveTimer

    //stepper_resetTimers(stepper); // reset stepper

    //stepper->instance.state = ON; // reset state of motor
}

void stepper_resetTimers(Stepper *stepper)
{
    __HAL_TIM_SET_COUNTER(&stepper->hardware.slaveTimer, 0);  // reset slaveTimer counter
    __HAL_TIM_SET_COUNTER(&stepper->hardware.masterTimer, 0); // reset masterTimer counter

    //__HAL_TIM_CLEAR_FLAG(&stepper->hardware.slaveTimer, TIM_SR_UIF);  // clear interrupt flag
    //_HAL_TIM_CLEAR_IT(&stepper->hardware.slaveTimer, TIM_IT_UPDATE); // clear update_flag
}