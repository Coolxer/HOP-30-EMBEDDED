#include "process/partial/process_operation.h"

#include "null.h"

#include "process/process.h"
#include "device/device_manager.h"
#include "device/low_voltage/stepper/partial/stepper_operation.h"
#include "device/low_voltage/stepper/partial/stepper_configuration.h"

void process_init(uint8_t *idx)
{
    stepper_switch(X_STEPPER, UP, EMPTY);
    stepper_switch(W_STEPPER, UP, EMPTY);

    hvd_switch(&POMP, ON);
    hvd_switch(&TH_PHASE_MOTOR, ON);

    stepper_run(X_STEPPER);
    stepper_run(W_STEPPER);

    stepper_setIndex(X_STEPPER, idx);
    stepper_setIndex(W_STEPPER, idx);

    PROCESS_STATE = FORWARD;
}

void process_reverse()
{
    stepper_changeDirectionImmediately(X_STEPPER);
    stepper_changeDirectionImmediately(W_STEPPER);

    stepper_setCurrentSpeed(X_STEPPER, 0.0f);
    stepper_setCurrentSpeed(W_STEPPER, 0.0f);

    PROCESS_STATE = BACKWARD;
}