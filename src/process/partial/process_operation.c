#include "process/partial/process_operation.h"

#include "null.h"

#include "process/process.h"
#include "device/device_manager.h"
#include "device/low_voltage/stepper/partial/stepper_operation.h"
#include "device/low_voltage/stepper/partial/stepper_configuration.h"

#include "device/low_voltage/stepper/partial/stepper_calculator.h"

void process_init()
{
    stepper_switch(X_STEPPER, ON);
    stepper_switch(W_STEPPER, ON);

    if (COOLANT_ENABLE)
        hvd_switch(&POMP, ON);

    hvd_switch(&TH_PHASE_MOTOR, ON);

    PROCESS_STATE = FORWARD;
    PROCESS_CONFIGURED = 0;

    stepper_run(X_STEPPER);
    stepper_run(W_STEPPER);
}

void process_reverse()
{
    stepper_changeDirectionImmediately(X_STEPPER);
    stepper_changeDirectionImmediately(W_STEPPER);

    stepper_setCurrentSpeed(X_STEPPER, MINIMUM_NOTICEABLED_SPEED);
    stepper_setCurrentSpeed(W_STEPPER, MINIMUM_NOTICEABLED_SPEED);

    PROCESS_STATE = BACKWARD;
}