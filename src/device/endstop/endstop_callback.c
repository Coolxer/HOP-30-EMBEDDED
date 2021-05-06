#include "device/endstop/partial/endstop_callback.h"

#include "command/cmd_builder.h"
#include "communication/uart.h"

#include "device/stepper/stepper.h"
#include "device/stepper/partial/stepper_helper.h"
#include "device/stepper/partial/stepper_intervention.h"

#include "process.h"

// [CALLED FROM MAIN LOOP]
void endstopClickedCallback(Endstop *endstop)
{
    Stepper *stepper = device_manager_findParentStepper(endstop);

    if (stepper_getState(stepper) != MOVING)
        return;

    if ((endstop == stepper->minEndstop && stepper_getDirection(stepper) == LEFT) ||
        (endstop == stepper->maxEndstop && stepper_getDirection(stepper) == RIGHT))
    {
        if (PROCESSING == FORWARD)
            process_reverse();
        else
        {
            if (PROCESSING == BACKWARD)
            {
                stepper_stop(X_STEPPER);
                stepper_stop(W_STEPPER);
                PROCESSING = NONE;
            }
            else
                stepper_stop(stepper);

            uart_send(cmd_builder_buildFin(stepper_getIndex(stepper)));
        }
    }
}