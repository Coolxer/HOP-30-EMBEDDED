//#ifdef UNIT_TEST
#include <unity.h> // includes unit testing library
#include <stdint.h>
#include "stm32f4xx_hal.h"
#include "stepper.h"

void setUp();// default setup function
void tearDown(); // default release function

void test_stepper_enable()
{
    struct Stepper s;
    stepper_init(&s, "s1", GPIOA, GPIO_PIN_5, 0, 0, 0, 0, 0, 0);

    stepper_enable(&s, true);
    TEST_ASSERT_EQUAL(GPIO_PIN_SET, HAL_GPIO_ReadPin(s.port, s.enable_pin));

}

void test_stepper_disable()
{
    struct Stepper s;
    stepper_init(&s, "s1", GPIOA, GPIO_PIN_5, 0, 0, 0, 0, 0, 0);

    stepper_enable(&s, false);
    TEST_ASSERT_EQUAL(GPIO_PIN_RESET, HAL_GPIO_ReadPin(s.port, s.enable_pin));
}

int main()
{
    HAL_Init(); // initialize the HAL library
    HAL_Delay(2000); // service delay

    UNITY_BEGIN();

    RUN_TEST(test_stepper_enable);
    HAL_Delay(500);
    RUN_TEST(test_stepper_disable);
    HAL_Delay(500);

    UNITY_END();
}

void SysTick_Handler(void) {
    HAL_IncTick();
}

//#endif // UNIT_TEST