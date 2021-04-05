#include "device/stepper/partial/stepper_configuration.h"

#include "counter.h"
#include "device/stepper/partial/stepper_calculator.h"
#include "device/stepper/partial/stepper_peripheral.h"
#include "device/stepper/partial/stepper_helper.h"

// calls multiple times with acceleration / deceleration
void stepper_updateSpeed(Stepper *stepper, float speed)
{
    if (getSpeedType(stepper) == DYNAMIC)
        updateLastTime(stepper);

    setCurrentSpeed(stepper, speed);

    Speed_params regs = convertSpeedToRegisters(getAxisType(stepper), speed);

    stepper_setSpeedRegisters(stepper, regs.psc, regs.arr, regs.pul);
}

// calls by user command
void stepper_configure(Stepper *stepper, float speed, float acceleration)
{
    setTargetSpeed(stepper, speed);
    setCurrentAcceleration(stepper, acceleration);

    if (acceleration > 0.0f)
    {
        setCurrentAcceleration(stepper, acceleration / 1000.0f); // save acceleration in milliseconds instead of seconds

        stepper_updateSpeed(stepper, 0.0f);
        setSpeedType(stepper, DYNAMIC);
    }
    else
    {
        stepper_updateSpeed(stepper, speed);
        setSpeedType(stepper, STATIC);
    }

    setSpeedState(stepper, CONSTANT);
}

void stepper_initAcceleration(Stepper *stepper, enum SpeedState state)
{
    if (getSpeedType(stepper) == STATIC)
        return;

    setSpeedState(stepper, state);
    updateLastTime(stepper);
}

// cals multiple times
void stepper_accelerate(Stepper *stepper) // only if acceleration is set
{
    float newSpeed = calculateSpeed(stepper);

    // in RAISING if speed goes to target or over
    // then need to align it, and set to CONSTANT
    // there is also invert of acceleration and calculated required steps
    if (newSpeed >= getTargetSpeed(stepper))
    {
        newSpeed = getTargetSpeed(stepper);
        setSpeedState(stepper, CONSTANT);

        // deceleration have sense only in MOVING mode (not HOMING), => then need to know how many steps acceleration takes
        if (getState(stepper) == MOVING)
        {
            setCurrentAcceleration(stepper, getCurrentAcceleration(stepper) * -1.0f);
            setStepsNeededToAccelerate(stepper, calculateStepsNeededToAccelerate(stepper));
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
    setCurrentSpeed(stepper, 0.0f);

    if (getCurrentAcceleration(stepper) < 0.0f)
        setCurrentAcceleration(stepper, getCurrentAcceleration(stepper) * -1.0f);

    setStepsNeededToAccelerate(stepper, 0);
}
