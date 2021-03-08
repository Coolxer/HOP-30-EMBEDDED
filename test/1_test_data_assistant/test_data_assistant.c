#ifdef UNIT_TEST

#include <unity.h> // includes unit testing library
#include "stm32f4xx_hal.h"
#include "null.h"
#include "command/partial/data_assistant.h"

void setUp();    // default setup function
void tearDown(); // default release function

/************************** char_append() ****************************/

void test_char_append_should_be_white_space()
{
    uint8_t *feedback = EMPTY;
    feedback = charAppend(feedback, ' ');
    TEST_ASSERT_EQUAL_STRING(" ", feedback);
}

void test_char_append_should_be_a()
{
    uint8_t *feedback = EMPTY;
    feedback = charAppend(feedback, 'a');
    TEST_ASSERT_EQUAL_STRING("a", feedback);
}

void test_char_append_should_be_abc_after_append_to_ab()
{
    uint8_t *feedback = (uint8_t *)"ab";

    feedback = charAppend(feedback, 'c');
    TEST_ASSERT_EQUAL_STRING("abc", feedback);
}

void test_char_append_should_be_fine_if_double_append()
{
    uint8_t *feedback = EMPTY;
    feedback = charAppend(feedback, 'a');
    feedback = charAppend(feedback, 'b');

    TEST_ASSERT_EQUAL_STRING("ab", feedback);
}

/************************** str_append() ****************************/

void test_str_append_should_be_empty_if_double_quotes()
{
    uint8_t *feedback = EMPTY;
    feedback = strAppend(feedback, EMPTY);
    TEST_ASSERT_EQUAL_STRING("", feedback);
}

void test_str_append_should_be_a()
{
    uint8_t *feedback = EMPTY;
    feedback = strAppend(feedback, (uint8_t *)"a");
    TEST_ASSERT_EQUAL_STRING("a", feedback);
}

void test_str_append_should_be_abc_after_append_to_a()
{
    uint8_t *feedback = (uint8_t *)"a";

    feedback = strAppend(feedback, (uint8_t *)"bc");
    TEST_ASSERT_EQUAL_STRING("abc", feedback);
}

void test_str_append_should_be_fine_if_double_append()
{
    uint8_t *feedback = (uint8_t *)"ab";

    feedback = strAppend(feedback, (uint8_t *)"cd");
    feedback = strAppend(feedback, (uint8_t *)"ef");

    TEST_ASSERT_EQUAL_STRING("abcdef", feedback);
}

int main()
{
    HAL_Init();      // initialize the HAL library
    HAL_Delay(2000); // service delay

    UNITY_BEGIN();

    RUN_TEST(test_char_append_should_be_white_space);
    RUN_TEST(test_char_append_should_be_a);
    RUN_TEST(test_char_append_should_be_abc_after_append_to_ab);
    RUN_TEST(test_char_append_should_be_fine_if_double_append);

    RUN_TEST(test_str_append_should_be_empty_if_double_quotes);
    RUN_TEST(test_str_append_should_be_a);
    RUN_TEST(test_str_append_should_be_abc_after_append_to_a);
    RUN_TEST(test_str_append_should_be_fine_if_double_append);

    UNITY_END();
}

#endif // UNIT_TEST