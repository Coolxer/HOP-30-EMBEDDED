#include "stepper/partial/stepper_calculator.h"

#include <math.h>

#include "config/clock.h"
#include "stepper/config/stepper_calculation.h"

void calculate_speed(Stepper *stepper, uint16_t speed)
{
    uint16_t psc = 0;   // prescaler
    uint16_t arr = 0;   // autoreload
    uint16_t pulse = 0; // pulse width

    // convert (mm/s or rps) to steps/s
    uint32_t stepsPerSecond = speed * (stepper->axisType == LINEAR ? STEPS_PER_MM : STEPS_PER_DEGREE);

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
        In many exmaples there was different values on ARR register,
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
    arr = (CLOCK_FREQUENCY / stepsPerSecond) - 1;

    // if divider overflow max 16-bit value [0 - 65535]
    // that means that i need use prescaler, beacause arr is not enough
    if (arr > MAX_16BIT_VALUE)
    {
        psc = round(arr / MAX_16BIT_VALUE);
        arr = MAX_16BIT_VALUE;
    }
    else // if divider is less or equals MAX_16BIT_VALUE
        arr = round(psc);

    // PWM pulse width [DUTY] (0%, 25%, 50%, 75%, 100%)
    // don't know what it should be, 2 different guys give 50% of ARR register
    // there should be min. 2.5us as stepper driver gives

    // so i decided to have 50% duty cycle, beacuse there is 50% time LOW nad 50% high signal
    pulse = round(arr / 2);

    __HAL_TIM_SET_PRESCALER(&stepper->masterTimer, psc);
    __HAL_TIM_SET_AUTORELOAD(&stepper->masterTimer, arr);
    __HAL_TIM_SET_COMPARE(&stepper->masterTimer, stepper->channel, pulse); // set pulse width
}