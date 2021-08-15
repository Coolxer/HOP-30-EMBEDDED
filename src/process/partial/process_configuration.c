#include "process/partial/process_configuration.h"

#include "data/assistant.h"
#include "process/process.h"

#include "device/device_manager.h"
#include "device/low_voltage/stepper./partial/stepper_configuration.h"

void process_configure(uint8_t *direction, uint8_t *coolant)
{
    stepper_setDirection(X_STEPPER, LEFT);
    stepper_setDirection(W_STEPPER, direction);

    COOLANT_ENABLE = convertStrToBoolean(coolant);
}
