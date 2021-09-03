#include "device/low_voltage/endstop/partial/endstop_callback.h"

#include <string.h>

#include "command/response/response_builder.h"
#include "communication/uart.h"

#include "device/device_manager.h"

#include "device/low_voltage/stepper/stepper.h"
#include "device/low_voltage/stepper/partial/stepper_helper.h"
#include "device/low_voltage/stepper/partial/stepper_intervention.h"

#include "process/partial/process_operation.h"
#include "process/process.h"

#include "command/cmd_manager.h"

// [CALLED FROM MAIN LOOP]
void endstopClickedCallback(Endstop *endstop)
{
    Stepper *stepper = device_manager_findParentStepper(endstop);

    if (stepper_getState(stepper) != MOVING)
        return;

    if ((endstop == stepper->minEndstop && !stepper_getDirection(stepper)) ||
        (endstop == stepper->maxEndstop && stepper_getDirection(stepper)))
    {
        if (PROCESS_STATE == FORWARD)
            process_reverse();
        else
        {
            if (PROCESS_STATE == BACKWARD)
            {
                stepper_stop(A_STEPPER);
                stepper_stop(Y_STEPPER);
                PROCESS_STATE = NONE;
            }
            else
                stepper_stop(stepper);

            justRegisteredCallbackResponseIndex = (justRegisteredCallbackResponseIndex < MAX_BUFFER_RESPONSES) ? justRegisteredCallbackResponseIndex + 1 : MAX_BUFFER_REQUESTS + 1;
            strcpy((void *)RESPONSES[justRegisteredCallbackResponseIndex], (void *)response_builder_buildFin(stepper_getIndex(stepper)));
            awaitingResponsesAmount++;
        }
    }
}