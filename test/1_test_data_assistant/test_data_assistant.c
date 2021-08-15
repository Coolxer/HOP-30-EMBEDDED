#ifdef UNIT_TEST

#include <unity.h> // includes unit testing library

#include "stm32f4xx_hal.h"

#include "data/assistant.h"

void setUp();
void tearDown();

void test_contains_only_digits_should_give_false()
{
    TEST_ASSERT_EQUAL_UINT8(0, containsOnlyDigits(" "));
    TEST_ASSERT_EQUAL_UINT8(0, containsOnlyDigits("a"));
    TEST_ASSERT_EQUAL_UINT8(0, containsOnlyDigits(" 1"));
    TEST_ASSERT_EQUAL_UINT8(0, containsOnlyDigits("a1"));
}

void test_contains_only_digits_should_give_true()
{
    TEST_ASSERT_EQUAL_UINT8(1, containsOnlyDigits("0"));
    TEST_ASSERT_EQUAL_UINT8(1, containsOnlyDigits("1"));
    TEST_ASSERT_EQUAL_UINT8(1, containsOnlyDigits("12"));
    TEST_ASSERT_EQUAL_UINT8(1, containsOnlyDigits("123"));
}

int main()
{
    HAL_Init();      // initialize the HAL library
    HAL_Delay(2000); // service delay

    UNITY_BEGIN();

    RUN_TEST(test_contains_only_digits_should_give_false);
    RUN_TEST(test_contains_only_digits_should_give_true);

    UNITY_END();
}

#endif // UNIT_TEST