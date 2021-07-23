#include "command/request/request_operator.h"

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

uint8_t **requiredRequestKeys = {0};
uint8_t requiredRequestKeysAmount = 0;

uint8_t (*validateRequestFunction)(Stepper *, uint8_t *, uint8_t *) = NULL;
void (*executeRequestFunction)(Stepper *, uint8_t *, uint8_t *) = NULL;

Stepper *stepper = NULL;
HVD *hvd = NULL;

uint8_t *request_operate(uint8_t *index, uint8_t *operation)
{
    stepper = NULL;
    hvd = NULL;

    if (stringEqual(OPT.CONFIGURE_STEPPER, operation))
    {
        requestType = INSTANT;

        requiredRequestKeys = (uint8_t *[]){KEY.STEPPER, KEY.SPEED, KEY.ACCELERATION};
        requiredRequestKeysAmount = 3;

        validateRequestFunction = &stepper_validateConfigure;
        executeRequestFunction = &stepper_configure;

        stepper = X_STEPPER;
    }

    if (stringEqual(OPT.CONFIGURE_PROCESS, operation))
    {
        requestType = INSTANT;

        requiredRequestKeys = (uint8_t *[]){KEY.DIRECTION};
        requiredRequestKeysAmount = 1;

        validateRequestFunction = &process_validateConfigure;
        executeRequestFunction = &process_init;
    }

    else if (stringEqual(OPT.SWITCH_STEPPER, operation))
    {
        requestType = INSTANT;

        requiredRequestKeys = (uint8_t *[]){KEY.STEPPER, KEY.STATE};
        requiredRequestKeysAmount = 2;

        validateRequestFunction = &stepper_validateSwitch;
        executeRequestFunction = &stepper_switch;

        stepper = X_STEPPER;
    }

    else if (stringEqual(OPT.SWITCH_POMP, operation))
    {
        requestType = INSTANT;

        requiredRequestKeys = (uint8_t *[]){KEY.STATE};
        requiredRequestKeysAmount = 1;

        executeRequestFunction = &hvd_switch;
        hvd = &POMP;
    }

    else if (stringEqual(OPT.SWITCH_TH_PHASE_MOTOR, operation))
    {
        requestType = INSTANT;

        requiredRequestKeys = (uint8_t *[]){KEY.STATE};
        requiredRequestKeysAmount = 1;

        executeRequestFunction = &hvd_switch;
        hvd = &TH_PHASE_MOTOR;
    }

    else if (stringEqual(OPT.MOVE_STEPPER, operation))
    {
        requestType = LONG_TERM;

        requiredRequestKeys = (uint8_t *[]){KEY.STEPPER, KEY.WAY, KEY.DIRECTION};
        requiredRequestKeysAmount = 3;

        validateRequestFunction = &stepper_validateMove;
        executeRequestFunction = &stepper_move;

        stepper = X_STEPPER;
    }

    else if (stringEqual(OPT.PAUSE_STEPPER, operation))
    {
        requestType = INSTANT;

        requiredRequestKeys = (uint8_t *[]){KEY.STEPPER};
        requiredRequestKeysAmount = 1;

        validateRequestFunction = &stepper_validatePause;
        executeRequestFunction = &stepper_pause;

        stepper = X_STEPPER;
    }

    else if (stringEqual(OPT.RESUME_STEPPER, operation))
    {
        requestType = INSTANT;

        requiredRequestKeys = (uint8_t *[]){KEY.STEPPER};
        requiredRequestKeysAmount = 1;

        validateRequestFunction = &stepper_validateResume;
        executeRequestFunction = &stepper_resume;

        stepper = X_STEPPER;
    }

    else if (stringEqual(OPT.STOP_STEPPER, operation))
    {
        requestType = INSTANT;

        requiredRequestKeys = (uint8_t *[]){KEY.STEPPER};
        requiredRequestKeysAmount = 1;

        validateRequestFunction = &stepper_validateStop;
        executeRequestFunction = &stepper_stop;

        stepper = X_STEPPER;
    }

    else if (stringEqual(OPT.PAUSE_PROCESS, operation))
    {
        requestType = INSTANT;

        validateRequestFunction = &process_validatePause;
        executeRequestFunction = &process_pause;
    }

    else if (stringEqual(OPT.RESUME_PROCESS, operation))
    {
        requestType = INSTANT;

        validateRequestFunction = &process_validateResume;
        executeRequestFunction = &process_resume;
    }

    else if (stringEqual(OPT.STOP_PROCESS, operation))
    {
        requestType = INSTANT;

        validateRequestFunction = &process_validateStop;
        executeRequestFunction = &process_stop;
    }

    else if (stringEqual(OPT.GET_ALL_STATES, operation))
    {
        requestType = INSTANT;
        executeRequestFunction = &device_manager_getAllDevicesStates;
    }

    else
    {
        return response_builder_buildErr(index, ERR.INVALID_OPERATION_VALUE);
    }

    return EMPTY;
}