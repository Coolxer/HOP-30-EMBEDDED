#include "device/stepper/partial/stepper_intervention.h"

#include "device/stepper/partial/stepper_peripheral.h"
#include "device/stepper/partial/stepper_configuration.h"
#include "device/stepper/partial/stepper_helper.h"

void stepper_pause(Stepper *stepper)
{
    if (getState(stepper) == MOVING) // if stepper is in MOVING state i need to remember register values TARGET and COUNTER
    {
        uint16_t rest = (uint16_t)(getCurrentDestination(stepper) - getProgress(stepper)); // MAX_16BITVALUE

        // TIM2 and TIM5 are 32-bit timers and there is something like, that i need to decrease arr for them
        if (rest > 0 && (getSlaveTimer(stepper)->Instance == TIM2 || getSlaveTimer(stepper)->Instance == TIM5))
            rest--;

        setRest(stepper, rest);
    }

    stepper_stopTimers(stepper); // stop timers

    updateLastSpeedState(stepper);
    setSpeedState(stepper, CONSTANT);
    setCurrentSpeed(stepper, 0.0f);

    updateLastState(stepper);  // save current state to recover
    setState(stepper, PAUSED); // update current state
}

void stepper_resume(Stepper *stepper)
{
    // if stepper was in MOVING state before pause, we need to set target and counter to previous values
    if (getLastState(stepper) == MOVING)
    {
        __HAL_TIM_SET_COUNTER(getSlaveTimer(stepper), 0);
        __HAL_TIM_SET_AUTORELOAD(getSlaveTimer(stepper), getRest(stepper));
        HAL_TIM_Base_Start_IT(getSlaveTimer(stepper)); // enable slaveTimer
    }

    HAL_TIM_PWM_Start(&stepper->hardware.masterTimer, stepper->hardware.channel); // enable masterTimer

    setSpeedState(stepper, getLastSpeedState(stepper));
    stepper_initAcceleration(stepper, RAISING);

    setState(stepper, getLastState(stepper)); // recover state
}

void stepper_stop(Stepper *stepper)
{
    stepper_stopTimers(stepper);
    stepper_resetSpeed(stepper);

    setGeneralTarget(stepper, 0);
    setState(stepper, ON);
    setHomeStep(stepper, FAST_BACKWARD);
}

void stepper_emergency_shutdown(Stepper *stepper)
{
    HAL_GPIO_WritePin((GPIO_TypeDef *)stepper->hardware.port, stepper->hardware.enable, GPIO_PIN_RESET); // switches the stepper OFF

    stepper_stop(stepper);
    setState(stepper, OFF);
}