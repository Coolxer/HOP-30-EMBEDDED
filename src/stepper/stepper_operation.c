#include "stepper/partial/stepper_operation.h"

#include <string.h>
#include <stdlib.h>
#include <inttypes.h>

#include "counter.h"
#include "stepper/partial/stepper_configuration.h"
#include "stepper/partial/stepper_validator.h"
#include "endstop/partial/endstop_operation.h"

uint8_t stepper_switch(Stepper *stepper, uint8_t state)
{
    if (!switch_validator(stepper))
        return 0;

    if (stepper->state != state) // check if state is not currently exists
    {
        HAL_GPIO_WritePin((GPIO_TypeDef *)stepper->port, stepper->enable, state == 0 ? 1 : 0); // switches the stepper (OFF or ON)
        stepper->state = state;                                                                // update stepper state
    }

    return 1;
}

uint8_t stepper_home(Stepper *stepper, uint8_t direction)
{
    if (!home_validator(stepper))
        return 0;

    if (stepper->homeStep == FAST)
    {
        if (!endstop_isClicked(stepper->minEndstop))
        {
            stepper_setSpeed(stepper, (uint8_t *)"30"); // home with 30% speed
            stepper_setDirection(stepper, direction);   // set left direction
            stepper_run(stepper);                       // start motor moving

            stepper->state = HOMING; // update stepper state
            stepper->lastHomeStep = FAST;
        }
    }
    else if (stepper->homeStep == BACKWARD)
    {
        counter_count(65000);
        stepper->state = ON;
        stepper_move(stepper, (uint8_t *)"400");

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

    return 1;
}

uint8_t stepper_move(Stepper *stepper, uint8_t *steps)
{
    int32_t nSteps = 0;

    uint8_t valid = move_validator(stepper, steps);

    if (valid == 0 || valid == 9)
        return valid;

    sscanf((void *)steps, "%" SCNd32, &nSteps); // translate string to number

    if (nSteps == 0) // if steps is equals to 0, error
        return 0;
    else if (nSteps < 0) // check if steos are negative, set LEFT direction
        stepper_setDirection(stepper, 0);
    else // set RIGHT direction
        stepper_setDirection(stepper, 1);

    nSteps = abs(nSteps); // calc absolute value

    if (nSteps == 1) // this is weird situation if we want to move by 1 step, i need to set counter to 1
        __HAL_TIM_SET_COUNTER(&stepper->slaveTimer, 1);
    else
    {
        if (stepper->slaveTimer.Instance == TIM2 || stepper->slaveTimer.Instance == TIM5) // TIM2 and TIM5 are 32-bit timers and there is something like, that i need to decrease steps for them
            nSteps -= 1;
    }

    __HAL_TIM_SET_AUTORELOAD(&stepper->slaveTimer, nSteps); // set target value

    stepper_switch(stepper, 1);                                 // turn ON stepper motor
    HAL_TIM_Base_Start_IT(&stepper->slaveTimer);                // starts counting of PWM cycles
    HAL_TIM_PWM_Start(&stepper->masterTimer, stepper->channel); // starts moving

    stepper->state = MOVING; // update stepper state

    return 1;
}

void stepper_run(Stepper *stepper)
{
    stepper_switch(stepper, 1);                                 // turn ON stepper
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