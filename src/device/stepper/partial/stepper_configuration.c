#include "device/stepper/partial/stepper_configuration.h"

#include "counter.h"
#include "device/stepper/partial/stepper_calculator.h"
#include "device/stepper/partial/stepper_state_manager.h"

void stepper_configure(Stepper *stepper, float speed, float acceleration)
{
    stepper->acceleration.current = acceleration;

    if (acceleration == 0.0f)
        stepper_updateSpeed(stepper, speed);
    else
    {
        stepper->speed.current = 0.0f;
        stepper->speed.target = speed;

        stepper->acceleration.current /= 1000.0f; // save acceleration in milliseconds instead of seconds
    }
}

void stepper_updateSpeed(Stepper *stepper, float speed)
{
    if (stepper->acceleration.current != 0.0f)
        stepper->speed.lastTimeUpdate = HAL_GetTick();

    Speed_params regs = calculate_speed(stepper->info.axisType, speed); // HERE

    stepper->speed.current = speed;

    __HAL_TIM_SET_PRESCALER(&stepper->hardware.masterTimer, regs.psc);
    __HAL_TIM_SET_AUTORELOAD(&stepper->hardware.masterTimer, regs.arr);
    __HAL_TIM_SET_COMPARE(&stepper->hardware.masterTimer, stepper->hardware.channel, regs.pul); // set pulse width
}

void stepper_accelerate(Stepper *stepper)
{
    if (stepper_isState(stepper, HOMING) || stepper_isState(stepper, MOVING))
    {
        if (stepper->speed.current < stepper->speed.target)
        {
            uint32_t elapsedTime = (HAL_GetTick() - stepper->speed.lastTimeUpdate);
            float newSpeed = stepper->speed.current + (elapsedTime * stepper->acceleration.current);

            stepper_updateSpeed(stepper, newSpeed);
        }
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
