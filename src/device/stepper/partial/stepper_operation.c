#include "device/stepper/partial/stepper_operation.h"

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

void stepper_home(Stepper *stepper, uint8_t step)
{
    if (step == FAST_BACKWARD)
    {
        if (!endstop_isClicked(stepper->minEndstop))
        {
            stepper_switch(stepper, UP);

            stepper_setSpeed(stepper, stepper->speed.homeFastBackward); // home with low speed
            stepper_setDirection(stepper, LEFT);                        // set left direction
            stepper_run(stepper);                                       // start motor moving

            stepper_setState(stepper, HOMING);
            stepper_setHomeStep(stepper, FAST_BACKWARD);
        }
    }
    else if (step == SLOW_FORWARD)
    {
        stepper_setSpeed(stepper, stepper->speed.homeSlowForward);
        stepper_move(stepper, 10.0f, RIGHT);
        stepper_setHomeStep(stepper, SLOW_FORWARD);
    }
    else // if step == PRECISE_BACKWARD
    {
        stepper_setSpeed(stepper, stepper->speed.homePreciseBackward);
        stepper_changeDirection(stepper);
        stepper_run(stepper);

        stepper_setState(stepper, HOMING);
        stepper_setHomeStep(stepper, PRECISE_BACKWARD);
    }
}

void stepper_startMoving(Stepper *stepper)
{
    stepper_switch(stepper, UP);

    stepper_updateSpeed(stepper, 0.0f);

    HAL_TIM_Base_Start_IT(&stepper->hardware.slaveTimer);                         // starts counting of PWM cycles
    HAL_TIM_PWM_Start(&stepper->hardware.masterTimer, stepper->hardware.channel); // starts moving

    stepper_setState(stepper, MOVING);
}

void stepper_move(Stepper *stepper, float way, uint8_t direction)
{
    Way_params params = calculate_way(stepper->info.axisType, way);

    stepper_setDirection(stepper, direction);

    // TIM2 and TIM5 are 32-bit timers and there is something like, that i need to decrease arr for them
    if (stepper->hardware.slaveTimer.Instance == TIM2 || stepper->hardware.slaveTimer.Instance == TIM5)
        params.arr--;

    stepper->instance.movement.way = params;

    stepper_manageSlaveTimer(stepper);
    stepper_startMoving(stepper);
}

void stepper_run(Stepper *stepper)
{
    HAL_TIM_PWM_Start(&stepper->hardware.masterTimer, stepper->hardware.channel); // starts moving
}
