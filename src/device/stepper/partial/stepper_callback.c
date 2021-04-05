#include "device/stepper/partial/stepper_callback.h"

#include "device/stepper/partial/stepper_peripheral.h"
#include "device/stepper/partial/stepper_configuration.h"
#include "device/stepper/partial/stepper_intervention.h"
#include "device/stepper/partial/stepper_operation.h"
#include "device/stepper/partial/stepper_helper.h"

#include "command/cmd_builder.h"
#include "communication/uart.h"

//  [CALLED FROM MAIN LOOP]
void stepperFinishedCallback(Stepper *stepper)
{
    // stepper counted up, try to reload registers, if not it is really end
    uint8_t reload = stepper_reload(stepper);

    if (!reload)
    {
        stepper_stop(stepper);
        setFinishedFlag(stepper, RESET);

        // if the movoment was homing'outgoing, then continue move
        if (getHomeStep(stepper) == SLOW_FORWARD)
            stepper_home(stepper, PRECISE_BACKWARD);

        else // if the movement was simple movement by user typing
            uart_send(cmd_builder_buildFin(getIndex(stepper)));
    }
}
