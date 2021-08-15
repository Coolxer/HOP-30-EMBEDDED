#include "command/request/request_operator.h"

#include <string.h>

#include "null.h"
#include "data/assistant.h"

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
#include "process/partial/process_configuration.h"

Request request_operate(uint8_t *operation)
{
    /* STEPPER REQUESTS */

    if (stringEqual(OPT.CONFIGURE_STEPPER, operation))
        return request_init(INSTANT, KEY.STEPPER, KEY.SPEED, KEY.ACCELERATION, 3, &stepper_validateConfigure, &stepper_configure, 2, X_STEPPER, NULL);

    else if (stringEqual(OPT.SWITCH_STEPPER, operation))
        return request_init(INSTANT, KEY.STEPPER, KEY.STATE, EMPTY_STRING, 2, &stepper_validateSwitch, &stepper_switch, 1, X_STEPPER, NULL);

    else if (stringEqual(OPT.MOVE_STEPPER, operation))
        return request_init(LONG_TERM, KEY.STEPPER, KEY.WAY, KEY.DIRECTION, 3, &stepper_validateMove, &stepper_move, 2, X_STEPPER, NULL);

    else if (stringEqual(OPT.PAUSE_STEPPER, operation))
        return request_init(INSTANT, KEY.STEPPER, EMPTY_STRING, EMPTY_STRING, 1, &stepper_validatePause, &stepper_pause, 0, X_STEPPER, NULL);

    else if (stringEqual(OPT.RESUME_STEPPER, operation))
        return request_init(INSTANT, KEY.STEPPER, EMPTY_STRING, EMPTY_STRING, 1, &stepper_validateResume, &stepper_resume, 0, X_STEPPER, NULL);

    else if (stringEqual(OPT.STOP_STEPPER, operation))
        return request_init(INSTANT, KEY.STEPPER, EMPTY_STRING, EMPTY_STRING, 1, &stepper_validateStop, &stepper_stop, 0, X_STEPPER, NULL);

    /* POMP AND TH_PHASE_MOTOR REQUESTS */

    else if (stringEqual(OPT.SWITCH_POMP, operation))
        return request_init(INSTANT, KEY.STATE, EMPTY_STRING, EMPTY_STRING, 1, NULL, &hvd_switch, 1, NULL, &POMP);

    else if (stringEqual(OPT.SWITCH_TH_PHASE_MOTOR, operation))
        return request_init(INSTANT, KEY.STATE, EMPTY_STRING, EMPTY_STRING, 1, NULL, &hvd_switch, 1, NULL, &TH_PHASE_MOTOR);

    /* PROCESS REQUESTS */

    else if (stringEqual(OPT.CONFIGURE_PROCESS, operation))
        return request_init(INSTANT, KEY.DIRECTION, KEY.COOLANT, EMPTY_STRING, 1, &process_validateConfigure, &process_configure, 1, NULL, NULL);

    else if (stringEqual(OPT.INIT_PROCESS, operation))
        return request_init(INSTANT, EMPTY_STRING, EMPTY_STRING, EMPTY_STRING, 0, NULL, &process_init, 0, NULL, NULL);

    else if (stringEqual(OPT.PAUSE_PROCESS, operation))
        return request_init(INSTANT, EMPTY_STRING, EMPTY_STRING, EMPTY_STRING, 0, &process_validatePause, &process_pause, 0, NULL, NULL);

    else if (stringEqual(OPT.RESUME_PROCESS, operation))
        return request_init(INSTANT, EMPTY_STRING, EMPTY_STRING, EMPTY_STRING, 0, &process_validateResume, &process_resume, 0, NULL, NULL);

    else if (stringEqual(OPT.STOP_PROCESS, operation))
        return request_init(INSTANT, EMPTY_STRING, EMPTY_STRING, EMPTY_STRING, 0, &process_validateStop, &process_stop, 0, NULL, NULL);

    /* GET STATES REQUEST */
    else if (stringEqual(OPT.GET_ALL_STATES, operation))
        return request_init(ANSWER, EMPTY_STRING, EMPTY_STRING, EMPTY_STRING, 0, NULL, &device_manager_getDevicesStatesMap, 0, NULL, NULL);

    // if the operation type was not resolved i creating empty request object
    Request request = {0};

    return request;
}