#include "process.h"

#include "null.h"

#include "validator.h"
#include "command/builder/partial/err.h"

#include "device/low_voltage/stepper/partial/stepper_configuration.h"
#include "device/low_voltage/stepper/partial/stepper_operation.h"
#include "device/low_voltage/stepper/partial/stepper_helper.h"

volatile enum ProcessState PROCESSING = NONE;

uint8_t process_validate(uint8_t *direction)
{
    // check if direction value is correct
    if (validate_boolean(direction) == ERR.ERROR)
        return ERR.INVALID_DIRECTION_VALUE;

    else if (stepper_getState(X_STEPPER) == MOVING || stepper_getState(W_STEPPER) == MOVING)
        return ERR.OPERATION_NOT_ALLOWED;

    return ERR.NO_ERROR;
}

void process_init(uint8_t *idx, uint8_t direction)
{
    stepper_setDirection(X_STEPPER, RIGHT);
    stepper_setDirection(W_STEPPER, direction);

    stepper_switch(X_STEPPER, UP, EMPTY);
    stepper_switch(W_STEPPER, UP, EMPTY);

    stepper_run(X_STEPPER);
    stepper_run(W_STEPPER);

    stepper_setIndex(X_STEPPER, idx);
    stepper_setIndex(W_STEPPER, idx);

    PROCESSING = FORWARD;
}

void process_reverse()
{
    stepper_changeDirectionImmediately(X_STEPPER);
    stepper_changeDirectionImmediately(W_STEPPER);

    stepper_setCurrentSpeed(X_STEPPER, 0.0f);
    stepper_setCurrentSpeed(W_STEPPER, 0.0f);

    PROCESSING = BACKWARD;
}
