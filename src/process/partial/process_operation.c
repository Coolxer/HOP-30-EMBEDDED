#include "process/partial/process_operation.h"

#include "null.h"

#include "process/process.h"
#include "device/device_manager.h"
#include "device/low_voltage/stepper/partial/stepper_operation.h"
#include "device/low_voltage/stepper/partial/stepper_configuration.h"

void process_init(uint8_t *index)
{
    stepper_switch(X_STEPPER, ON);
    stepper_switch(W_STEPPER, ON);

    if (COOLANT_ENABLE)
        hvd_switch(&POMP, ON);

    hvd_switch(&TH_PHASE_MOTOR, ON);

    stepper_setIndex(X_STEPPER, index);
    stepper_setIndex(W_STEPPER, index);
    PROCESS_STATE = FORWARD;

    stepper_run(X_STEPPER);
    stepper_run(W_STEPPER);
}

void process_reverse()
{
    stepper_changeDirectionImmediately(X_STEPPER);
    stepper_changeDirectionImmediately(W_STEPPER);

    stepper_setCurrentSpeed(X_STEPPER, 0.0f);
    stepper_setCurrentSpeed(W_STEPPER, 0.0f);

    PROCESS_STATE = BACKWARD;
}