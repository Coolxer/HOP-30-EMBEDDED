#ifdef UNIT_TEST

#include <unity.h> // includes unit testing library

#include "stm32f4xx_hal.h"
#include "stepper/partial/stepper_validator.h"
#include "enum/stepper_state.h"

void setUp();    // default setup function
void tearDown(); // default release function

/**************** stepper_home ********************/

void test_stepper_home_should_give_false()
{
    Stepper stepper;
    stepper.homeStep = stepper.lastHomeStep = FAST;

    stepper.state = HOMING;
    TEST_ASSERT_FALSE(home_validator(&stepper));

    stepper.state = MOVING;
    TEST_ASSERT_FALSE(home_validator(&stepper));

    stepper.state = PAUSED;
    TEST_ASSERT_FALSE(home_validator(&stepper));
}

void test_stepper_home_should_give_true()
{
    Stepper stepper;
    stepper.homeStep = stepper.lastHomeStep = FAST;

    stepper.state = OFF;
    TEST_ASSERT_TRUE(home_validator(&stepper));

    stepper.state = OFF;
    TEST_ASSERT_TRUE(home_validator(&stepper));

    stepper.state = ON;
    TEST_ASSERT_TRUE(home_validator(&stepper));

    stepper.state = ON;
    TEST_ASSERT_TRUE(home_validator(&stepper));
}

/**************** stepper_move ********************/

void test_stepper_move_should_give_nine_if_not_allowed_operation()
{
    Stepper stepper;

    stepper.state = HOMING;
    TEST_ASSERT_EQUAL_UINT8(9, move_validator(&stepper, (uint8_t *)"2"));

    stepper.state = MOVING;
    TEST_ASSERT_EQUAL_UINT8(9, move_validator(&stepper, (uint8_t *)"2"));

    stepper.state = PAUSED;
    TEST_ASSERT_EQUAL_UINT8(9, move_validator(&stepper, (uint8_t *)"2"));
}

void test_stepper_move_should_give_false_if_empty()
{
    Stepper stepper;
    stepper.state = OFF;

    TEST_ASSERT_FALSE(move_validator(&stepper, (uint8_t *)""));
}

void test_stepper_move_should_give_false_if_starts_with_0_and_have_others()
{
    Stepper stepper;
    stepper.state = OFF;
    TEST_ASSERT_FALSE(move_validator(&stepper, (uint8_t *)"032"));
}

void test_stepper_move_should_give_false_if_letters_only()
{
    Stepper stepper;
    stepper.state = OFF;
    TEST_ASSERT_FALSE(move_validator(&stepper, (uint8_t *)"ab"));
}

void test_stepper_move_should_give_false_if_mix()
{
    Stepper stepper;
    stepper.state = OFF;
    TEST_ASSERT_FALSE(move_validator(&stepper, (uint8_t *)"1a3"));
}

void test_stepper_move_should_give_false_if_zero()
{
    Stepper stepper;
    stepper.state = OFF;
    TEST_ASSERT_FALSE(move_validator(&stepper, (uint8_t *)"0"));
}

void test_stepper_move_should_give_one_if_negative()
{
    Stepper stepper;
    stepper.state = ON;

    TEST_ASSERT_EQUAL_UINT8(1, move_validator(&stepper, (uint8_t *)"-2"));
}

void test_stepper_move_should_give_one_if_positive()
{
    Stepper stepper;
    stepper.state = ON;

    TEST_ASSERT_EQUAL_UINT8(1, move_validator(&stepper, (uint8_t *)"2"));
}

int main()
{
    HAL_Init();      // initialize the HAL library
    HAL_Delay(2000); // service delay

    UNITY_BEGIN();

    /**************** stepper_home ********************/

    RUN_TEST(test_stepper_home_should_give_false);
    RUN_TEST(test_stepper_home_should_give_true);

    /**************** stepper_move ********************/

    RUN_TEST(test_stepper_move_should_give_nine_if_not_allowed_operation);
    RUN_TEST(test_stepper_move_should_give_false_if_empty);
    RUN_TEST(test_stepper_move_should_give_false_if_starts_with_0_and_have_others);
    RUN_TEST(test_stepper_move_should_give_false_if_letters_only);
    RUN_TEST(test_stepper_move_should_give_false_if_mix);
    RUN_TEST(test_stepper_move_should_give_false_if_zero);
    RUN_TEST(test_stepper_move_should_give_one_if_negative);
    RUN_TEST(test_stepper_move_should_give_one_if_positive);

    UNITY_END();
}

#endif // UNIT_TEST