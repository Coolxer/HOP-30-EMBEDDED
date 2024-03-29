#include "device/low_voltage/stepper/partial/stepper_calculator.h"

#include <math.h>

#include "config.h"
#include "device/low_voltage/stepper/config/stepper_calculation.h"
#include "device/low_voltage/stepper/partial/stepper_helper.h"

Speed_params
convertSpeedToRegisters(float stepsPerUnit, float speed)
{
    Speed_params regs = {0};
    float arr = 0.0f; // autoreload
    float stepsPerSecond = 0.0f;

    // convert mm/s to steps/s
    stepsPerSecond = (float)(speed * stepsPerUnit);

    /* MATHEMATICAL FORMULA

        Update_event = TIM_CLK/((PSC + 1)*(ARR + 1)*(RCR + 1)), where RCR = 0
        Update_event = TIM_CLK/((PSC + 1)*(ARR + 1))

        # WHERE #
        TIM_CLK = timer clock input
        PSC = 16-bit prescaler register [0 - 65535]
        ARR = 16/32-bit Autoreload register [0 - 65535]
        RCR = 16-bit repetition counter [0 - 65535]
        
    END OF MATHEMATICAL FORMULA*/

    /*
        ATTENTION!
        In many examples there was different values on ARR register,
        but PSC still be const as it was set up at start

        I'm not sure if it can be changine at time like ARR,
        but to get wide range of speed <0.1, 100> 2 registers are needed

        Probably min speed is too low and max speed is too high.
        If you reduce range it is possible to have const PSC = 1
        and just modify ARR register at a time

        Probably ARR should have any value [in my opinion it have always 1 at least]
        so i decided to reverse psc and arr
    */

    // calc how big divider is needed and asign it as arr
    arr = (float)((CLOCK_FREQUENCY / stepsPerSecond) - 1.0f);

    // if divider overflow max 16-bit value [0 - 65535]
    // that means that i need use prescaler, beacause arr is not enough
    if (arr > MAX_16BIT_VALUE)
    {
        regs.psc = (uint16_t)round((float)(arr / MAX_16BIT_VALUE));
        regs.arr = MAX_16BIT_VALUE;
    }
    else // if divider is less or equals MAX_16BIT_VALUE
    {
        regs.psc = 0;
        regs.arr = (uint16_t)round(arr);
    }

    // PWM pulse width [DUTY] (0%, 25%, 50%, 75%, 100%)
    // don't know what it should be, 2 different guys give 50% of ARR register
    // there should be min. 2.5us as stepper driver gives

    // so i decided to have 50% duty cycle, because there is 50% time LOW nad 50% high signal
    regs.pul = (uint16_t)(round(regs.arr / 2.0f));

    return regs;
}

float calculateSpeed(Stepper *stepper)
{
    uint32_t elapsedTime = (HAL_GetTick() - stepper_getLastTimeUpdate(stepper));

    // calculates increares / decrease of speed in time
    float delta = (float)(elapsedTime)*stepper_getCurrentAcceleration(stepper);

    // calculates new speed by delta(
    float speed = stepper_getCurrentSpeed(stepper) + delta;

    // in FALLING if speed goes to zero or below
    // then set 0 speed
    if (speed < 0.0f)
        speed = 0.0f;

    return speed;
}

uint32_t calculateStepsNeededToAccelerate(Stepper *stepper)
{
    uint32_t steps = stepper_getStepsNeededToAccelerate(stepper) + stepper_getProgress(stepper);

    float safetyBarier = 0.01f * (float)steps;

    // add safety barier [in deceleration to not zero speed if there are steps to be done]
    // beacause adding 1% (it may the stepper speed will not falling to really 0 but its ok)
    steps = (uint32_t)round(steps - (uint32_t)safetyBarier);

    return steps;
}

uint32_t convertWayToSteps(float stepsPerUnit, float way)
{
    // calc real steps need to make to move by given mm or deg.
    uint32_t steps = (uint32_t)(round(way * stepsPerUnit));

    return steps;
}

uint16_t calculateRemainingSteps(Stepper *stepper)
{
    return (uint16_t)(stepper_getTarget(stepper) - stepper_getProgress(stepper));
}
