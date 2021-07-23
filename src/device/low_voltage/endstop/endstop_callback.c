#include "device/low_voltage/endstop/partial/endstop_callback.h"

//#include "command/response_builder.h"
#include "communication/uart.h"

#include "device/low_voltage/stepper/stepper.h"
#include "device/low_voltage/stepper/partial/stepper_helper.h"
#include "device/low_voltage/stepper/partial/stepper_intervention.h"

#include "process/process.h"

// [CALLED FROM MAIN LOOP]
void endstopClickedCallback(Endstop *endstop)
{
    Stepper *stepper = device_manager_findParentStepper(endstop);

    if (stepper_getState(stepper) != MOVING)
        return;

    if ((endstop == stepper->minEndstop && stepper_getDirection(stepper) == LEFT) ||
        (endstop == stepper->maxEndstop && stepper_getDirection(stepper) == RIGHT))
    {
        if (PROCESS_STATE == FORWARD)
            process_reverse();
        else
        {
            if (PROCESS_STATE == BACKWARD)
            {
                // TODO
                //stepper_stop(X_STEPPER);
                //stepper_stop(W_STEPPER);
                PROCESS_STATE = NONE;
            }
            // TODO
            //else
            //    stepper_stop(stepper);

            // TODO
            //uart_send(cmd_builder_buildFin(stepper_getIndex(stepper)));
        }
    }
}