#include "device/stepper/partial/stepper_intervention.h"

#include "device/stepper/partial/stepper_peripheral.h"
#include "device/stepper/partial/stepper_configuration.h"
#include "device/stepper/partial/stepper_helper.h"
#include "device/stepper/partial/stepper_calculator.h"

void stepper_pause(Stepper *stepper, uint8_t *EMPTY1, uint8_t *EMPTY2)
{
    if (stepper_getMoveType(stepper) == PRECISED) // if stepper is in MOVING state i need to remember register values TARGET and COUNTER
    {
        uint16_t rest = calculateRemainingSteps(stepper);

        // TIM2 and TIM5 are 32-bit timers and there is something like, that i need to decrease arr for them
        if (rest > 0 && (stepper_getSlaveTimer(stepper)->Instance == TIM2 || stepper_getSlaveTimer(stepper)->Instance == TIM5))
            rest--;

        stepper_setRest(stepper, rest);
    }

    stepper_stopTimers(stepper); // stop timers

    stepper_setSpeedState(stepper, CONSTANT);

    stepper_setState(stepper, PAUSED); // update current state
}

void stepper_resume(Stepper *stepper, uint8_t *EMPTY1, uint8_t *EMPTY2)
{
    if (stepper_getMoveType(stepper) == PRECISED)
    {
        __HAL_TIM_SET_COUNTER(stepper_getSlaveTimer(stepper), 0);
        __HAL_TIM_SET_AUTORELOAD(stepper_getSlaveTimer(stepper), stepper_getRest(stepper));
        HAL_TIM_Base_Start_IT(stepper_getSlaveTimer(stepper)); // enable slaveTimer
    }

    HAL_TIM_PWM_Start(&stepper->hardware.masterTimer, stepper->hardware.channel); // enable masterTimer

    // stepper_initAcceleration(stepper, RAISING);
    stepper_setState(stepper, MOVING); // recover state
}

void stepper_stop(Stepper *stepper, uint8_t *EMPTY1, uint8_t *EMPTY2)
{
    stepper_stopTimers(stepper);
    stepper_resetSpeed(stepper);

    stepper_setUnloadedSteps(stepper, 0);
    stepper_setState(stepper, ON);
}
