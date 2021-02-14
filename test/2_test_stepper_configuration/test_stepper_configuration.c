#ifdef UNIT_TEST

#include <unity.h> // includes unit testing library
#include "stm32f4xx_hal.h"
#include "stepper/partial/stepper_validator.h"

void setUp();    // default setup function
void tearDown(); // default release function

void test_stepper_setSpeed_should_give_false_if_empty()
{
    TEST_ASSERT_FALSE(set_speed_validator(NULL, (uint8_t *)""));
}

void test_stepper_setSpeed_should_give_false_if_more_than_3_characters()
{
    TEST_ASSERT_FALSE(set_speed_validator(NULL, (uint8_t *)"1000"));
}

void test_stepper_setSpeed_should_give_false_if_starts_with_0()
{
    TEST_ASSERT_FALSE(set_speed_validator(NULL, (uint8_t *)"045"));
}

void test_stepper_setSpeed_should_give_false_if_mix()
{
    TEST_ASSERT_FALSE(set_speed_validator(NULL, (uint8_t *)"2a"));
}

void test_stepper_setSpeed_should_give_false_if_less_than_one()
{
    TEST_ASSERT_FALSE(set_speed_validator(NULL, (uint8_t *)"0"));
}

void test_stepper_setSpeed_should_give_true()
{
    TEST_ASSERT_TRUE(set_speed_validator(NULL, (uint8_t *)"50"));
}

int main()
{
    HAL_Init();      // initialize the HAL library
    HAL_Delay(2000); // service delay

    UNITY_BEGIN();

    RUN_TEST(test_stepper_setSpeed_should_give_false_if_empty);
    RUN_TEST(test_stepper_setSpeed_should_give_false_if_more_than_3_characters);
    RUN_TEST(test_stepper_setSpeed_should_give_false_if_starts_with_0);
    RUN_TEST(test_stepper_setSpeed_should_give_false_if_mix);
    RUN_TEST(test_stepper_setSpeed_should_give_false_if_less_than_one);
    RUN_TEST(test_stepper_setSpeed_should_give_true);

    UNITY_END();
}

#endif // UNIT_TEST