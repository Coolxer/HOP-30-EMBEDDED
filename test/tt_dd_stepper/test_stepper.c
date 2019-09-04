#ifdef UNIT_TEST

#include <unity.h> // includes unit testing library
#include <stdint.h>
#include "stm32f4xx_hal.h"
#include "stepper.h"

void setUp();// default setup function
void tearDown(); // default release function

// test if stepper_toggle switch ON
void test_stepper_toggle_should_turn_on()
{
    struct Stepper s;
    stepper_init(&s, "s1", GPIOA, GPIO_PIN_5, 0, 0, 0, 0, 0, 0);

    HAL_GPIO_WritePin(s.port, s.enable_pin, GPIO_PIN_RESET);

    TEST_ASSERT_TRUE(stepper_toggle(&s));
}

// test if stepper_toggle switch OFF
void test_stepper_toggle_should_turn_off()
{
    struct Stepper s;
    stepper_init(&s, "s1", GPIOA, GPIO_PIN_5, 0, 0, 0, 0, 0, 0);

    HAL_GPIO_WritePin(s.port, s.enable_pin, GPIO_PIN_SET);

    TEST_ASSERT_TRUE(stepper_toggle(&s));
}

int main()
{
    HAL_Init(); // initialize the HAL library
    HAL_Delay(2000); // service delay

    UNITY_BEGIN();

    RUN_TEST(test_stepper_toggle_should_turn_on);
    HAL_Delay(500);
    RUN_TEST(test_stepper_toggle_should_turn_off);
    HAL_Delay(500);

    UNITY_END();
}

#endif // UNIT_TEST