#include "command/request/request_operator.h"

#include <string.h>

#include "null.h"
#include "data_assistant.h"

#include "command/response/response_builder.h"

#include "device/device_manager.h"

#include "device/low_voltage/stepper/partial/stepper_validator.h"
#include "device/low_voltage/stepper/partial/stepper_configuration.h"
#include "device/low_voltage/stepper/partial/stepper_operation.h"
#include "device/low_voltage/stepper/partial/stepper_intervention.h"

#include "device/high_voltage/hvd.h"

#include "process/partial/process_validator.h"
#include "process/partial/process_operation.h"
#include "process/partial/process_intervention.h"

enum RequestType requestType;

uint8_t *requiredKeys[MAX_REQUIRED_KEYS_AMOUNT] = {""};
uint8_t requiredKeysAmount = 0;

uint8_t (*validateRequestFunction)() = NULL;
void (*executeRequestFunction)() = NULL;

uint8_t numberOfValuesToValidate = 0;

Stepper *stepper = NULL;
HVD *hvd = NULL;

uint8_t *request_operate(uint8_t *index, uint8_t *operation)
{
    stepper = NULL;
    hvd = NULL;

    if (stringEqual(OPT.CONFIGURE_STEPPER, operation))
    {
        requestType = INSTANT;

        requiredKeys[0] = KEY.STEPPER;
        requiredKeys[1] = KEY.SPEED;
        requiredKeys[2] = KEY.ACCELERATION;
        requiredKeysAmount = 3;

        validateRequestFunction = &stepper_validateConfigure;
        executeRequestFunction = &stepper_configure;

        numberOfValuesToValidate = 2;

        stepper = X_STEPPER;

        return EMPTY;
    }

    else if (stringEqual(OPT.CONFIGURE_PROCESS, operation))
    {
        requestType = INSTANT;

        requiredKeys[0] = KEY.DIRECTION;
        requiredKeysAmount = 1;

        validateRequestFunction = &process_validateConfigure;
        executeRequestFunction = &process_init;

        return EMPTY;
    }

    else if (stringEqual(OPT.SWITCH_STEPPER, operation))
    {
        requestType = INSTANT;

        requiredKeys[0] = KEY.STEPPER;
        requiredKeys[1] = KEY.STATE;
        requiredKeysAmount = 2;

        validateRequestFunction = &stepper_validateSwitch;
        executeRequestFunction = &stepper_switch;

        numberOfValuesToValidate = 1;

        stepper = X_STEPPER;

        return EMPTY;
    }

    else if (stringEqual(OPT.SWITCH_POMP, operation))
    {
        requestType = INSTANT;

        requiredKeys[0] = KEY.STATE;
        requiredKeysAmount = 1;

        validateRequestFunction = NULL;
        executeRequestFunction = &hvd_switch;

        numberOfValuesToValidate = 1;

        hvd = &POMP;

        return EMPTY;
    }

    else if (stringEqual(OPT.SWITCH_TH_PHASE_MOTOR, operation))
    {
        requestType = INSTANT;

        requiredKeys[0] = KEY.STATE;
        requiredKeysAmount = 1;

        validateRequestFunction = NULL;
        executeRequestFunction = &hvd_switch;

        numberOfValuesToValidate = 1;

        hvd = &TH_PHASE_MOTOR;

        return EMPTY;
    }

    else if (stringEqual(OPT.MOVE_STEPPER, operation))
    {
        requestType = LONG_TERM;

        requiredKeys[0] = KEY.STEPPER;
        requiredKeys[1] = KEY.WAY;
        requiredKeys[2] = KEY.DIRECTION;
        requiredKeysAmount = 3;

        validateRequestFunction = &stepper_validateMove;
        executeRequestFunction = &stepper_move;

        numberOfValuesToValidate = 2;

        stepper = X_STEPPER;

        return EMPTY;
    }

    else if (stringEqual(OPT.PAUSE_STEPPER, operation))
    {
        requestType = INSTANT;

        requiredKeys[0] = KEY.STEPPER;
        requiredKeysAmount = 1;

        validateRequestFunction = &stepper_validatePause;
        executeRequestFunction = &stepper_pause;

        numberOfValuesToValidate = 0;

        stepper = X_STEPPER;

        return EMPTY;
    }

    else if (stringEqual(OPT.RESUME_STEPPER, operation))
    {
        requestType = INSTANT;

        requiredKeys[0] = KEY.STEPPER;
        requiredKeysAmount = 1;

        validateRequestFunction = &stepper_validateResume;
        executeRequestFunction = &stepper_resume;

        numberOfValuesToValidate = 0;

        stepper = X_STEPPER;

        return EMPTY;
    }

    else if (stringEqual(OPT.STOP_STEPPER, operation))
    {
        requestType = INSTANT;

        requiredKeys[0] = KEY.STEPPER;
        requiredKeysAmount = 1;

        validateRequestFunction = &stepper_validateStop;
        executeRequestFunction = &stepper_stop;

        numberOfValuesToValidate = 0;

        stepper = X_STEPPER;

        return EMPTY;
    }

    else if (stringEqual(OPT.PAUSE_PROCESS, operation))
    {
        requestType = INSTANT;

        requiredKeysAmount = 0;

        validateRequestFunction = &process_validatePause;
        executeRequestFunction = &process_pause;

        numberOfValuesToValidate = 0;

        return EMPTY;
    }

    else if (stringEqual(OPT.RESUME_PROCESS, operation))
    {
        requestType = INSTANT;

        requiredKeysAmount = 0;

        validateRequestFunction = &process_validateResume;
        executeRequestFunction = &process_resume;

        numberOfValuesToValidate = 0;

        return EMPTY;
    }

    else if (stringEqual(OPT.STOP_PROCESS, operation))
    {
        requestType = INSTANT;

        requiredKeysAmount = 0;

        validateRequestFunction = &process_validateStop;
        executeRequestFunction = &process_stop;

        numberOfValuesToValidate = 0;

        return EMPTY;
    }

    else if (stringEqual(OPT.GET_ALL_STATES, operation))
    {
        requestType = INSTANT;

        requiredKeysAmount = 0;

        validateRequestFunction = NULL;
        executeRequestFunction = &device_manager_getAllDevicesStates;

        numberOfValuesToValidate = 0;

        return EMPTY;
    }

    return response_builder_buildErr(index, ERR.INVALID_OPERATION_VALUE);
}