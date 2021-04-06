#include "device/stepper/partial/stepper_intervention.h"

#include "device/stepper/partial/stepper_peripheral.h"
#include "device/stepper/partial/stepper_configuration.h"
#include "device/stepper/partial/stepper_helper.h"

void stepper_pause(Stepper *stepper)
{
    if (getMoveType(stepper) == PRECISED) // if stepper is in MOVING state i need to remember register values TARGET and COUNTER
    {
        uint16_t rest = (uint16_t)(getCurrentTarget(stepper) - getProgress(stepper));

        // TIM2 and TIM5 are 32-bit timers and there is something like, that i need to decrease arr for them
        if (rest > 0 && (getSlaveTimer(stepper)->Instance == TIM2 || getSlaveTimer(stepper)->Instance == TIM5))
            rest--;

        setRest(stepper, rest);
    }

    stepper_stopTimers(stepper); // stop timers

    // service speed state
    setSpeedState(stepper, CONSTANT);
    setCurrentSpeed(stepper, 0.0f);

    setState(stepper, PAUSED); // update current state
}

void stepper_resume(Stepper *stepper)
{
    if (getMoveType(stepper) == PRECISED)
    {
        __HAL_TIM_SET_COUNTER(getSlaveTimer(stepper), 0);
        __HAL_TIM_SET_AUTORELOAD(getSlaveTimer(stepper), getRest(stepper));
        HAL_TIM_Base_Start_IT(getSlaveTimer(stepper)); // enable slaveTimer
    }

    HAL_TIM_PWM_Start(&stepper->hardware.masterTimer, stepper->hardware.channel); // enable masterTimer

    stepper_initAcceleration(stepper, RAISING);
    setState(stepper, MOVING); // recover state
}

void stepper_stop(Stepper *stepper)
{
    stepper_stopTimers(stepper);
    stepper_resetSpeed(stepper);

    setTarget(stepper, 0);
    setState(stepper, ON);
}

void stepper_emergency_shutdown(Stepper *stepper)
{
    HAL_GPIO_WritePin((GPIO_TypeDef *)stepper->hardware.port, stepper->hardware.enable, GPIO_PIN_RESET); // switches the stepper OFF

    stepper_stop(stepper);
    setState(stepper, OFF);
}