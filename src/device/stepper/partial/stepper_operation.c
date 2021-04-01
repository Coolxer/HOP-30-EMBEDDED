#include "device/stepper/partial/stepper_operation.h"

#include "device/stepper/partial/stepper_state_manager.h"
#include "device/stepper/partial/stepper_peripheral.h"
#include "device/stepper/partial/stepper_configuration.h"

#include "device/stepper/partial/stepper_calculator.h"
#include "device/endstop/partial/endstop_operation.h"

float ENDSTOP_OUTGOING_WAY = 20.0f; // way to get out of endstop range

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

            stepper_configure(stepper, stepper->speed.homeFastBackward, stepper->acceleration.homeFastBackward);
            stepper_setDirection(stepper, LEFT);
            stepper_run(stepper);

            stepper_setHomeStep(stepper, FAST_BACKWARD);
        }
    }
    else if (step == SLOW_FORWARD)
    {
        stepper_configure(stepper, stepper->speed.homeSlowForward, stepper->acceleration.homeSlowForward);
        stepper_move(stepper, ENDSTOP_OUTGOING_WAY, RIGHT);
        stepper_setHomeStep(stepper, SLOW_FORWARD);
        return; // to not set HOMING state, because it's time for MOVING
    }
    else // if step == PRECISE_BACKWARD
    {
        stepper_configure(stepper, stepper->speed.homePreciseBackward, stepper->acceleration.homePreciseBackward);
        stepper_changeDirection(stepper);
        stepper_run(stepper);

        stepper_setHomeStep(stepper, PRECISE_BACKWARD);
    }

    stepper_setState(stepper, HOMING);
}

void stepper_startMoving(Stepper *stepper)
{
    stepper_switch(stepper, UP);

    HAL_TIM_Base_Start_IT(&stepper->hardware.slaveTimer);                         // starts counting of PWM cycles
    HAL_TIM_PWM_Start(&stepper->hardware.masterTimer, stepper->hardware.channel); // starts moving
    stepper_startSpeedProcedure(stepper);

    stepper_setState(stepper, MOVING);
}

void stepper_move(Stepper *stepper, float way, uint8_t direction)
{
    uint32_t target = calculate_way(stepper->info.axisType, way);

    // TIM2 and TIM5 are 32-bit timers and there is something like, that i need to decrease arr for them
    if (stepper->hardware.slaveTimer.Instance == TIM2 || stepper->hardware.slaveTimer.Instance == TIM5)
        target--;

    stepper->movement.target = target;

    stepper_setDirection(stepper, direction);

    stepper_manageSlaveTimer(stepper);
    stepper_startMoving(stepper);
}

void stepper_run(Stepper *stepper)
{
    HAL_TIM_PWM_Start(&stepper->hardware.masterTimer, stepper->hardware.channel); // starts moving

    stepper_startSpeedProcedure(stepper);
}

void stepper_process(Stepper *stepper)
{
    if (!stepper_isState(stepper, HOMING) && !stepper_isState(stepper, MOVING))
        return;

    if (stepper->speed.type == DYNAMIC)
    {
        if (stepper->speed.state != CONSTANT)
            stepper_accelerate(stepper);
        else
        {
            if (stepper_isState(stepper, HOMING))
                return;

            uint32_t target = stepper->movement.target + (stepper->hardware.slaveTimer.Instance->ARR - stepper->hardware.slaveTimer.Instance->CNT);

            // check if target is less or equal to number of steps needed for full accel (same value need to deaccel)
            // then start to deceleration

            // start deeceleration with safety barier beacause adding 1% (it may the stepper speed will not falling to really 0 but its ok)
            if (target <= (float)(stepper->acceleration.stepsNeededToFullAccelerate - (0.01f * (float)stepper->acceleration.stepsNeededToFullAccelerate)))
            {
                stepper->speed.state = FALLING;
                stepper->speed.lastTimeUpdate = HAL_GetTick(); // need to update time, beacuse it was updated long ago (at speed raising) -> dont know when it was
            }
        }
    }
}
