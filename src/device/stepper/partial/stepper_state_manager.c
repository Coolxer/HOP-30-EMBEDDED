#include "device/stepper/partial/stepper_state_manager.h"

/* State */

uint8_t stepper_getState(Stepper *stepper)
{
    return stepper->instance.state;
}

uint8_t stepper_getLastState(Stepper *stepper)
{
    return stepper->instance.lastState;
}

uint8_t stepper_isState(Stepper *stepper, uint8_t state)
{
    return stepper->instance.state == state;
}

void stepper_setState(Stepper *stepper, uint8_t state)
{
    stepper->instance.state = state;
}

void stepper_updateStates(Stepper *stepper, uint8_t state)
{
    stepper->instance.state = stepper->instance.lastState = state;
}

void stepper_updateLastState(Stepper *stepper)
{
    stepper->instance.lastState = stepper_getState(stepper);
}

/* Home step */

uint8_t stepper_getHomeStep(Stepper *stepper)
{
    return stepper->instance.homeStep;
}

uint8_t stepper_getLastHomeStep(Stepper *stepper)
{
    return stepper->instance.lastHomeStep;
}

uint8_t stepper_isHomeStep(Stepper *stepper, uint8_t step)
{
    return stepper->instance.homeStep == step;
}

void stepper_setHomeStep(Stepper *stepper, uint8_t step)
{
    stepper->instance.homeStep = step;
}

void stepper_updateLastHomeStep(Stepper *stepper)
{
    stepper->instance.lastHomeStep = stepper_getHomeStep(stepper);
}
