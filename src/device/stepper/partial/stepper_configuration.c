#include "device/stepper/partial/stepper_configuration.h"

#include "counter.h"
#include "device/stepper/partial/stepper_calculator.h"
#include "device/stepper/partial/stepper_state_manager.h"

void stepper_updateSpeed(Stepper *stepper, float speed)
{
    if (stepper->speed.type == DYNAMIC)
        stepper->speed.lastTimeUpdate = HAL_GetTick();

    stepper->speed.current = speed;

    Speed_params regs = calculate_speed(stepper->info.axisType, speed);

    __HAL_TIM_SET_PRESCALER(&stepper->hardware.masterTimer, regs.psc);
    __HAL_TIM_SET_AUTORELOAD(&stepper->hardware.masterTimer, regs.arr);
    __HAL_TIM_SET_COMPARE(&stepper->hardware.masterTimer, stepper->hardware.channel, regs.pul); // set pulse width
}

// called by user command
void stepper_configure(Stepper *stepper, float speed, float acceleration)
{
    stepper->speed.target = speed;
    stepper->acceleration.current = acceleration;

    if (acceleration > 0.0f)
    {
        stepper->acceleration.current /= 1000.0f; // save acceleration in milliseconds instead of seconds

        stepper_updateSpeed(stepper, 0.0f);
        stepper->speed.type = DYNAMIC;
        stepper->speed.state = CONSTANT;
    }
    else
    {
        stepper_updateSpeed(stepper, speed);
        stepper->speed.type = STATIC;
        stepper->speed.state = CONSTANT;
    }
}

void stepper_startSpeedProcedure(Stepper *stepper)
{
    if (stepper->speed.type == STATIC)
        return;

    stepper->speed.state = RAISING;
    stepper->speed.lastTimeUpdate = HAL_GetTick();
}

void stepper_accelerate(Stepper *stepper) // only if acceleration is set
{
    uint32_t elapsedTime = (HAL_GetTick() - stepper->speed.lastTimeUpdate);

    // calculates increares / decrease of speed in time
    float delta = (float)((uint32_t)(elapsedTime)*stepper->acceleration.current);

    // calculates new speed by delta
    float newSpeed = stepper->speed.current + delta;

    // checks if new calculated speed fit within

    // in FALLING if speed goes to zero or below
    // then set 0 speed and CONSTANT (this actially mean 0 speed (move -> falling finished))
    if (newSpeed <= 0.0f)
    {
        newSpeed = 0.0f;
        stepper->speed.state = CONSTANT;
    }

    // in RAISING if speed goes to target or over
    // then need to align it, and set to CONSTANT
    // there is also invert of acceleration and calculated required steps
    else if (newSpeed >= stepper->speed.target)
    {
        newSpeed = stepper->speed.target;
        stepper->acceleration.current *= -1.0f;

        stepper->speed.state = CONSTANT;

        // deceleration have sense only in MOVING mode (not HOMING), => then need to know how many steps acceleration takes
        if (stepper_isState(stepper, MOVING))
            stepper->acceleration.stepsNeededToFullAccelerate += (stepper->hardware.slaveTimer.Instance->ARR - stepper->hardware.slaveTimer.Instance->CNT);
    }

    stepper_updateSpeed(stepper, newSpeed);
}

void stepper_setDirection(Stepper *stepper, uint8_t direction)
{
    HAL_GPIO_WritePin((GPIO_TypeDef *)stepper->hardware.port, stepper->hardware.dir, direction);
    wait(5); // need wait minimum 5us after set direction before go
}

void stepper_changeDirection(Stepper *stepper)
{
    stepper_changeDirectionImmediately(stepper);
    wait(5); // need wait minimum 5us after change direction before go
}

void stepper_changeDirectionImmediately(Stepper *stepper)
{
    HAL_GPIO_TogglePin((GPIO_TypeDef *)stepper->hardware.port, stepper->hardware.dir);
}

void stepper_resetSpeed(Stepper *stepper)
{
    stepper->speed.current = 0.0f;

    if (stepper->acceleration.current < 0.0f)
        stepper->acceleration.current *= -1.0f;

    //stepper->acceleration.set
    stepper->acceleration.stepsNeededToFullAccelerate = 0;
}
