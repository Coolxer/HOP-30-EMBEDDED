#include "process/partial/process_operation.h"

#include "null.h"

#include "process/process.h"
#include "device/device_manager.h"
#include "device/low_voltage/stepper/partial/stepper_operation.h"
#include "device/low_voltage/stepper/partial/stepper_configuration.h"

#include "device/low_voltage/stepper/partial/stepper_calculator.h"

void process_init()
{
    stepper_switch(A_STEPPER, ON);
    stepper_switch(Y_STEPPER, ON);

    if (COOLANT_ENABLE)
        hvd_switch(&POMP, ON);

    hvd_switch(&TH_PHASE_MOTOR, ON);

    PROCESS_STATE = FORWARD;
    PROCESS_CONFIGURED = 0;

    stepper_run(A_STEPPER);
    stepper_run(Y_STEPPER);
}

void process_reverse()
{
    stepper_changeDirectionImmediately(A_STEPPER);
    stepper_changeDirectionImmediately(Y_STEPPER);

    stepper_setCurrentSpeed(A_STEPPER, MINIMUM_NOTICEABLED_SPEED);
    stepper_setCurrentSpeed(Y_STEPPER, MINIMUM_NOTICEABLED_SPEED);

    PROCESS_STATE = BACKWARD;
}