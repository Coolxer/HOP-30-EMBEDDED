#ifdef UNIT_TEST

#include <unity.h> // includes unit testing library
#include "stm32f4xx_hal.h"
#include "stepper/partial/stepper_validator.h"

void setUp();    // default setup function
void tearDown(); // default release function

/**************** stepper_switch ********************/

void test_stepper_switch_should_give_false()
{
    Stepper stepper;

    stepper.state = HOMING;
    TEST_ASSERT_FALSE(switch_validator(&stepper));

    stepper.state = MOVING;
    TEST_ASSERT_FALSE(switch_validator(&stepper));
}

void test_stepper_switch_should_give_true()
{
    Stepper stepper;

    stepper.state = OFF;
    TEST_ASSERT_TRUE(switch_validator(&stepper));

    stepper.state = ON;
    TEST_ASSERT_TRUE(switch_validator(&stepper));

    stepper.state = PAUSED;
    TEST_ASSERT_TRUE(switch_validator(&stepper));
}

int main()
{
    HAL_Init();      // initialize the HAL library
    HAL_Delay(2000); // service delay

    UNITY_BEGIN();

    /**************** stepper_switch ********************/

    RUN_TEST(test_stepper_switch_should_give_false);
    RUN_TEST(test_stepper_switch_should_give_true);

    UNITY_END();
}

#endif // UNIT_TEST