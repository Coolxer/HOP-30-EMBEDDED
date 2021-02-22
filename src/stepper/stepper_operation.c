#include "stepper/partial/stepper_operation.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "counter.h"
#include "command/partial/err.h"

#include "stepper/config/stepper_calculation.h"

#include "stepper/partial/stepper_calculator.h"
#include "stepper/partial/stepper_configuration.h"
#include "stepper/partial/stepper_validator.h"
#include "endstop/partial/endstop_operation.h"

uint8_t stepper_switch(Stepper *stepper, uint8_t *state)
{
    uint8_t invalid = switch_validator(stepper, state);

    if (invalid)
        return invalid;

    uint8_t _state = 0;

    sscanf((void *)state, "%hhu", &_state); // str to uint

    if (stepper->state != _state) // check if state is not currently exists
    {
        HAL_GPIO_WritePin((GPIO_TypeDef *)stepper->port, stepper->enable, _state == 0 ? 0 : 1); // switches the stepper (OFF or ON)
        stepper->state = _state;                                                                // update stepper state
    }

    return ERR.NO_ERROR;
}

uint8_t stepper_home(Stepper *stepper, uint8_t *direction)
{
    uint8_t invalid = home_validator(stepper, direction);

    if (invalid)
        return invalid;

    if (stepper->homeStep == FAST)
    {
        if (!endstop_isClicked(stepper->minEndstop))
        {
            stepper_setSpeed(stepper, (uint8_t *)"10"); // home with low speed
            stepper_setDirection(stepper, direction);   // set left direction
            stepper_run(stepper);                       // start motor moving

            stepper->state = HOMING; // update stepper state
            stepper->lastHomeStep = FAST;
        }
    }
    else if (stepper->homeStep == BACKWARD)
    {
        //counter_count(65000); // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! HERE !!!!!!!!!!!!!!!!!!!!!
        stepper->state = ON;
        stepper_move(stepper, (uint8_t *)"10", (uint8_t *)"0");

        stepper->lastHomeStep = BACKWARD;
    }
    else
    {
        //HAL_Delay(150);
        stepper_setSpeed(stepper, (uint8_t *)"1");
        stepper_changeDirection(stepper);
        stepper_run(stepper);

        stepper->state = HOMING;
        stepper->lastHomeStep = PRECISE;
    }

    return ERR.NO_ERROR;
}

uint8_t stepper_move(Stepper *stepper, uint8_t *way, uint8_t *direction)
{
    uint8_t invalid = move_validator(stepper, way, direction);

    if (invalid)
        return invalid;

    uint16_t steps = 0;
    float _way = 0;

    _way = strtof((void *)way, NULL);

    if (_way == 0) // if way is equals to 0, ERR, because there is no move
        return ERR.INVALID_WAY_VALUE;

    stepper_setDirection(stepper, direction);

    steps = calculate_steps(stepper, _way);

    if (steps == 1) // this is weird situation if we want to move by 1 step, i need to set counter to 1
        __HAL_TIM_SET_COUNTER(&stepper->slaveTimer, 1);
    else
    {
        if (stepper->slaveTimer.Instance == TIM2 || stepper->slaveTimer.Instance == TIM5) // TIM2 and TIM5 are 32-bit timers and there is something like, that i need to decrease steps for them
            steps -= 1;
    }

    __HAL_TIM_SET_AUTORELOAD(&stepper->slaveTimer, steps); // set target value

    if (stepper->state == OFF)
        stepper_switch(stepper, (uint8_t *)"1");

    HAL_TIM_Base_Start_IT(&stepper->slaveTimer);                // starts counting of PWM cycles
    HAL_TIM_PWM_Start(&stepper->masterTimer, stepper->channel); // starts moving

    stepper->state = MOVING; // update stepper state

    return ERR.NO_ERROR;
}

void stepper_run(Stepper *stepper)
{
    if (stepper->state == OFF)
        stepper_switch(stepper, (uint8_t *)"1");

    HAL_TIM_PWM_Start(&stepper->masterTimer, stepper->channel); // starts moving
}

/*
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == TIM3)
	{
		//TIM3->ARR = v;
		//TIM3->CCR1 = v / 2;
	}
}
*/