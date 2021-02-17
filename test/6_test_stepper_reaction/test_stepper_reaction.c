#ifdef UNIT_TEST

#include <unity.h> // includes unit testing library
#include "stm32f4xx_hal.h"
#include "stepper/partial/stepper_validator.h"

void setUp();    // default setup function
void tearDown(); // default release function

/**************** stepper_pause ********************/

void test_stepper_pause_should_give_false()
{
    Stepper stepper;

    stepper.state = OFF;
    TEST_ASSERT_FALSE(pause_validator(&stepper));

    stepper.state = ON;
    TEST_ASSERT_FALSE(pause_validator(&stepper));

    stepper.state = PAUSED;
    TEST_ASSERT_FALSE(pause_validator(&stepper));
}

void test_stepper_pause_should_give_true()
{
    Stepper stepper;

    stepper.state = HOMING;
    TEST_ASSERT_TRUE(pause_validator(&stepper));

    stepper.state = MOVING;
    TEST_ASSERT_TRUE(pause_validator(&stepper));
}

/**************** stepper_resume ********************/

void test_stepper_resume_should_give_false()
{
    Stepper stepper;

    stepper.state = OFF;
    TEST_ASSERT_FALSE(resume_validator(&stepper));

    stepper.state = ON;
    TEST_ASSERT_FALSE(resume_validator(&stepper));

    stepper.state = HOMING;
    TEST_ASSERT_FALSE(resume_validator(&stepper));

    stepper.state = MOVING;
    TEST_ASSERT_FALSE(resume_validator(&stepper));
}

void test_stepper_resume_should_give_true()
{
    Stepper stepper;

    stepper.state = PAUSED;
    TEST_ASSERT_TRUE(resume_validator(&stepper));
}

/**************** stepper_stop ********************/

void test_stepper_stop_should_give_false()
{
    Stepper stepper;

    stepper.state = OFF;
    TEST_ASSERT_FALSE(stop_validator(&stepper));

    stepper.state = ON;
    TEST_ASSERT_FALSE(stop_validator(&stepper));
}

void test_stepper_stop_should_give_true()
{
    Stepper stepper;

    stepper.state = HOMING;
    TEST_ASSERT_TRUE(stop_validator(&stepper));

    stepper.state = MOVING;
    TEST_ASSERT_TRUE(stop_validator(&stepper));

    stepper.state = PAUSED;
    TEST_ASSERT_TRUE(stop_validator(&stepper));
}

int main()
{
    HAL_Init();      // initialize the HAL library
    HAL_Delay(2000); // service delay

    UNITY_BEGIN();

    /**************** stepper_pause ********************/

    RUN_TEST(test_stepper_pause_should_give_false);
    RUN_TEST(test_stepper_pause_should_give_true);

    /**************** stepper_resume ********************/

    RUN_TEST(test_stepper_resume_should_give_false);
    RUN_TEST(test_stepper_resume_should_give_true);

    /**************** stepper_stop ********************/

    RUN_TEST(test_stepper_stop_should_give_false);
    RUN_TEST(test_stepper_stop_should_give_true);

    UNITY_END();
}

#endif // UNIT_TEST