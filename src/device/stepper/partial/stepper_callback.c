#include "device/stepper/partial/stepper_callback.h"

#include "device/stepper/partial/stepper_peripheral.h"
#include "device/stepper/partial/stepper_intervention.h"
#include "device/stepper/partial/stepper_helper.h"

#include "command/cmd_builder.h"
#include "communication/uart.h"

//  [CALLED FROM MAIN LOOP]
void stepperFinishedCallback(Stepper *stepper)
{
    stepper->movement.FINISHED_FLAG = RESET;

    // stepper counted up, try to reload registers, if not it is really end
    if (stepper_reload(stepper))
        return;

    stepper_stop(stepper);
    uart_send(cmd_builder_buildFin(getIndex(stepper)));
}
