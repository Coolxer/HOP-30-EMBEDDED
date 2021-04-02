#include "device/stepper/partial/stepper_intervention.h"

#include "device/stepper/partial/stepper_state_manager.h"
#include "device/stepper/partial/stepper_peripheral.h"
#include "device/stepper/partial/stepper_configuration.h"

void stepper_pause(Stepper *stepper)
{
    if (stepper_isState(stepper, MOVING)) // if stepper is in MOVING state i need to remember register values TARGET and COUNTER
    {
        uint16_t rest = (uint16_t)(stepper->hardware.slaveTimer.Instance->ARR - stepper->hardware.slaveTimer.Instance->CNT); // MAX_16BITVALUE

        // TIM2 and TIM5 are 32-bit timers and there is something like, that i need to decrease arr for them
        if (rest > 0 && (stepper->hardware.slaveTimer.Instance == TIM2 || stepper->hardware.slaveTimer.Instance == TIM5))
            rest--;

        stepper->movement.rest = rest;
    }

    stepper_stopTimers(stepper); // stop timers

    stepper->speed.lastState = stepper->speed.state;
    stepper->speed.state = CONSTANT;
    stepper->speed.current = 0.0f;

    stepper_updateLastState(stepper);  // save current state to recover
    stepper_setState(stepper, PAUSED); // update current state
}

void stepper_resume(Stepper *stepper)
{
    // if stepper was in MOVING state before pause, we need to set target and counter to previous values
    if (stepper_getLastState(stepper) == MOVING)
    {
        __HAL_TIM_SET_COUNTER(&stepper->hardware.slaveTimer, 0);
        __HAL_TIM_SET_AUTORELOAD(&stepper->hardware.slaveTimer, stepper->movement.rest);
        HAL_TIM_Base_Start_IT(&stepper->hardware.slaveTimer); // enable slaveTimer
    }

    HAL_TIM_PWM_Start(&stepper->hardware.masterTimer, stepper->hardware.channel); // enable masterTimer

    stepper->speed.state = stepper->speed.lastState;
    stepper_initAcceleration(stepper, RAISING);

    stepper_setState(stepper, stepper_getLastState(stepper)); // recover state
}

void stepper_stop(Stepper *stepper)
{
    stepper_stopTimers(stepper);
    stepper_resetSpeed(stepper);

    stepper->movement.target = 0;

    stepper_updateStates(stepper, ON);
    stepper_setHomeStep(stepper, FAST_BACKWARD);
}

void stepper_emergency_shutdown(Stepper *stepper)
{
    HAL_GPIO_WritePin((GPIO_TypeDef *)stepper->hardware.port, stepper->hardware.enable, GPIO_PIN_RESET); // switches the stepper OFF

    stepper_stop(stepper);
    stepper_setState(stepper, OFF);
}