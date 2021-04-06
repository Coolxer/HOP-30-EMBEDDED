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

    if (PROCESSING)
        process_reverse();
    else if (getState(stepper) == MOVING)
    {
        if ((endstop == stepper->minEndstop && getDirection(stepper) == LEFT) ||
            (endstop == stepper->maxEndstop && getDirection(stepper) == RIGHT))
        {
            stepper_stop(stepper);

            uart_send(cmd_builder_buildFin(getIndex(stepper)));
        }
    }
}