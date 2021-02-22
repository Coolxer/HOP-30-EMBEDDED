#include "stepper/partial/stepper_intervention.h"

#include "command/partial/err.h"
#include "stepper/partial/stepper_validator.h"
#include "stepper/partial/stepper_configuration.h"

uint8_t stepper_pause(Stepper *stepper)
{
    uint8_t invalid = pause_validator(stepper);

    if (invalid)
        return invalid;

    if (stepper->state == MOVING) // if stepper is in MOVING state i need to remember register values TARGET and COUNTER
    {
        stepper->target = stepper->slaveTimer.Instance->ARR;
        stepper->cnt = stepper->slaveTimer.Instance->CNT;

        if (stepper->slaveTimer.Instance == TIM2 || stepper->slaveTimer.Instance == TIM5) // if TIM2 and TIM5 i need to decrease target
            stepper->target--;
    }

    stepper_stopTimers(stepper); // stop timers

    stepper->lastState = stepper->state; // remember last state
    stepper->state = PAUSED;             // update state

    return ERR.NO_ERROR;
}

uint8_t stepper_resume(Stepper *stepper)
{
    uint8_t invalid = resume_validator(stepper);

    if (invalid)
        return invalid;

    if (stepper->lastState == MOVING) // if stepper was in MOVING state before pause, we need to set target and counter to previous values
    {
        __HAL_TIM_SET_AUTORELOAD(&stepper->slaveTimer, stepper->target);
        __HAL_TIM_SET_COUNTER(&stepper->slaveTimer, stepper->cnt);

        HAL_TIM_Base_Start_IT(&stepper->slaveTimer); // enable slaveTimer
    }

    HAL_TIM_PWM_Start(&stepper->masterTimer, stepper->channel); // enable masterTimer

    stepper->state = stepper->lastState; // recover state

    return ERR.NO_ERROR;
}

uint8_t stepper_stop(Stepper *stepper)
{
    uint8_t invalid = stop_validator(stepper);

    if (invalid)
        return invalid;

    stepper_stopTimers(stepper); // stop timers

    stepper->lastState = stepper->state = ON; // reset stepper state

    return ERR.NO_ERROR;
}

uint8_t stepper_emergency_shutdown(Stepper *stepper)
{
    HAL_GPIO_WritePin((GPIO_TypeDef *)stepper->port, stepper->enable, GPIO_PIN_RESET); // switches the stepper OFF

    stepper->state = OFF; // update stepper state

    return ERR.NO_ERROR;
}