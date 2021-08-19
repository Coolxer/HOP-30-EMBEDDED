#include "command/partial/err.h"

err ERR = {0};

void err_init()
{
    // STRUCTURE ERRORS

    ERR.UNDEFINED = 1;

    ERR.COMMAND_TOO_SHORT = 2;
    ERR.COMMAND_TOO_LONG = 3;
    ERR.COMMAND_INCORRECT_BEGINING = 4;
    ERR.COMMAND_INCORRECT_CONTENT = 5;
    ERR.COMMAND_INCORRECT_END = 6;

    ERR.NO_PARAMS = 7;
    ERR.ONE_PARAM_ONLY = 8;
    ERR.TO_MANY_PARAMS = 9;

    ERR.NO_INDEX_KEY = 10;
    ERR.INCORRECT_INDEX_VALUE = 11;

    ERR.NO_OPERATION_KEY = 12;
    ERR.INCORRECT_OPERATION_VALUE = 13;

    ERR.NO_STEPPER_KEY = 14;
    ERR.INCORRECT_STEPPER_VALUE = 15;

    ERR.NO_ENDSTOP_KEY = 16;
    ERR.INCORRECT_ENDSTOP_VALUE = 17;

    ERR.NO_SPEED_KEY = 18;
    ERR.INCORRECT_SPEED_VALUE = 19;

    ERR.NO_ACCELERATION_KEY = 20;
    ERR.INCORRECT_ACCELERATION_VALUE = 21;

    ERR.NO_STATE_KEY = 22;
    ERR.INCORRECT_STATE_VALUE = 23;

    ERR.NO_WAY_KEY = 24;
    ERR.INCORRECT_WAY_VALUE = 25;

    ERR.NO_DIRECTION_KEY = 26;
    ERR.INCORRECT_DIRECTION_VALUE = 27;

    ERR.NO_COOLANT_KEY = 28;
    ERR.INCORRECT_COOLANT_VALUE = 29;

    // ENVIRONMENT STATE ERRORS

    ERR.LIMIT_SWITCH_REACHED = 30;

    ERR.STEPPER_SPEED_NOT_SET = 31;
    ERR.STEPPER_NOT_RUNNING = 32;
    ERR.STEPPER_NOT_PAUSED = 33;
    ERR.STEPPER_NOT_RUNNING_OR_PAUSED = 34;

    ERR.STEPPER_ALREADY_RUNNING = 35;
    ERR.STEPPER_ALREADY_PAUSED = 36;

    ERR.PROCESS_NOT_CONFIGURED = 37;
    ERR.PROCESS_NOT_HALTED = 38;
    ERR.PROCESS_NOT_RUNNING = 39;
    ERR.PROCESS_ALREADY_RUNNING = 40;

    ERR.OPERATION_NOT_ALLOWED = 41;
}
