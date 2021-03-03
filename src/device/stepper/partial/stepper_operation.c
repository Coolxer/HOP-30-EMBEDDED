#include "device/stepper/partial/stepper_operation.h"

#include "enum/type.h"

#include "counter.h"

#include "device/stepper/partial/stepper_state_manager.h"
#include "device/stepper/partial/stepper_peripheral.h"
#include "device/stepper/partial/stepper_configuration.h"

#include "device/endstop/partial/endstop_operation.h"

void stepper_switch(Stepper *stepper, uint8_t state)
{
    if (!stepper_isState(stepper, state)) // check if state is not currently exists
    {
        HAL_GPIO_WritePin((GPIO_TypeDef *)stepper->hardware.port, stepper->hardware.enable, state); // switches the stepper (OFF or ON)
        stepper_setState(stepper, state);
    }
}

void stepper_home(Stepper *stepper)
{
    if (stepper_isHomeStep(stepper, FAST))
    {
        if (!endstop_isClicked(stepper->minEndstop))
        {
            stepper_updateLastHomeStep(stepper);

            stepper_switch(stepper, UP);

            stepper_setSpeed(stepper, 10.0f);    // home with low speed
            stepper_setDirection(stepper, LEFT); // set left direction
            stepper_run(stepper);                // start motor moving

            stepper_setState(stepper, HOMING);
        }
    }
    else if (stepper_isHomeStep(stepper, BACKWARD))
    {
        stepper_updateLastHomeStep(stepper);

        wait(65000); // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! HERE !!!!!!!!!!!!!!!!!!!!!
        stepper_updateStates(stepper, ON);
        stepper_move(stepper, 10.0f, LEFT);
    }
    else
    {
        stepper_updateLastHomeStep(stepper);

        //HAL_Delay(150);
        stepper_setSpeed(stepper, 1.0f);
        stepper_changeDirection(stepper);
        stepper_run(stepper);

        stepper_setState(stepper, HOMING);
    }
}

void stepper_startMoving(Stepper *stepper)
{
    stepper_switch(stepper, UP);

    HAL_TIM_Base_Start_IT(&stepper->hardware.slaveTimer);                         // starts counting of PWM cycles
    HAL_TIM_PWM_Start(&stepper->hardware.masterTimer, stepper->hardware.channel); // starts moving

    stepper_setState(stepper, MOVING);
}

void stepper_move(Stepper *stepper, float way, uint8_t direction)
{
    Way params = calculate_way(stepper->info.axisType, way);

    stepper_setDirection(stepper, direction);

    // TIM2 and TIM5 are 32-bit timers and there is something like, that i need to decrease arr for them
    if (stepper->hardware.slaveTimer.Instance == TIM2 || stepper->hardware.slaveTimer.Instance == TIM5)
        params.arr--;

    stepper->instance.movement.way = params;

    stepper_manageSlaveTimer(stepper);
    stepper_startMoving(stepper);
}

void stepper_finishMoving(Stepper *stepper)
{
    stepper_stopTimers(stepper);
    stepper_updateStates(stepper, ON);
}

void stepper_run(Stepper *stepper)
{
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