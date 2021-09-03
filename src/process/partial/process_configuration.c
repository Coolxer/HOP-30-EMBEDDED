#include "process/partial/process_configuration.h"

#include "data/assistant.h"
#include "process/process.h"

#include "device/device_manager.h"
#include "device/low_voltage/stepper./partial/stepper_configuration.h"

#include "device/low_voltage/endstop/partial/endstop_operation.h"
#include "process/partial/process_operation.h"

void process_configure(uint8_t *direction, uint8_t *coolant)
{
    stepper_setDirection(Y_STEPPER, LEFT);
    stepper_setDirection(A_STEPPER, direction);

    COOLANT_ENABLE = convertStrToBoolean(coolant);

    if (endstop_isClicked(Y_STEPPER->minEndstop))
        process_reverse();

    PROCESS_CONFIGURED = 1;
}
