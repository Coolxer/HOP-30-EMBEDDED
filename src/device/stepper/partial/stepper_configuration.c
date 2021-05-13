#include "device/stepper/partial/stepper_configuration.h"

#include "config.h"
#include "counter.h"

#include "command/partial/data_assistant.h"

#include "device/stepper/partial/stepper_calculator.h"
#include "device/stepper/partial/stepper_peripheral.h"
#include "device/stepper/partial/stepper_helper.h"

// calls multiple times with acceleration / deceleration
void stepper_updateSpeed(Stepper *stepper, float speed)
{
    stepper_updateLastTime(stepper);
    stepper_setCurrentSpeed(stepper, speed);

    Speed_params regs = convertSpeedToRegisters(stepper_getAxisType(stepper), speed);
    stepper_setSpeedRegisters(stepper, regs.psc, regs.arr, regs.pul);
}

// calls by user command
void stepper_configure(Stepper *stepper, uint8_t *speed, uint8_t *acceleration)
{
    float spd = convertStrToFloat(speed);
    float acc = convertStrToFloat(acceleration);

    if (acc > 0.0f)
    {
        stepper_setCurrentAcceleration(stepper, spd / 1000.0f); // save acceleration in milliseconds instead of seconds
        stepper_updateSpeed(stepper, 0.0f);
        stepper_setSpeedType(stepper, DYNAMIC);
    }
    else
    {
        stepper_setCurrentAcceleration(stepper, 0.0f);
        stepper_updateSpeed(stepper, spd);
        stepper_setSpeedType(stepper, STATIC);
    }

    stepper_setTargetSpeed(stepper, spd);
    stepper_setSpeedState(stepper, CONSTANT);
}

void stepper_initAcceleration(Stepper *stepper, enum SpeedState state)
{
    stepper_setSpeedState(stepper, state); // state == RAISING || FALLING
    stepper_updateLastTime(stepper);
}

// calls multiple times
void stepper_accelerate(Stepper *stepper) // only if acceleration is set
{
    float newSpeed = calculateSpeed(stepper);

    // in RAISING if speed goes to target or over
    // then need to align it, and set to CONSTANT
    // there is also invert of acceleration and calculated required steps
    if (newSpeed >= stepper_stepper_getTargetSpeed(stepper))
    {
        newSpeed = stepper_stepper_getTargetSpeed(stepper);
        stepper_setSpeedState(stepper, CONSTANT);

        // deceleration have sense only in PRECISED move, => then need to know how many steps acceleration takes
        if (stepper_getMoveType(stepper) == PRECISED)
        {
            stepper_setStepsNeededToAccelerate(stepper, calculateStepsNeededToAccelerate(stepper));
            stepper_setCurrentAcceleration(stepper, stepper_getCurrentAcceleration(stepper) * -1.0f);
        }
    }

    stepper_updateSpeed(stepper, newSpeed);
}

void stepper_resetSpeed(Stepper *stepper)
{
    stepper_setCurrentSpeed(stepper, 0.0f);

    float acceleration = stepper_getCurrentAcceleration(stepper);
    if (acceleration < 0.0f)
        stepper_setCurrentAcceleration(stepper, acceleration * -1.0f);

    stepper_setStepsNeededToAccelerate(stepper, 0);
}

void stepper_setDirection(Stepper *stepper, uint8_t direction)
{
    HAL_GPIO_WritePin((GPIO_TypeDef *)stepper->hardware.dirPort, stepper->hardware.dirPin, direction);
    wait(STEPPER_SET_DIRECTION_DELAY); // need wait minimum 5us after set direction before go
}

void stepper_changeDirectionImmediately(Stepper *stepper)
{
    HAL_GPIO_TogglePin((GPIO_TypeDef *)stepper->hardware.dirPort, stepper->hardware.dirPin);
}

void stepper_changeDirection(Stepper *stepper)
{
    stepper_changeDirectionImmediately(stepper);
    wait(STEPPER_SET_DIRECTION_DELAY); // need wait minimum 5us after change direction before go
}
