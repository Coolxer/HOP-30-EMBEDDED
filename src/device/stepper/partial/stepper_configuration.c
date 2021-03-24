#include "device/stepper/partial/stepper_configuration.h"

#include "counter.h"
#include "device/stepper/partial/stepper_calculator.h"
#include "device/stepper/partial/stepper_state_manager.h"

void stepper_configure(Stepper *stepper, float speed, float acceleration)
{
    stepper->speed.target = speed;
    stepper->acceleration.current = acceleration;

    if (acceleration > 0.0f)
    {
        stepper->acceleration.current /= 1000.0f; // save acceleration in milliseconds instead of seconds
        stepper->acceleration.set = SET;
        stepper->speed.state = RAISING;

        stepper_updateSpeed(stepper, 0.0f);
    }
    else
    {
        stepper->acceleration.set = RESET;
        stepper->speed.state = CONSTANT;
        stepper_updateSpeed(stepper, speed);
    }
}

void stepper_updateSpeed(Stepper *stepper, float speed)
{
    if (stepper->acceleration.set)
        stepper->speed.lastTimeUpdate = HAL_GetTick();

    stepper->speed.current = speed;

    Speed_params regs = calculate_speed(stepper->info.axisType, speed);

    __HAL_TIM_SET_PRESCALER(&stepper->hardware.masterTimer, regs.psc);
    __HAL_TIM_SET_AUTORELOAD(&stepper->hardware.masterTimer, regs.arr);
    __HAL_TIM_SET_COMPARE(&stepper->hardware.masterTimer, stepper->hardware.channel, regs.pul); // set pulse width
}

void stepper_accelerate(Stepper *stepper) // only if acceleration is set
{
    // if stepper is accelerating (acceleration > 0 and speed target not reached) OR
    // if stepper is decelerating (acceleration < 0 and speed target not reached (0))
    if ((stepper->acceleration.current > 0.0f && stepper->speed.current < stepper->speed.target) ||
        (stepper->acceleration.current < 0.0f && stepper->speed.current > stepper->speed.target))
    {
        uint32_t elapsedTime = (HAL_GetTick() - stepper->speed.lastTimeUpdate);
        float newSpeed = stepper->speed.current + (float)((uint32_t)(elapsedTime)*stepper->acceleration.current);

        if (newSpeed > 0) // security in deecelerate to not over-go to minus values
            stepper_updateSpeed(stepper, newSpeed);
        else
            stepper->acceleration.set = RESET;
    }
    // if stepper is over-accelerated (current speed > target speed) => then align current to target
    else if (stepper->acceleration.current > 0.0f && stepper->speed.current > stepper->speed.target)
        stepper_updateSpeed(stepper, stepper->speed.target);

    // if finish accelerating or decelerating
    else
    {
        stepper->acceleration.current *= -1.0f;
        stepper->acceleration.set = RESET;

        // deceleration have sense only in MOVING mode (not HOMING), => then need to know how many steps acceleration takes
        if (stepper_isState(stepper, MOVING))
            stepper->acceleration.stepsNeededToFullAccelerate += (stepper->hardware.slaveTimer.Instance->ARR - stepper->hardware.slaveTimer.Instance->CNT);
    }
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

void stepper_reset(Stepper *stepper)
{
    stepper->speed.current = 0.0f;
    stepper->speed.lastTimeUpdate = 0;

    if (stepper->acceleration.current < 0.0f || stepper->acceleration.current > 0.0f)
    {
        // restores acceleration settings
        if (stepper->acceleration.current < 0.0f)
            stepper->acceleration.current *= -1.0f;

        stepper->acceleration.set = SET;
    }

    //stepper->acceleration.set
    stepper->acceleration.stepsNeededToFullAccelerate = 0;
}
