#ifdef UNIT_TEST

#include <unity.h> // includes unit testing library
#include "data_assistant.h"

void setUp();// default setup function
void tearDown(); // default release function

/************************** char_append() ****************************/

void test_char_append_should_be_white_space()
{
    uint8_t* feedback = "";
    feedback = char_append(feedback, ' ');
    TEST_ASSERT_EQUAL_STRING(" ", feedback);
}

void test_char_append_should_be_a()
{
    uint8_t* feedback = "";
    feedback = char_append(feedback, 'a');
    TEST_ASSERT_EQUAL_STRING("a", feedback);
}

void test_char_append_should_be_abc_after_append_to_ab()
{
    uint8_t* feedback = "ab";

    feedback = char_append(feedback, 'c');
    TEST_ASSERT_EQUAL_STRING("abc", feedback);
}

void test_char_append_should_be_fine_if_double_append()
{
    uint8_t* feedback = "";
    feedback = char_append(feedback, 'a');
    feedback = char_append(feedback, 'b');

    TEST_ASSERT_EQUAL_STRING("ab", feedback);
}

/************************** str_append() ****************************/

void test_str_append_should_be_empty_if_double_quotes()
{
    uint8_t* feedback = "";
    feedback = str_append(feedback, "");
    TEST_ASSERT_EQUAL_STRING("", feedback);
}

void test_str_append_should_be_a()
{
    uint8_t* feedback = "";
    feedback = str_append(feedback, "a");
    TEST_ASSERT_EQUAL_STRING("a", feedback);
}

void test_str_append_should_be_abc_after_append_to_a()
{
    uint8_t* feedback = "a";

    feedback = str_append(feedback, "bc");
    TEST_ASSERT_EQUAL_STRING("abc", feedback);
}

void test_str_append_should_be_fine_if_double_append()
{
    uint8_t* feedback = "ab";

    feedback = str_append(feedback, "cd");
    feedback = str_append(feedback, "ef");

    TEST_ASSERT_EQUAL_STRING("abcdef", feedback);
}

int main()
{
    HAL_Init();         // initialize the HAL library
    HAL_Delay(2000);    // service delay

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