#ifdef UNIT_TEST

#include <unity.h> // includes unit testing library

#include "stm32f4xx_hal.h"
#include "stepper/partial/stepper_validator.h"
#include "enum/stepper_state.h"

void setUp();    // default setup function
void tearDown(); // default release function

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

int main()
{
    HAL_Init();      // initialize the HAL library
    HAL_Delay(2000); // service delay

    UNITY_BEGIN();

    RUN_TEST(test_stepper_home_should_give_false);
    RUN_TEST(test_stepper_home_should_give_true);

    UNITY_END();
}

#endif // UNIT_TEST