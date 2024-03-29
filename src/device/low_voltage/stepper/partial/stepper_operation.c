#include "device/low_voltage/stepper/partial/stepper_operation.h"

#include "null.h"
#include "data/assistant.h"
#include "command/partial/val.h"

#include "device/low_voltage/stepper/partial/stepper_peripheral.h"
#include "device/low_voltage/stepper/partial/stepper_configuration.h"
#include "device/low_voltage/stepper/partial/stepper_calculator.h"
#include "device/low_voltage/stepper/partial/stepper_helper.h"

#include "device/low_voltage/endstop/partial/endstop_operation.h"

void stepper_switch(Stepper *stepper, uint8_t *state)
{
    uint8_t st = convertStrToBoolean(state);

    if (stepper_getState(stepper) != st) // check if state is not currently exists
    {
        HAL_GPIO_WritePin((GPIO_TypeDef *)stepper->hardware.enablePort, stepper->hardware.enablePin, st); // switches the stepper (LOW or HIGH)
        stepper_setState(stepper, st);
    }
}

void stepper_move(Stepper *stepper, uint8_t *way, uint8_t *direction)
{
    float road = stringEqual(way, VAL.LIMIT) ? 0.0f : convertStrToFloat(way);

    if (road > 0.0f)
    {
        stepper_setMoveType(stepper, PRECISED);

        uint32_t steps = convertWayToSteps(stepper_getStepsPerUnit(stepper), road);

        // TIM2 and TIM5 are 32-bit timers and there is something like, that i need to decrease arr for them
        if (stepper_getSlaveTimer(stepper)->Instance == TIM2 || stepper_getSlaveTimer(stepper)->Instance == TIM5)
            steps--;

        stepper_setUnloadedSteps(stepper, steps);
        stepper_reload(stepper);
    }
    else
        stepper_setMoveType(stepper, LIMITED);

    stepper_setDirection(stepper, direction);
    stepper_switch(stepper, ON);
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
    if (stepper_getState(stepper) != MOVING || stepper_getSpeedType(stepper) != DYNAMIC)
        return;

    if (stepper_getSpeedState(stepper) != CONSTANT)
        stepper_accelerate(stepper);
    else
    {
        // deceleration is only possible with MOVING, because with HOMING destination is unknown
        if (stepper_getMoveType(stepper) != PRECISED)
            return;

        // check if target is less or equal to number of steps needed for deceleration (same value as acceleration)
        // then start to deceleration
        if ((stepper_getUnloadedSteps(stepper) + calculateRemainingSteps(stepper)) <= stepper_getStepsNeededToAccelerate(stepper))
            stepper_initAcceleration(stepper, FALLING);
    }
}