#include "device/stepper/partial/stepper_configuration.h"

#include "counter.h"
#include "device/stepper/partial/stepper_calculator.h"
#include "device/stepper/partial/stepper_state_manager.h"
#include "device/stepper/partial/stepper_peripheral.h"

// calls multiple times with acceleration / deceleration
void stepper_updateSpeed(Stepper *stepper, float speed)
{
    if (stepper->speed.type == DYNAMIC)
        stepper->speed.lastTimeUpdate = HAL_GetTick();

    stepper->speed.current = speed;

    Speed_params regs = convertSpeedToRegisters(stepper->info.axisType, speed);

    __HAL_TIM_SET_PRESCALER(&stepper->hardware.masterTimer, regs.psc);
    __HAL_TIM_SET_AUTORELOAD(&stepper->hardware.masterTimer, regs.arr);
    __HAL_TIM_SET_COMPARE(&stepper->hardware.masterTimer, stepper->hardware.channel, regs.pul); // set pulse width
}

// calls by user command
void stepper_configure(Stepper *stepper, float speed, float acceleration)
{
    stepper->speed.target = speed;
    stepper->acceleration.current = acceleration;

    if (acceleration > 0.0f)
    {
        stepper->acceleration.current /= 1000.0f; // save acceleration in milliseconds instead of seconds

        stepper_updateSpeed(stepper, 0.0f);
        stepper->speed.type = DYNAMIC;
    }
    else
    {
        stepper_updateSpeed(stepper, speed);
        stepper->speed.type = STATIC;
    }

    stepper->speed.state = CONSTANT;
}

void stepper_initAcceleration(Stepper *stepper, enum SpeedState state)
{
    if (stepper->speed.type == STATIC)
        return;

    stepper->speed.state = state;
    stepper->speed.lastTimeUpdate = HAL_GetTick();
}

// cals multiple times
void stepper_accelerate(Stepper *stepper) // only if acceleration is set
{
    float newSpeed = calculateSpeed(stepper);

    // in RAISING if speed goes to target or over
    // then need to align it, and set to CONSTANT
    // there is also invert of acceleration and calculated required steps
    if (newSpeed >= stepper->speed.target)
    {
        newSpeed = stepper->speed.target;
        stepper->speed.state = CONSTANT;

        // deceleration have sense only in MOVING mode (not HOMING), => then need to know how many steps acceleration takes
        if (stepper_isState(stepper, MOVING))
        {
            stepper->acceleration.current *= -1.0f;
            stepper->acceleration.stepsNeededToAccelerate = calculateStepsNeededToAccelerate(stepper);
        }
    }

    stepper_updateSpeed(stepper, newSpeed);
}

void stepper_setDirection(Stepper *stepper, uint8_t direction)
{
    HAL_GPIO_WritePin((GPIO_TypeDef *)stepper->hardware.port, stepper->hardware.dir, direction);
    wait(5); // need wait minimum 5us after set direction before go
}

void stepper_changeDirectionImmediately(Stepper *stepper)
{
    HAL_GPIO_TogglePin((GPIO_TypeDef *)stepper->hardware.port, stepper->hardware.dir);
}

void stepper_changeDirection(Stepper *stepper)
{
    stepper_changeDirectionImmediately(stepper);
    wait(5); // need wait minimum 5us after change direction before go
}

void stepper_resetSpeed(Stepper *stepper)
{
    stepper->speed.current = 0.0f;

    if (stepper->acceleration.current < 0.0f)
        stepper->acceleration.current *= -1.0f;

    stepper->acceleration.stepsNeededToAccelerate = 0;
}