#include "device/stepper/partial/stepper_operation.h"

#include "device/stepper/config/stepper_config.h"
#include "device/stepper/partial/stepper_peripheral.h"
#include "device/stepper/partial/stepper_configuration.h"
#include "device/stepper/partial/stepper_calculator.h"
#include "device/stepper/partial/stepper_helper.h"

#include "device/endstop/partial/endstop_operation.h"

void stepper_switch(Stepper *stepper, uint8_t state)
{
    if (getState(stepper) != state) // check if state is not currently exists
    {
        HAL_GPIO_WritePin((GPIO_TypeDef *)stepper->hardware.port, stepper->hardware.enable, state); // switches the stepper (OFF or ON)
        setState(stepper, state);
    }
}

void stepper_home(Stepper *stepper, uint8_t step)
{
    if (step == FAST_BACKWARD)
    {
        if (!endstop_isClicked(stepper->minEndstop))
        {
            stepper_configure(stepper, getHomeFastBackwardSpeed(stepper), getHomeFastBackwardAcceleration(stepper));
            stepper_setDirection(stepper, LEFT);
            stepper_switch(stepper, UP);
            stepper_run(stepper);

            setHomeStep(stepper, FAST_BACKWARD);
        }
    }
    else if (step == SLOW_FORWARD)
    {
        stepper_configure(stepper, getHomeSlowForwardSpeed(stepper), getHomeSlowForwardAcceleration(stepper));
        stepper_move(stepper, ENDSTOP_OUTGOING_WAY, RIGHT);
        setHomeStep(stepper, SLOW_FORWARD);
        return; // to not set HOMING state, because it's time for MOVING
    }
    else // if step == PRECISE_BACKWARD
    {
        stepper_configure(stepper, getHomePreciseBackwardSpeed(stepper), getHomePreciseBackwardAcceleration(stepper));
        stepper_changeDirection(stepper);
        stepper_run(stepper);

        setHomeStep(stepper, PRECISE_BACKWARD);
    }

    setState(stepper, HOMING);
}

void stepper_move(Stepper *stepper, float way, uint8_t direction)
{
    uint32_t target = calculateTarget(getAxisType(stepper), way);

    // TIM2 and TIM5 are 32-bit timers and there is something like, that i need to decrease arr for them
    if (getSlaveTimer(stepper)->Instance == TIM2 || getSlaveTimer(stepper)->Instance == TIM5)
        target--;

    setTarget(stepper, target);
    stepper_setDirection(stepper, direction);
    stepper_reload(stepper);

    stepper_switch(stepper, UP);
    setState(stepper, MOVING);
    stepper_run(stepper);
}

void stepper_run(Stepper *stepper)
{
    if (getState(stepper) == MOVING)
        HAL_TIM_Base_Start_IT(getSlaveTimer(stepper));

    HAL_TIM_PWM_Start(&stepper->hardware.masterTimer, stepper->hardware.channel); // starts moving

    stepper_initAcceleration(stepper, RAISING);
}

void stepper_process(Stepper *stepper)
{
    if (getState(stepper) != HOMING && getState(stepper) != MOVING)
        return;

    if (getSpeedType(stepper) == DYNAMIC)
    {
        if (getSpeedState(stepper) != CONSTANT)
            stepper_accelerate(stepper);
        else
        {
            // deceleration is only possible with MOVING, because with HOMING destination is unknown
            if (getState(stepper) == MOVING)
            {
                // check if target is less or equal to number of steps needed for deceleration (same value as acceleration)
                // then start to deceleration
                if (calculateRemainingTarget(stepper) <= getStepsNeededToAccelerate(stepper))
                    stepper_initAcceleration(stepper, FALLING);
            }
        }
    }
}
