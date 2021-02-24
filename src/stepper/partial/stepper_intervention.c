#include "stepper/partial/stepper_intervention.h"

#include "command/partial/err.h"
#include "stepper/partial/stepper_validator.h"
#include "stepper/partial/stepper_configuration.h"

uint8_t stepper_pause(Stepper *stepper)
{
    uint8_t invalid = validate_pause(stepper);

    if (invalid)
        return invalid;

    if (stepper->instance.state == MOVING) // if stepper is in MOVING state i need to remember register values TARGET and COUNTER
    {
        uint16_t rest = (uint16_t)(stepper->hardware.slaveTimer.Instance->ARR - stepper->hardware.slaveTimer.Instance->CNT); // MAX_16BITVALUE

        // TIM2 and TIM5 are 32-bit timers and there is something like, that i need to decrease arr for them
        if (rest > 0 && (stepper->hardware.slaveTimer.Instance == TIM2 || stepper->hardware.slaveTimer.Instance == TIM5))
            rest--;

        stepper->instance.movement.rest = rest;
    }

    stepper_stopTimers(stepper); // stop timers

    stepper->instance.lastState = stepper->instance.state; // remember last state
    stepper->instance.state = PAUSED;                      // update state

    return ERR.NO_ERROR;
}

uint8_t stepper_resume(Stepper *stepper)
{
    uint8_t invalid = validate_resume(stepper);

    if (invalid)
        return invalid;

    // if stepper was in MOVING state before pause, we need to set target and counter to previous values
    if (stepper->instance.lastState == MOVING)
    {
        __HAL_TIM_SET_COUNTER(&stepper->hardware.slaveTimer, 0);
        __HAL_TIM_SET_AUTORELOAD(&stepper->hardware.slaveTimer, stepper->instance.movement.rest);

        HAL_TIM_Base_Start_IT(&stepper->hardware.slaveTimer); // enable slaveTimer
    }

    HAL_TIM_PWM_Start(&stepper->hardware.masterTimer, stepper->hardware.channel); // enable masterTimer

    stepper->instance.state = stepper->instance.lastState; // recover state

    return ERR.NO_ERROR;
}

uint8_t stepper_stop(Stepper *stepper)
{
    uint8_t invalid = validate_stop(stepper);

    if (invalid)
        return invalid;

    stepper_stopTimers(stepper); // stop timers

    stepper->instance.lastState = stepper->instance.state = ON; // reset stepper state

    return ERR.NO_ERROR;
}

uint8_t stepper_emergency_shutdown(Stepper *stepper)
{
    HAL_GPIO_WritePin((GPIO_TypeDef *)stepper->hardware.port, stepper->hardware.enable, GPIO_PIN_RESET); // switches the stepper OFF

    stepper->instance.state = OFF; // update stepper state

    return ERR.NO_ERROR;
}