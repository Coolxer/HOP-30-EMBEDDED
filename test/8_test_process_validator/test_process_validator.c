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

void test_process_validateConfigure_should_give_error()
{
    PROCESS_STATE = NONE;
    PROCESS_PREVIOUS_STATE = NONE;

    stepper_setState(X_STEPPER, MOVING);
    stepper_setState(W_STEPPER, MOVING);

    TEST_ASSERT_EQUAL_UINT8(ERR.STEPPER_ALREADY_RUNNING, process_validateConfigure((void *)"0\0", (void *)"0\0"));

    PROCESS_STATE = FORWARD;

    TEST_ASSERT_EQUAL_UINT8(ERR.PROCESS_ALREADY_RUNNING, process_validateConfigure((void *)"0\0", (void *)"0\0"));

    PROCESS_STATE = BACKWARD;
    TEST_ASSERT_EQUAL_UINT8(ERR.PROCESS_ALREADY_RUNNING, process_validateConfigure((void *)"0\0", (void *)"0\0"));

    PROCESS_STATE = HALTED;
    TEST_ASSERT_EQUAL_UINT8(ERR.PROCESS_ALREADY_RUNNING, process_validateConfigure((void *)"0\0", (void *)"0\0"));
}

void test_process_validateConfigure_should_give_no_error()
{
    PROCESS_STATE = NONE;

    stepper_setState(X_STEPPER, LOW);
    stepper_setState(W_STEPPER, LOW);

    TEST_ASSERT_EQUAL_UINT8(CORRECT, process_validateConfigure((void *)"0\0", (void *)"0\0"));
}

/************************** validateInit() ****************************/
void test_process_validateInit_should_give_error()
{
    PROCESS_STATE = NONE;
    TEST_ASSERT_EQUAL_UINT8(ERR.PROCESS_NOT_CONFIGURED, process_validateInit());
}

void test_process_validateInit_should_give_no_error()
{
    PROCESS_STATE = NONE;
    PROCESS_CONFIGURED = 1;

    TEST_ASSERT_EQUAL_UINT8(CORRECT, process_validateInit());
}

/************************** validatePause() ****************************/

void test_process_validatePause_should_give_error()
{
    PROCESS_STATE = NONE;
    TEST_ASSERT_EQUAL_UINT8(ERR.PROCESS_NOT_RUNNING, process_validatePause());

    PROCESS_STATE = HALTED;
    TEST_ASSERT_EQUAL_UINT8(ERR.PROCESS_NOT_RUNNING, process_validatePause());
}

void test_process_validatePause_should_give_no_error()
{
    PROCESS_STATE = FORWARD;
    TEST_ASSERT_EQUAL_UINT8(CORRECT, process_validatePause());

    PROCESS_STATE = BACKWARD;
    TEST_ASSERT_EQUAL_UINT8(CORRECT, process_validatePause());
}

/************************** validateResume() ****************************/

void test_process_validateResume_should_give_error()
{
    PROCESS_STATE = NONE;
    TEST_ASSERT_EQUAL_UINT8(ERR.PROCESS_NOT_HALTED, process_validateResume());

    PROCESS_STATE = FORWARD;
    TEST_ASSERT_EQUAL_UINT8(ERR.PROCESS_NOT_HALTED, process_validateResume());

    PROCESS_STATE = BACKWARD;
    TEST_ASSERT_EQUAL_UINT8(ERR.PROCESS_NOT_HALTED, process_validateResume());
}

void test_process_validateResume_should_give_no_error()
{
    PROCESS_STATE = HALTED;
    TEST_ASSERT_EQUAL_UINT8(CORRECT, process_validateResume());
}

/************************** validateStop() ****************************/

void test_process_validateStop_should_give_error()
{
    PROCESS_STATE = NONE;
    TEST_ASSERT_EQUAL_UINT8(ERR.PROCESS_NOT_RUNNING, process_validateStop());
}

void test_process_validateStop_should_give_no_error()
{
    PROCESS_STATE = FORWARD;
    TEST_ASSERT_EQUAL_UINT8(CORRECT, process_validateStop());

    PROCESS_STATE = BACKWARD;
    TEST_ASSERT_EQUAL_UINT8(CORRECT, process_validateStop());

    PROCESS_STATE = HALTED;
    TEST_ASSERT_EQUAL_UINT8(CORRECT, process_validateStop());
}

int main()
{
    HAL_Init();      // initialize the HAL library
    HAL_Delay(2000); // service delay

    UNITY_BEGIN();

    RUN_TEST(test_process_validateConfigure_should_give_error);
    RUN_TEST(test_process_validateConfigure_should_give_no_error);

    RUN_TEST(test_process_validatePause_should_give_error);
    RUN_TEST(test_process_validatePause_should_give_no_error);

    RUN_TEST(test_process_validateResume_should_give_error);
    RUN_TEST(test_process_validateResume_should_give_no_error);

    RUN_TEST(test_process_validateStop_should_give_error);
    RUN_TEST(test_process_validateStop_should_give_no_error);

    UNITY_END();
}

#endif // UNIT_TEST