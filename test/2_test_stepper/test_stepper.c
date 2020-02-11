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

/**************** stepper_switch ********************/

void test_stepper_switch_should_give_false_if_empty()
{
    TEST_ASSERT_FALSE(stepper_switch(NULL, (uint8_t*)""));
}

void test_stepper_switch_should_give_false_if_a()
{
    TEST_ASSERT_FALSE(stepper_switch(NULL, (uint8_t*)"a"));
}

void test_stepper_switch_should_give_false_if_one_zero()
{
    TEST_ASSERT_FALSE(stepper_switch(NULL, (uint8_t*)"10"));
}

void test_stepper_switch_switch_should_give_true_if_0()
{
    TEST_ASSERT_TRUE(stepper_switch(NULL, (uint8_t*)"0"));
}

void test_stepper_switch_switch_should_give_true_if_1()
{
    TEST_ASSERT_TRUE(stepper_switch(NULL, (uint8_t*)"1"));
}

/**************** stepper_move ********************/

void test_stepper_move_should_give_false_if_empty()
{
    TEST_ASSERT_FALSE(stepper_move(NULL, (uint8_t*)""));
}

void test_stepper_move_should_give_false_if_starts_with_0_and_have_others()
{
    TEST_ASSERT_FALSE(stepper_move(NULL, (uint8_t*)"032"));
}

void test_stepper_move_should_give_false_if_letters_only()
{
    TEST_ASSERT_FALSE(stepper_move(NULL, (uint8_t*)"ab"));
}

void test_stepper_move_should_give_false_if_mix()
{
    TEST_ASSERT_FALSE(stepper_move(NULL, (uint8_t*)"1a3"));
}

void test_stepper_move_should_give_false_if_zero()
{
    TEST_ASSERT_FALSE(stepper_move(NULL, (uint8_t*)"0"));
}

void test_stepper_move_should_give_true_if_negative()
{
    TEST_ASSERT_TRUE(stepper_move(NULL, (uint8_t*)"-2"));
}

void test_stepper_move_should_give_true_if_positive()
{
    TEST_ASSERT_TRUE(stepper_move(NULL, (uint8_t*)"2"));
}

/**************** stepper_setDirection ********************/

void test_stepper_setDirection_should_give_false_if_empty()
{
    TEST_ASSERT_FALSE(stepper_setDirection(NULL, (uint8_t*)""));
}

void test_stepper_setDirection_should_give_false_if_a()
{
    TEST_ASSERT_FALSE(stepper_setDirection(NULL, (uint8_t*)"a"));
}

void test_stepper_setDirection_should_give_false_if_mix()
{
    TEST_ASSERT_FALSE(stepper_setDirection(NULL, (uint8_t*)"1a"));
}

void test_stepper_setDirection_should_give_false_if_not_zero_and_not_one()
{
    TEST_ASSERT_FALSE(stepper_setDirection(NULL, (uint8_t*)"4"));
}

void test_stepper_setDirection_should_give_true_if_zero()
{
    TEST_ASSERT_TRUE(stepper_setDirection(NULL, (uint8_t*)"0"));
}

/**************** stepper_pause ********************/

void test_stepper_pause_should_give_false_if_empty()
{
    TEST_ASSERT_FALSE(stepper_pause(NULL, (uint8_t*)""));
}

void test_stepper_pause_should_give_false_if_a()
{
    TEST_ASSERT_FALSE(stepper_pause(NULL, (uint8_t*)"a"));
}

void test_stepper_pause_should_give_false_if_mix()
{
    TEST_ASSERT_FALSE(stepper_pause(NULL, (uint8_t*)"1a"));
}

void test_stepper_pause_should_give_false_if_not_zero_and_not_one()
{
    TEST_ASSERT_FALSE(stepper_pause(NULL, (uint8_t*)"4"));
}

void test_stepper_pause_should_give_true_if_zero()
{
    TEST_ASSERT_TRUE(stepper_pause(NULL, (uint8_t*)"0"));
}

/**************** stepper_resume ********************/

void test_stepper_resume_should_give_false_if_empty()
{
    TEST_ASSERT_FALSE(stepper_resume(NULL, (uint8_t*)""));
}

void test_stepper_resume_should_give_false_if_a()
{
    TEST_ASSERT_FALSE(stepper_resume(NULL, (uint8_t*)"a"));
}

void test_stepper_resume_should_give_false_if_mix()
{
    TEST_ASSERT_FALSE(stepper_resume(NULL, (uint8_t*)"1a"));
}

void test_stepper_resume_should_give_false_if_not_zero_and_not_one()
{
    TEST_ASSERT_FALSE(stepper_resume(NULL, (uint8_t*)"4"));
}

void test_stepper_resume_should_give_true_if_zero()
{
    TEST_ASSERT_TRUE(stepper_resume(NULL, (uint8_t*)"0"));
}

/**************** stepper_stop ********************/

void test_stepper_stop_should_give_false_if_empty()
{
    TEST_ASSERT_FALSE(stepper_stop(NULL, (uint8_t*)""));
}

void test_stepper_stop_should_give_false_if_a()
{
    TEST_ASSERT_FALSE(stepper_stop(NULL, (uint8_t*)"a"));
}

void test_stepper_stop_should_give_false_if_mix()
{
    TEST_ASSERT_FALSE(stepper_stop(NULL, (uint8_t*)"1a"));
}

void test_stepper_stop_should_give_false_if_not_zero_and_not_one()
{
    TEST_ASSERT_FALSE(stepper_stop(NULL, (uint8_t*)"4"));
}

void test_stepper_stop_should_give_true_if_zero()
{
    TEST_ASSERT_TRUE(stepper_stop(NULL, (uint8_t*)"0"));
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

    /**************** stepper_switch ********************/

    RUN_TEST(test_stepper_switch_should_give_false_if_empty);
    RUN_TEST(test_stepper_switch_should_give_false_if_a);
    RUN_TEST(test_stepper_switch_should_give_false_if_one_zero);
    RUN_TEST(test_stepper_switch_switch_should_give_true_if_0);
    RUN_TEST(test_stepper_switch_switch_should_give_true_if_1);

    /**************** stepper_move ********************/

    RUN_TEST(test_stepper_move_should_give_false_if_empty);
    RUN_TEST(test_stepper_move_should_give_false_if_starts_with_0_and_have_others);
    RUN_TEST(test_stepper_move_should_give_false_if_letters_only);
    RUN_TEST(test_stepper_move_should_give_false_if_mix);
    RUN_TEST(test_stepper_move_should_give_false_if_zero);
    RUN_TEST(test_stepper_move_should_give_true_if_negative);
    RUN_TEST(test_stepper_move_should_give_true_if_positive);

    /**************** stepper_setDirection ********************/

    RUN_TEST(test_stepper_setDirection_should_give_false_if_empty);
    RUN_TEST(test_stepper_setDirection_should_give_false_if_a);
    RUN_TEST(test_stepper_setDirection_should_give_false_if_mix);
    RUN_TEST(test_stepper_setDirection_should_give_false_if_not_zero_and_not_one);
    RUN_TEST(test_stepper_setDirection_should_give_true_if_zero);

    /**************** stepper_pause ********************/

    RUN_TEST(test_stepper_pause_should_give_false_if_empty);
    RUN_TEST(test_stepper_pause_should_give_false_if_a);
    RUN_TEST(test_stepper_pause_should_give_false_if_mix);
    RUN_TEST(test_stepper_pause_should_give_false_if_not_zero_and_not_one);
    RUN_TEST(test_stepper_pause_should_give_true_if_zero);

    /**************** stepper_resume ********************/

    RUN_TEST(test_stepper_resume_should_give_false_if_empty);
    RUN_TEST(test_stepper_resume_should_give_false_if_a);
    RUN_TEST(test_stepper_resume_should_give_false_if_mix);
    RUN_TEST(test_stepper_resume_should_give_false_if_not_zero_and_not_one);
    RUN_TEST(test_stepper_resume_should_give_true_if_zero);

    /**************** stepper_stop ********************/

    RUN_TEST(test_stepper_stop_should_give_false_if_empty);
    RUN_TEST(test_stepper_stop_should_give_false_if_a);
    RUN_TEST(test_stepper_stop_should_give_false_if_mix);
    RUN_TEST(test_stepper_stop_should_give_false_if_not_zero_and_not_one);
    RUN_TEST(test_stepper_stop_should_give_true_if_zero);

    UNITY_END();
}

#endif // UNIT_TEST