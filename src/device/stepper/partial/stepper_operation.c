#include "device/stepper/partial/stepper_operation.h"

#include "device/stepper/partial/stepper_peripheral.h"
#include "device/stepper/partial/stepper_configuration.h"
#include "device/stepper/partial/stepper_calculator.h"
#include "device/stepper/partial/stepper_helper.h"

#include "device/endstop/partial/endstop_operation.h"

void stepper_switch(Stepper *stepper, uint8_t state)
{
    if (stepper_getState(stepper) != state) // check if state is not currently exists
    {
        HAL_GPIO_WritePin((GPIO_TypeDef *)stepper->hardware.port, stepper->hardware.enable, state); // switches the stepper (OFF or ON)
        stepper_setState(stepper, state);
    }
}

void stepper_move(Stepper *stepper, float way, uint8_t direction)
{
    if (way > 0.0f)
    {
        stepper_setMoveType(stepper, PRECISED);

        uint32_t steps = convertWayToSteps(stepper_getAxisType(stepper), way);

        // TIM2 and TIM5 are 32-bit timers and there is something like, that i need to decrease arr for them
        if (stepper_getSlaveTimer(stepper)->Instance == TIM2 || stepper_getSlaveTimer(stepper)->Instance == TIM5)
            steps--;

        stepper_setUnloadedSteps(stepper, steps);
        stepper_reload(stepper);
    }
    else
        stepper_setMoveType(stepper, LIMITED);

    stepper_setDirection(stepper, direction);
    stepper_switch(stepper, UP);
    stepper_run(stepper);
}

void stepper_run(Stepper *stepper)
{
    if (stepper_getMoveType(stepper) == PRECISED)
        HAL_TIM_Base_Start_IT(stepper_getSlaveTimer(stepper));

    HAL_TIM_PWM_Start(&stepper->hardware.masterTimer, stepper->hardware.channel); // starts moving

    stepper_initAcceleration(stepper, RAISING);
    stepper_setState(stepper, MOVING);
}

void stepper_watchdog(Stepper *stepper)
{
    if (stepper_getState(stepper) == MOVING)
    {
        if (stepper_getSpeedType(stepper) == DYNAMIC)
        {
            if (stepper_getSpeedState(stepper) != CONSTANT)
                stepper_accelerate(stepper);
            else
            {
                // deceleration is only possible with MOVING, because with HOMING destination is unknown
                if (stepper_getMoveType(stepper) == PRECISED)
                {
                    // check if target is less or equal to number of steps needed for deceleration (same value as acceleration)
                    // then start to deceleration
                    if ((stepper_getUnloadedSteps(stepper) + calculateRemainingSteps(stepper)) <= stepper_getStepsNeededToAccelerate(stepper))
                        stepper_initAcceleration(stepper, FALLING);
                }
            }
        }
    }
}
