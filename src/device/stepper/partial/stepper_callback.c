#include "device/stepper/partial/stepper_callback.h"

#include "enum/type.h"

#include "device/stepper/partial/stepper_peripheral.h"
#include "device/stepper/partial/stepper_state_manager.h"
#include "device/stepper/partial/stepper_operation.h"

#include "command/cmd_builder.h"
#include "communication/uart.h"

//  [CALLED FROM MAIN LOOP]
void stepperFinishedCallback(Stepper *stepper)
{
    stepper_stopTimers(stepper);

    if (stepper_isState(stepper, HOMING) && stepper_isHomeStep(stepper, BACKWARD))
        stepper_home(stepper, PRECISE);
    else if (stepper_manageSlaveTimer(stepper) == NOT_RELOADED)
    {
        stepper_updateStates(stepper, ON);
        uart_send(cmd_builder_buildFin(stepper->info.index));
    }
}
