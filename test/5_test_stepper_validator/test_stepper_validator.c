#ifdef UNIT_TEST

#include <unity.h> // includes unit testing library
#include <string.h>

#include "stm32f4xx_hal.h"

#include "command/partial/err.h"

#include "device/device_manager.h"
#include "device/low_voltage/stepper/partial/stepper_helper.h"
#include "device/low_voltage/stepper/partial/stepper_validator.h"

void setUp()
{
    err_init();
    device_manager_init();
}

void tearDown();

/************************** validateConfigure() ****************************/

void test_stepper_validateConfigure_should_give_error_if_stepper_running_or_paused()
{
    stepper_setState(X_STEPPER, MOVING);
    TEST_ASSERT_EQUAL_UINT8(ERR.OPERATION_NOT_ALLOWED, stepper_validateConfigure(X_STEPPER, (void *)"50\0", (void *)"10\0"));

    stepper_setState(X_STEPPER, PAUSED);
    TEST_ASSERT_EQUAL_UINT8(ERR.OPERATION_NOT_ALLOWED, stepper_validateConfigure(X_STEPPER, (void *)"50\0", (void *)"10\0"));
}

void test_stepper_validateConfigure_should_give_no_error()
{
    stepper_setState(X_STEPPER, LOW);
    TEST_ASSERT_EQUAL_UINT8(ERR.NO_ERROR, stepper_validateConfigure(X_STEPPER, (void *)"50\0", (void *)"10\0"));

    stepper_setState(X_STEPPER, HIGH);
    TEST_ASSERT_EQUAL_UINT8(ERR.NO_ERROR, stepper_validateConfigure(X_STEPPER, (void *)"50\0", (void *)"10\0"));
}

/************************** validateSwitch() ****************************/

void test_stepper_validateSwitch_should_give_error_if_stepper_running()
{
    stepper_setState(X_STEPPER, MOVING);
    TEST_ASSERT_EQUAL_UINT8(ERR.OPERATION_NOT_ALLOWED, stepper_validateSwitch(X_STEPPER, (void *)"0\0"));
}

void test_stepper_validateSwitch_should_give_no_error()
{
    stepper_setState(X_STEPPER, LOW);
    TEST_ASSERT_EQUAL_UINT8(ERR.NO_ERROR, stepper_validateSwitch(X_STEPPER, (void *)"0\0"));

    stepper_setState(X_STEPPER, HIGH);
    TEST_ASSERT_EQUAL_UINT8(ERR.NO_ERROR, stepper_validateSwitch(X_STEPPER, (void *)"0\0"));

    stepper_setState(X_STEPPER, PAUSED);
    TEST_ASSERT_EQUAL_UINT8(ERR.NO_ERROR, stepper_validateSwitch(X_STEPPER, (void *)"0\0"));
}

/************************** validateMove() ****************************/

void test_stepper_validateMove_should_give_error_if_stepper_running_or_paused()
{
    stepper_setState(X_STEPPER, MOVING);
    TEST_ASSERT_EQUAL_UINT8(ERR.OPERATION_NOT_ALLOWED, stepper_validateMove(X_STEPPER, (void *)"50\0", (void *)"0\0"));

    stepper_setState(X_STEPPER, PAUSED);
    TEST_ASSERT_EQUAL_UINT8(ERR.OPERATION_NOT_ALLOWED, stepper_validateMove(X_STEPPER, (void *)"50\0", (void *)"0\0"));
}

void test_stepper_validateMove_should_give_no_error()
{
    stepper_setState(X_STEPPER, LOW);
    TEST_ASSERT_EQUAL_UINT8(ERR.NO_ERROR, stepper_validateMove(X_STEPPER, (void *)"50\0", (void *)"0\0"));

    stepper_setState(X_STEPPER, HIGH);
    TEST_ASSERT_EQUAL_UINT8(ERR.NO_ERROR, stepper_validateMove(X_STEPPER, (void *)"50\0", (void *)"0\0"));
}

/************************** validatePause() ****************************/

void test_stepper_validatePause_should_give_error_if_stepper_not_running()
{
    stepper_setState(X_STEPPER, LOW);
    TEST_ASSERT_EQUAL_UINT8(ERR.OPERATION_NOT_ALLOWED, stepper_validatePause(X_STEPPER));

    stepper_setState(X_STEPPER, HIGH);
    TEST_ASSERT_EQUAL_UINT8(ERR.OPERATION_NOT_ALLOWED, stepper_validatePause(X_STEPPER));

    stepper_setState(X_STEPPER, PAUSED);
    TEST_ASSERT_EQUAL_UINT8(ERR.OPERATION_NOT_ALLOWED, stepper_validatePause(X_STEPPER));
}

void test_stepper_validatePause_should_give_no_error()
{
    stepper_setState(X_STEPPER, MOVING);
    TEST_ASSERT_EQUAL_UINT8(ERR.NO_ERROR, stepper_validatePause(X_STEPPER));
}

/************************** validateResume() ****************************/

void test_stepper_validateResume_should_give_error_if_stepper_not_pause()
{
    stepper_setState(X_STEPPER, LOW);
    TEST_ASSERT_EQUAL_UINT8(ERR.OPERATION_NOT_ALLOWED, stepper_validateResume(X_STEPPER));

    stepper_setState(X_STEPPER, HIGH);
    TEST_ASSERT_EQUAL_UINT8(ERR.OPERATION_NOT_ALLOWED, stepper_validateResume(X_STEPPER));

    stepper_setState(X_STEPPER, MOVING);
    TEST_ASSERT_EQUAL_UINT8(ERR.OPERATION_NOT_ALLOWED, stepper_validateResume(X_STEPPER));
}

void test_stepper_validateResume_should_give_no_error()
{
    stepper_setState(X_STEPPER, PAUSED);
    TEST_ASSERT_EQUAL_UINT8(ERR.NO_ERROR, stepper_validateResume(X_STEPPER));
}

/************************** validateStop() ****************************/

void test_stepper_validateStop_should_give_error_if_stepper_not_running_or_paused()
{
    stepper_setState(X_STEPPER, LOW);
    TEST_ASSERT_EQUAL_UINT8(ERR.OPERATION_NOT_ALLOWED, stepper_validateStop(X_STEPPER));

    stepper_setState(X_STEPPER, HIGH);
    TEST_ASSERT_EQUAL_UINT8(ERR.OPERATION_NOT_ALLOWED, stepper_validateStop(X_STEPPER));
}

void test_stepper_validateStop_should_give_no_error()
{
    stepper_setState(X_STEPPER, MOVING);
    TEST_ASSERT_EQUAL_UINT8(ERR.NO_ERROR, stepper_validateStop(X_STEPPER));

    stepper_setState(X_STEPPER, PAUSED);
    TEST_ASSERT_EQUAL_UINT8(ERR.NO_ERROR, stepper_validateStop(X_STEPPER));
}

int main()
{
    HAL_Init();      // initialize the HAL library
    HAL_Delay(2000); // service delay

    UNITY_BEGIN();

    RUN_TEST(test_stepper_validateConfigure_should_give_error_if_stepper_running_or_paused);
    RUN_TEST(test_stepper_validateConfigure_should_give_no_error);

    RUN_TEST(test_stepper_validateSwitch_should_give_error_if_stepper_running);
    RUN_TEST(test_stepper_validateSwitch_should_give_no_error);

    RUN_TEST(test_stepper_validateMove_should_give_error_if_stepper_running_or_paused);
    RUN_TEST(test_stepper_validateMove_should_give_no_error);

    RUN_TEST(test_stepper_validatePause_should_give_error_if_stepper_not_running);
    RUN_TEST(test_stepper_validatePause_should_give_no_error);

    RUN_TEST(test_stepper_validateResume_should_give_error_if_stepper_not_pause);
    RUN_TEST(test_stepper_validateResume_should_give_no_error);

    RUN_TEST(test_stepper_validateStop_should_give_error_if_stepper_not_running_or_paused);
    RUN_TEST(test_stepper_validateStop_should_give_no_error);

    UNITY_END();
}

#endif // UNIT_TEST