#include "process/process.h"

#include "null.h"

#include "validator.h"
#include "command/partial/err.h"

#include "device/low_voltage/stepper/partial/stepper_configuration.h"
#include "device/low_voltage/stepper/partial/stepper_operation.h"
#include "device/low_voltage/stepper/partial/stepper_helper.h"

volatile enum ProcessState PROCESS_STATE = NONE;
volatile enum ProcessState PROCESS_PREVIOUS_STATE = NONE;
