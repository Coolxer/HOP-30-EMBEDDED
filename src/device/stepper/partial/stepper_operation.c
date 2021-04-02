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
            stepper_configure(stepper, stepper->speed.homeFastBackward, stepper->acceleration.homeFastBackward);
            stepper_setDirection(stepper, LEFT);
            stepper_switch(stepper, UP);
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

void stepper_move(Stepper *stepper, float way, uint8_t direction)
{
    uint32_t target = calculateWay(stepper->info.axisType, way);

    // TIM2 and TIM5 are 32-bit timers and there is something like, that i need to decrease arr for them
    if (stepper->hardware.slaveTimer.Instance == TIM2 || stepper->hardware.slaveTimer.Instance == TIM5)
        target--;

    stepper->movement.target = target;

    stepper_setDirection(stepper, direction);

    stepper_reload(stepper);

    stepper_switch(stepper, UP);
    stepper_setState(stepper, MOVING);
    stepper_run(stepper);
}

void stepper_run(Stepper *stepper)
{
    if (stepper_isState(stepper, MOVING))
        HAL_TIM_Base_Start_IT(&stepper->hardware.slaveTimer);

    HAL_TIM_PWM_Start(&stepper->hardware.masterTimer, stepper->hardware.channel); // starts moving

    stepper_initAcceleration(stepper, RAISING);
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
            // deceleration is only possible with MOVING, beacuse with HOMING destination is unknown
            if (stepper_isState(stepper, MOVING))
            {
                if (calculateIfShouldStartDecelerate(stepper))
                    stepper_initAcceleration(stepper, FALLING);
            }
        }
    }
}
