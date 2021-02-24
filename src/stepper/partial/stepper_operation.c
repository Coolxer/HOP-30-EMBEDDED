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
    uint8_t invalid = validate_switch(stepper, state);

    if (invalid)
        return invalid;

    uint8_t _state = 0;

    sscanf((void *)state, "%hhu", &_state); // str to uint

    if (stepper->instance.state != _state) // check if state is not currently exists
    {
        HAL_GPIO_WritePin((GPIO_TypeDef *)stepper->hardware.port, stepper->hardware.enable, _state == 0 ? 0 : 1); // switches the stepper (OFF or ON)
        stepper->instance.state = _state;                                                                         // update stepper state
    }

    return ERR.NO_ERROR;
}

void stepper_startMoving(Stepper *stepper)
{
    if (stepper->instance.state == OFF)
        stepper_switch(stepper, (uint8_t *)"1");

    HAL_TIM_Base_Start_IT(&stepper->hardware.slaveTimer);                         // starts counting of PWM cycles
    HAL_TIM_PWM_Start(&stepper->hardware.masterTimer, stepper->hardware.channel); // starts moving

    stepper->instance.state = MOVING; // update stepper state
}

void stepper_moveEssential(Stepper *stepper, float way, uint8_t *direction)
{
    Way params = calculate_way(stepper->info.axisType, way);

    stepper_setDirection(stepper, direction);

    params.laps = 1;
    params.arr = 3;

    // TIM2 and TIM5 are 32-bit timers and there is something like, that i need to decrease arr for them
    if (stepper->hardware.slaveTimer.Instance == TIM2 || stepper->hardware.slaveTimer.Instance == TIM5)
        params.arr--;

    if (params.laps > 0)
    {
        __HAL_TIM_SET_AUTORELOAD(&stepper->hardware.slaveTimer, 5 - 1); // set target value //MAX_16BIT_VALUE // -1 only for TiM2, tim5
        params.laps--;
    }
    else
    {
        __HAL_TIM_SET_AUTORELOAD(&stepper->hardware.slaveTimer, params.arr); // set target value // -1 only for TiM2, tim5
        params.arr = 0;
    }

    stepper->instance.movement.way = params;

    stepper_startMoving(stepper);
}

uint8_t stepper_home(Stepper *stepper, uint8_t *direction)
{
    uint8_t invalid = validate_home(stepper, direction);

    if (invalid)
        return invalid;

    if (stepper->instance.homeStep == FAST)
    {
        if (!endstop_isClicked(stepper->minEndstop))
        {
            stepper_setSpeedEssential(stepper, 10.0f); // home with low speed
            stepper_setDirection(stepper, direction);  // set left direction
            stepper_run(stepper);                      // start motor moving

            stepper->instance.state = HOMING; // update stepper state
            stepper->instance.lastHomeStep = FAST;
        }
    }
    else if (stepper->instance.homeStep == BACKWARD)
    {
        //counter_count(65000); // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! HERE !!!!!!!!!!!!!!!!!!!!!
        stepper->instance.state = ON;
        stepper_moveEssential(stepper, 10.0f, (uint8_t *)"0");

        stepper->instance.lastHomeStep = BACKWARD;
    }
    else
    {
        //HAL_Delay(150);
        stepper_setSpeedEssential(stepper, 1.0f);
        stepper_changeDirection(stepper);
        stepper_run(stepper);

        stepper->instance.state = HOMING;
        stepper->instance.lastHomeStep = PRECISE;
    }

    return ERR.NO_ERROR;
}

uint8_t stepper_move(Stepper *stepper, uint8_t *way, uint8_t *direction)
{
    uint8_t invalid = validate_move(stepper, way, direction);

    if (invalid)
        return invalid;

    float _way = strtof((void *)way, NULL);

    stepper_moveEssential(stepper, _way, direction);

    return ERR.NO_ERROR;
}

void stepper_run(Stepper *stepper)
{
    if (stepper->instance.state == OFF)
        stepper_switch(stepper, (uint8_t *)"1");

    HAL_TIM_PWM_Start(&stepper->hardware.masterTimer, stepper->hardware.channel); // starts moving
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