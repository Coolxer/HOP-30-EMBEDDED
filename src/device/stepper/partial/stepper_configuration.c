#include "device/stepper/partial/stepper_configuration.h"

#include "counter.h"
#include "device/stepper/partial/stepper_calculator.h"
#include "device/stepper/partial/stepper_state_manager.h"

void stepper_setSpeed(Stepper *stepper, float speed)
{
    stepper->speedAcceleration.speed.current = 0.0f;
    stepper->speedAcceleration.speed.target = speed;
}

void stepper_setAcceleration(Stepper *stepper, float acceleration)
{
    stepper->speedAcceleration.acceleration.current = acceleration / 1000.0f; // save acceleratin in milliseconds instead of seconds
}

void stepper_updateSpeed(Stepper *stepper, float speed)
{
    stepper->speedAcceleration.speed.lastTimeUpdate = HAL_GetTick();

    Speed_params regs = calculate_speed(stepper->info.axisType, speed); // HERE

    stepper->speedAcceleration.speed.current = speed;

    __HAL_TIM_SET_PRESCALER(&stepper->hardware.masterTimer, regs.psc);
    __HAL_TIM_SET_AUTORELOAD(&stepper->hardware.masterTimer, regs.arr);
    __HAL_TIM_SET_COMPARE(&stepper->hardware.masterTimer, stepper->hardware.channel, regs.pul); // set pulse width

    //stepper->speedAcceleration.speed.lastTimeUpdate = HAL_GetTick(); // or HERE
}

void stepper_accelerate(Stepper *stepper)
{
    if (stepper_isState(stepper, HOMING) || stepper_isState(stepper, MOVING))
    {
        if (stepper->speedAcceleration.speed.current < stepper->speedAcceleration.speed.target)
        {
            float elapsedTime = (HAL_GetTick() - stepper->speedAcceleration.speed.lastTimeUpdate);
            float newSpeed = stepper->speedAcceleration.speed.current + (elapsedTime * stepper->speedAcceleration.acceleration.current);

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
