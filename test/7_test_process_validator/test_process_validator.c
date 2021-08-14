#ifdef UNIT_TEST

#include <unity.h> // includes unit testing library
#include <string.h>

#include "stm32f4xx_hal.h"

#include "command/partial/err.h"
#include "process/process.h"
#include "process/partial/process_validator.h"

#include "device/device_manager.h"
#include "device/low_voltage/stepper/partial/stepper_helper.h"

void setUp()
{
    err_init();
    device_manager_init();
}

void tearDown();

/************************** validateConfigure() ****************************/

void test_process_validateConfigure_should_give_error_if_steppers_running()
{
    PROCESS_STATE = NONE;
    PROCESS_PREVIOUS_STATE = NONE;

    stepper_setState(X_STEPPER, MOVING);
    stepper_setState(W_STEPPER, MOVING);

    TEST_ASSERT_EQUAL_UINT8(ERR.OPERATION_NOT_ALLOWED, process_validateConfigure((void *)"0\0"));
}

void test_process_validateConfigure_should_give_error_if_process_running()
{
    PROCESS_STATE = FORWARD;

    stepper_setState(X_STEPPER, LOW);
    stepper_setState(W_STEPPER, LOW);

    TEST_ASSERT_EQUAL_UINT8(ERR.OPERATION_NOT_ALLOWED, process_validateConfigure((void *)"0\0"));

    PROCESS_STATE = BACKWARD;
    TEST_ASSERT_EQUAL_UINT8(ERR.OPERATION_NOT_ALLOWED, process_validateConfigure((void *)"0\0"));

    PROCESS_STATE = HALTED;
    TEST_ASSERT_EQUAL_UINT8(ERR.OPERATION_NOT_ALLOWED, process_validateConfigure((void *)"0\0"));
}

void test_process_validateConfigure_should_give_error_no_error()
{
    PROCESS_STATE = NONE;

    stepper_setState(X_STEPPER, LOW);
    stepper_setState(W_STEPPER, LOW);

    TEST_ASSERT_EQUAL_UINT8(ERR.NO_ERROR, process_validateConfigure((void *)"0\0"));
}

/************************** validatePause() ****************************/

void test_process_validatePause_should_give_error_if_process_is_not_running()
{
    PROCESS_STATE = NONE;
    TEST_ASSERT_EQUAL_UINT8(ERR.OPERATION_NOT_ALLOWED, process_validatePause());

    PROCESS_STATE = HALTED;
    TEST_ASSERT_EQUAL_UINT8(ERR.OPERATION_NOT_ALLOWED, process_validatePause());
}

void test_process_validatePause_should_give_no_error()
{
    PROCESS_STATE = FORWARD;
    TEST_ASSERT_EQUAL_UINT8(ERR.NO_ERROR, process_validatePause());

    PROCESS_STATE = BACKWARD;
    TEST_ASSERT_EQUAL_UINT8(ERR.NO_ERROR, process_validatePause());
}

/************************** validateResume() ****************************/

void test_process_validateResume_should_give_error_if_process_is_not_paused()
{
    PROCESS_STATE = NONE;
    TEST_ASSERT_EQUAL_UINT8(ERR.OPERATION_NOT_ALLOWED, process_validateResume());

    PROCESS_STATE = FORWARD;
    TEST_ASSERT_EQUAL_UINT8(ERR.OPERATION_NOT_ALLOWED, process_validateResume());

    PROCESS_STATE = BACKWARD;
    TEST_ASSERT_EQUAL_UINT8(ERR.OPERATION_NOT_ALLOWED, process_validateResume());
}

void test_process_validateResume_should_give_no_error()
{
    PROCESS_STATE = HALTED;
    TEST_ASSERT_EQUAL_UINT8(ERR.NO_ERROR, process_validateResume());
}

/************************** validateStop() ****************************/

void test_process_validateStop_should_give_error_if_process_not_initialized()
{
    PROCESS_STATE = NONE;
    TEST_ASSERT_EQUAL_UINT8(ERR.OPERATION_NOT_ALLOWED, process_validateStop());
}

void test_process_validateStop_should_give_no_error()
{
    PROCESS_STATE = FORWARD;
    TEST_ASSERT_EQUAL_UINT8(ERR.NO_ERROR, process_validateStop());

    PROCESS_STATE = BACKWARD;
    TEST_ASSERT_EQUAL_UINT8(ERR.NO_ERROR, process_validateStop());

    PROCESS_STATE = HALTED;
    TEST_ASSERT_EQUAL_UINT8(ERR.NO_ERROR, process_validateStop());
}

int main()
{
    HAL_Init();      // initialize the HAL library
    HAL_Delay(2000); // service delay

    UNITY_BEGIN();

    RUN_TEST(test_process_validateConfigure_should_give_error_if_steppers_running);
    RUN_TEST(test_process_validateConfigure_should_give_error_if_process_running);
    RUN_TEST(test_process_validateConfigure_should_give_error_no_error);

    RUN_TEST(test_process_validatePause_should_give_error_if_process_is_not_running);
    RUN_TEST(test_process_validatePause_should_give_no_error);

    RUN_TEST(test_process_validateResume_should_give_error_if_process_is_not_paused);
    RUN_TEST(test_process_validateResume_should_give_no_error);

    RUN_TEST(test_process_validateStop_should_give_error_if_process_not_initialized);
    RUN_TEST(test_process_validateStop_should_give_no_error);

    UNITY_END();
}

#endif // UNIT_TEST