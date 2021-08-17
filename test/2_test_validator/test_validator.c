#ifdef UNIT_TEST

#include <unity.h> // includes unit testing library

#include "stm32f4xx_hal.h"

#include "data/validator.h"
#include "command/partial/err.h"

void setUp()
{
    err_init();
}

void tearDown(); // default release function

/************************** validate_boolean() ****************************/

void test_validate_boolean_should_give_error()
{
    TEST_ASSERT_EQUAL_UINT8(ERR.ERROR, validate_boolean((uint8_t *)"\0"));
    TEST_ASSERT_EQUAL_UINT8(ERR.ERROR, validate_boolean((uint8_t *)" "));
    TEST_ASSERT_EQUAL_UINT8(ERR.ERROR, validate_boolean((uint8_t *)"."));
    TEST_ASSERT_EQUAL_UINT8(ERR.ERROR, validate_boolean((uint8_t *)"a"));
    TEST_ASSERT_EQUAL_UINT8(ERR.ERROR, validate_boolean((uint8_t *)"-1"));
    TEST_ASSERT_EQUAL_UINT8(ERR.ERROR, validate_boolean((uint8_t *)"5"));
}

void test_validate_boolean_should_give_no_error()
{
    TEST_ASSERT_EQUAL_UINT8(ERR.NO_ERROR, validate_boolean((uint8_t *)"0"));
    TEST_ASSERT_EQUAL_UINT8(ERR.NO_ERROR, validate_boolean((uint8_t *)"1"));
}

/************************** validate_float() ****************************/

void test_validate_float_should_give_error()
{
    TEST_ASSERT_EQUAL_UINT8(ERR.ERROR, validate_float((uint8_t *)"\0"));
    TEST_ASSERT_EQUAL_UINT8(ERR.ERROR, validate_float((uint8_t *)" "));
    TEST_ASSERT_EQUAL_UINT8(ERR.ERROR, validate_float((uint8_t *)"."));
    TEST_ASSERT_EQUAL_UINT8(ERR.ERROR, validate_float((uint8_t *)"a"));
    TEST_ASSERT_EQUAL_UINT8(ERR.ERROR, validate_float((uint8_t *)"-1"));
    TEST_ASSERT_EQUAL_UINT8(ERR.ERROR, validate_float((uint8_t *)"0"));
    TEST_ASSERT_EQUAL_UINT8(ERR.ERROR, validate_float((uint8_t *)"0."));
    TEST_ASSERT_EQUAL_UINT8(ERR.ERROR, validate_float((uint8_t *)"1."));
    TEST_ASSERT_EQUAL_UINT8(ERR.ERROR, validate_float((uint8_t *)".1"));
    TEST_ASSERT_EQUAL_UINT8(ERR.ERROR, validate_float((uint8_t *)"0a"));
    TEST_ASSERT_EQUAL_UINT8(ERR.ERROR, validate_float((uint8_t *)"012"));
    TEST_ASSERT_EQUAL_UINT8(ERR.ERROR, validate_float((uint8_t *)"0.00"));
}

void test_validate_float_should_give_no_error()
{
    TEST_ASSERT_EQUAL_UINT8(ERR.NO_ERROR, validate_float((uint8_t *)"1"));
    TEST_ASSERT_EQUAL_UINT8(ERR.NO_ERROR, validate_float((uint8_t *)"9"));
    TEST_ASSERT_EQUAL_UINT8(ERR.NO_ERROR, validate_float((uint8_t *)"10"));
    TEST_ASSERT_EQUAL_UINT8(ERR.NO_ERROR, validate_float((uint8_t *)"99"));
    TEST_ASSERT_EQUAL_UINT8(ERR.NO_ERROR, validate_float((uint8_t *)"0.1"));
    TEST_ASSERT_EQUAL_UINT8(ERR.NO_ERROR, validate_float((uint8_t *)"0.01"));
    TEST_ASSERT_EQUAL_UINT8(ERR.NO_ERROR, validate_float((uint8_t *)"0.84"));
}

int main()
{
    HAL_Init();      // initialize the HAL library
    HAL_Delay(2000); // service delay

    UNITY_BEGIN();

    RUN_TEST(test_validate_boolean_should_give_error);
    RUN_TEST(test_validate_boolean_should_give_no_error);
    RUN_TEST(test_validate_float_should_give_error);
    RUN_TEST(test_validate_float_should_give_no_error);

    UNITY_END();
}

#endif // UNIT_TEST