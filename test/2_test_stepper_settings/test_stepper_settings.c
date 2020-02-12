#ifdef UNIT_TEST

#include <unity.h> // includes unit testing library
#include "stm32f4xx_hal.h"
#include "stepper.h"

void setUp();// default setup function
void tearDown(); // default release function

/**************** stepper_setMicrostepping ********************/

void test_stepper_setMicrostepping_should_give_false_if_empty()
{
    TEST_ASSERT_FALSE(stepper_setMicrostepping(NULL, (uint8_t*)""));
}

void test_stepper_setMicrostepping_should_give_false_if_a()
{
    TEST_ASSERT_FALSE(stepper_setMicrostepping(NULL, (uint8_t*)"a"));
}

void test_stepper_setMicrostepping_should_give_false_if_1()
{
    TEST_ASSERT_FALSE(stepper_setMicrostepping(NULL, (uint8_t*)"1"));
}

void test_stepper_setMicrostepping_should_give_false_if_too_many_numbers()
{
    TEST_ASSERT_FALSE(stepper_setMicrostepping(NULL, (uint8_t*)"0101010"));
}

void test_stepper_setMicrostepping_should_give_false_if_random_numbers()
{
    TEST_ASSERT_FALSE(stepper_setMicrostepping(NULL, (uint8_t*)"408"));
}

void test_stepper_setMicrostepping_should_give_false_if_mix()
{
    TEST_ASSERT_FALSE(stepper_setMicrostepping(NULL, (uint8_t*)"1a0"));
}

void test_stepper_setMicrostepping_should_give_true()
{
    TEST_ASSERT_TRUE(stepper_setMicrostepping(NULL, (uint8_t*)"101"));
}

/**************** stepper_setSpeed ********************/

void test_stepper_setSpeed_should_give_false_if_empty()
{
    TEST_ASSERT_FALSE(stepper_setSpeed(NULL, (uint8_t*)""));
}

void test_stepper_setSpeed_should_give_false_if_more_than_3_characters()
{
    TEST_ASSERT_FALSE(stepper_setSpeed(NULL, (uint8_t*)"1000"));
}

void test_stepper_setSpeed_should_give_false_if_starts_with_0()
{
    TEST_ASSERT_FALSE(stepper_setSpeed(NULL, (uint8_t*)"045"));
}

void test_stepper_setSpeed_should_give_false_if_mix()
{
    TEST_ASSERT_FALSE(stepper_setSpeed(NULL, (uint8_t*)"2a"));
}

void test_stepper_setSpeed_should_give_false_if_less_than_one()
{
    TEST_ASSERT_FALSE(stepper_setSpeed(NULL, (uint8_t*)"0"));
}

void test_stepper_setSpeed_should_give_false_if_more_than_one_hundred()
{
    TEST_ASSERT_FALSE(stepper_setSpeed(NULL, (uint8_t*)"101"));
}

void test_stepper_setSpeed_should_give_true()
{
    TEST_ASSERT_TRUE(stepper_setSpeed(NULL, (uint8_t*)"50"));
}

int main()
{
    HAL_Init();         // initialize the HAL library
    HAL_Delay(2000);    // service delay

    UNITY_BEGIN();

    /**************** stepper_setMicrostepping ********************/

    RUN_TEST(test_stepper_setMicrostepping_should_give_false_if_empty);
    RUN_TEST(test_stepper_setMicrostepping_should_give_false_if_a);
    RUN_TEST(test_stepper_setMicrostepping_should_give_false_if_1);
    RUN_TEST(test_stepper_setMicrostepping_should_give_false_if_too_many_numbers);
    RUN_TEST(test_stepper_setMicrostepping_should_give_false_if_random_numbers);
    RUN_TEST(test_stepper_setMicrostepping_should_give_false_if_mix);
    RUN_TEST(test_stepper_setMicrostepping_should_give_true);

    /**************** stepper_setSpeed ********************/

    RUN_TEST(test_stepper_setSpeed_should_give_false_if_empty);
    RUN_TEST(test_stepper_setSpeed_should_give_false_if_more_than_3_characters);
    RUN_TEST(test_stepper_setSpeed_should_give_false_if_starts_with_0);
    RUN_TEST(test_stepper_setSpeed_should_give_false_if_mix);
    RUN_TEST(test_stepper_setSpeed_should_give_false_if_less_than_one);
    RUN_TEST(test_stepper_setSpeed_should_give_false_if_more_than_one_hundred);
    RUN_TEST(test_stepper_setSpeed_should_give_true);

    UNITY_END();
}

#endif // UNIT_TEST