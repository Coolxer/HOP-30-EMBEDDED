#include "process.h"

#include "validator.h"
#include "command/partial/err.h"

#include "device/stepper/partial/stepper_configuration.h"
#include "device/stepper/partial/stepper_operation.h"
#include "device/stepper/partial/stepper_helper.h"

volatile uint8_t PROCESSING = 0;

void process_init(uint8_t *idx, uint8_t direction)
{
    stepper_setDirection(X_STEPPER, RIGHT);
    stepper_setDirection(W_STEPPER, direction);

    stepper_switch(X_STEPPER, UP);
    stepper_switch(W_STEPPER, UP);

    stepper_run(X_STEPPER);
    stepper_run(W_STEPPER);

    setIndex(X_STEPPER, idx);
    setIndex(W_STEPPER, idx);

    PROCESSING = 1;
}

void process_reverse()
{
    stepper_changeDirectionImmediately(X_STEPPER);
    stepper_changeDirectionImmediately(W_STEPPER);

    setCurrentSpeed(X_STEPPER, 0.0f);
    setCurrentSpeed(W_STEPPER, 0.0f);

    if (getSpeedType(X_STEPPER) == DYNAMIC)
    {
        setSpeedState(X_STEPPER, RAISING);
        setSpeedState(W_STEPPER, RAISING);
    }
}

uint8_t process_validate(uint8_t *direction)
{
    // check if direction value is correct
    if (validate_boolean(direction) == ERR.ERROR)
        return ERR.INVALID_DIRECTION_VALUE;

    return ERR.NO_ERROR;
}