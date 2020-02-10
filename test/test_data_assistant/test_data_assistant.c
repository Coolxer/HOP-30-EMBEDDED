//#ifdef UNIT_TEST

#include <unity.h> // includes unit testing library
#include <string.h>
#include "data_assistant.h"

#include "stm32f4xx_hal.h"

uint8_t* feedback;

void setUp()// default setup function
{
    feedback = "";
}

void tearDown(); // default release function

/************************** char_append() ****************************/

void test_char_append_should_be_white_space()
{
    feedback = char_append(feedback, ' ');
    TEST_ASSERT_EQUAL_STRING(" ", feedback);
}

void test_char_append_should_be_a()
{
    feedback = char_append(feedback, 'a');
    TEST_ASSERT_EQUAL_STRING("a", feedback);
}

void test_char_append_should_be_abc_after_append_to_ab()
{
    feedback = "ab";

    feedback = char_append(feedback, 'c');
    TEST_ASSERT_EQUAL_STRING("abc", feedback);
}

/*
void test_char_append_should_pass_through_if_a_in_double_quotes()
{
    feedback = char_append(feedback, "a");
    TEST_ASSERT_EQUAL_STRING("a", feedback);
}
*/

void test_char_append_should_be_fine_if_double_append()
{
    feedback = char_append(feedback, 'a');
    feedback = char_append(feedback, 'b');

    TEST_ASSERT_EQUAL_STRING("ab", feedback);
}

/************************** str_append() ****************************/

void test_str_append_should_be_empty_if_double_quotes()
{
    feedback = str_append(feedback, "");
    TEST_ASSERT_EQUAL_STRING("", feedback);
}

void test_str_append_should_be_a()
{
    feedback = str_append(feedback, "a");
    TEST_ASSERT_EQUAL_STRING("a", feedback);
}

void test_str_append_should_be_abc_after_append_to_a()
{
    feedback = "a";

    feedback = str_append(feedback, "bc");
    TEST_ASSERT_EQUAL_STRING("abc", feedback);
}

void test_str_append_should_be_fine_if_double_append()
{
    feedback = "a";

    feedback = str_append(feedback, "b");
    feedback = str_append(feedback, "cd");
    TEST_ASSERT_EQUAL_STRING("abcd", feedback);
}

int main()
{
    HAL_Init();         // initialize the HAL library
    HAL_Delay(2000);    // service delay

    UNITY_BEGIN();
    
    RUN_TEST(test_char_append_should_be_white_space);
    RUN_TEST(test_char_append_should_be_a);
    RUN_TEST(test_char_append_should_be_abc_after_append_to_ab);
    //RUN_TEST(test_char_append_should_pass_through_if_a_in_double_quotes);
    RUN_TEST(test_char_append_should_be_fine_if_double_append);

    RUN_TEST(test_str_append_should_be_empty_if_double_quotes);
    RUN_TEST(test_str_append_should_be_a);
    RUN_TEST(test_str_append_should_be_abc_after_append_to_a);
    RUN_TEST(test_str_append_should_be_fine_if_double_append);

    UNITY_END();
}

//#endif // UNIT_TEST