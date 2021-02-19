#ifdef UNIT_TEST

#include <unity.h> // includes unit testing library
#include "stm32f4xx_hal.h"
#include "stepper/partial/stepper_validator.h"

void setUp();    // default setup function
void tearDown(); // default release function

/*** NEGATIVE ***/

void test_stepper_setSpeed_should_give_false_if_empty()
{
    TEST_ASSERT_FALSE(set_speed_validator(NULL, (uint8_t *)""));
}

void test_stepper_setSpeed_should_give_false_if_too_long()
{
    TEST_ASSERT_FALSE(set_speed_validator(NULL, (uint8_t *)"       "));
    TEST_ASSERT_FALSE(set_speed_validator(NULL, (uint8_t *)"......."));
    TEST_ASSERT_FALSE(set_speed_validator(NULL, (uint8_t *)"abcdefg"));
    TEST_ASSERT_FALSE(set_speed_validator(NULL, (uint8_t *)"1234567"));
    TEST_ASSERT_FALSE(set_speed_validator(NULL, (uint8_t *)"12345.67"));
    TEST_ASSERT_FALSE(set_speed_validator(NULL, (uint8_t *)"123.4567"));
}

void test_stepper_setSpeed_should_give_false_if_len_one_wrong_characters()
{
    TEST_ASSERT_FALSE(set_speed_validator(NULL, (uint8_t *)" "));
    TEST_ASSERT_FALSE(set_speed_validator(NULL, (uint8_t *)"."));
    TEST_ASSERT_FALSE(set_speed_validator(NULL, (uint8_t *)"a"));
    TEST_ASSERT_FALSE(set_speed_validator(NULL, (uint8_t *)"0"));
}

void test_stepper_setSpeed_should_give_false_if_len_two_wrong_characters()
{
    TEST_ASSERT_FALSE(set_speed_validator(NULL, (uint8_t *)"  "));
    TEST_ASSERT_FALSE(set_speed_validator(NULL, (uint8_t *)".."));
    TEST_ASSERT_FALSE(set_speed_validator(NULL, (uint8_t *)"aa"));
    TEST_ASSERT_FALSE(set_speed_validator(NULL, (uint8_t *)"a1"));
    TEST_ASSERT_FALSE(set_speed_validator(NULL, (uint8_t *)"01"));
    TEST_ASSERT_FALSE(set_speed_validator(NULL, (uint8_t *)"1."));
    TEST_ASSERT_FALSE(set_speed_validator(NULL, (uint8_t *)".1"));
}

void test_stepper_setSpeed_should_give_false_if_long_len_starts_with_0_wrong_characters()
{
    TEST_ASSERT_FALSE(set_speed_validator(NULL, (uint8_t *)"0ab"));
    TEST_ASSERT_FALSE(set_speed_validator(NULL, (uint8_t *)"012"));
    TEST_ASSERT_FALSE(set_speed_validator(NULL, (uint8_t *)"0.a"));
    TEST_ASSERT_FALSE(set_speed_validator(NULL, (uint8_t *)"0.0"));
    TEST_ASSERT_FALSE(set_speed_validator(NULL, (uint8_t *)"0.00"));
    TEST_ASSERT_FALSE(set_speed_validator(NULL, (uint8_t *)"0.000"));
}

void test_stepper_setSpeed_should_give_false_if_long_len_starts_with_not_0_wrong_characters()
{
    TEST_ASSERT_FALSE(set_speed_validator(NULL, (uint8_t *)"   "));
    TEST_ASSERT_FALSE(set_speed_validator(NULL, (uint8_t *)"..."));
    TEST_ASSERT_FALSE(set_speed_validator(NULL, (uint8_t *)"abc"));
    TEST_ASSERT_FALSE(set_speed_validator(NULL, (uint8_t *)"a12"));
    TEST_ASSERT_FALSE(set_speed_validator(NULL, (uint8_t *)"12a"));
    TEST_ASSERT_FALSE(set_speed_validator(NULL, (uint8_t *)".123"));
    TEST_ASSERT_FALSE(set_speed_validator(NULL, (uint8_t *)"a.2"));
    TEST_ASSERT_FALSE(set_speed_validator(NULL, (uint8_t *)"5.a"));
    TEST_ASSERT_FALSE(set_speed_validator(NULL, (uint8_t *)"53."));
    TEST_ASSERT_FALSE(set_speed_validator(NULL, (uint8_t *)"12.123"));
    TEST_ASSERT_FALSE(set_speed_validator(NULL, (uint8_t *)"1.1234"));
}

/*** POSITIVE ***/

void test_stepper_setSpeed_should_give_true_if_len_one()
{
    TEST_ASSERT_TRUE(set_speed_validator(NULL, (uint8_t *)"1"));
    TEST_ASSERT_TRUE(set_speed_validator(NULL, (uint8_t *)"9"));
}

void test_stepper_setSpeed_should_give_true_if_len_two()
{
    TEST_ASSERT_TRUE(set_speed_validator(NULL, (uint8_t *)"10"));
    TEST_ASSERT_TRUE(set_speed_validator(NULL, (uint8_t *)"99"));
}

void test_stepper_setSpeed_should_give_true_if_long_len_starts_with_0()
{
    TEST_ASSERT_TRUE(set_speed_validator(NULL, (uint8_t *)"0.1"));
    TEST_ASSERT_TRUE(set_speed_validator(NULL, (uint8_t *)"0.01"));
    TEST_ASSERT_TRUE(set_speed_validator(NULL, (uint8_t *)"0.04"));
    TEST_ASSERT_TRUE(set_speed_validator(NULL, (uint8_t *)"0.76"));
    TEST_ASSERT_TRUE(set_speed_validator(NULL, (uint8_t *)"0.9"));
    TEST_ASSERT_TRUE(set_speed_validator(NULL, (uint8_t *)"0.99"));
}

void test_stepper_setSpeed_should_give_true_if_long_len_starts_with_not_0()
{
    TEST_ASSERT_TRUE(set_speed_validator(NULL, (uint8_t *)"123"));
    TEST_ASSERT_TRUE(set_speed_validator(NULL, (uint8_t *)"1.23"));
    TEST_ASSERT_TRUE(set_speed_validator(NULL, (uint8_t *)"12.3"));
    TEST_ASSERT_TRUE(set_speed_validator(NULL, (uint8_t *)"1.34"));
    TEST_ASSERT_TRUE(set_speed_validator(NULL, (uint8_t *)"3.66"));
    TEST_ASSERT_TRUE(set_speed_validator(NULL, (uint8_t *)"99.99"));
}

int main()
{
    HAL_Init();      // initialize the HAL library
    HAL_Delay(2000); // service delay

    UNITY_BEGIN();

    // NEGATIVE
    RUN_TEST(test_stepper_setSpeed_should_give_false_if_empty);
    RUN_TEST(test_stepper_setSpeed_should_give_false_if_too_long);
    RUN_TEST(test_stepper_setSpeed_should_give_false_if_len_one_wrong_characters);
    RUN_TEST(test_stepper_setSpeed_should_give_false_if_len_two_wrong_characters);
    RUN_TEST(test_stepper_setSpeed_should_give_false_if_long_len_starts_with_0_wrong_characters);
    RUN_TEST(test_stepper_setSpeed_should_give_false_if_long_len_starts_with_not_0_wrong_characters);

    // POSITIVE
    RUN_TEST(test_stepper_setSpeed_should_give_true_if_len_one);
    RUN_TEST(test_stepper_setSpeed_should_give_true_if_len_two);
    RUN_TEST(test_stepper_setSpeed_should_give_true_if_long_len_starts_with_0);
    RUN_TEST(test_stepper_setSpeed_should_give_true_if_long_len_starts_with_0);
    RUN_TEST(test_stepper_setSpeed_should_give_true_if_long_len_starts_with_not_0);

    UNITY_END();
}

#endif // UNIT_TEST