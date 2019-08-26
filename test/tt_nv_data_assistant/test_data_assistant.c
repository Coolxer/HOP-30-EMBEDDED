#ifdef UNIT_TEST

#include <unity.h> // includes unit testing library
#include <string.h>
#include "data_assistant.h"

void setUp();// default setup function
void tearDown(); // default release function

/************************************** DATA_LENGTH TESTS ******************************************************/

// test if data_length return 0 if the string is empty
void test_data_length_should_be_zero() 
{
    uint8_t string[64];
    strcpy(string, "");
    TEST_ASSERT_EQUAL_UINT8(0, data_length(string));
}

// test if data_length returns 3 if string length is 3
void test_data_length_should_be_three() 
{
    uint8_t string[64];
    strcpy(string, "123");
    TEST_ASSERT_EQUAL_UINT8(3, data_length(string));
}

// test if data_length returns 5 if string length is 5
void test_data_length_should_be_five() 
{
    uint8_t string[64];
    strcpy(string, "12345");
    TEST_ASSERT_EQUAL_UINT8(5, data_length(string));
}

/************************************** DATA_SIZE TESTS ******************************************************/
void test_data_size_should_return_64()
{
    uint8_t string[64];
    strcpy(string, "");

    TEST_ASSERT_EQUAL_UINT8(64, data_size(string));
}

/**************************************** DATA_CLEAR TESTS *************************************************************/

// test if data_clear correctly clears the array
void test_data_clear()
{
    uint8_t string[64];
    strcpy(string, "12345");
    data_clear(string);

    TEST_ASSERT_EQUAL_STRING("", string);
}

/**************************************** DATA_BUILD TESTS **************************************************************/

// test if data_build fills in empty data array with space_filler's
void test_data_build_should_fill_all_with_space_filler_if_data_empty()
{
    uint8_t string[64];
    data_clear(string);
    data_build(string);

    TEST_ASSERT_EQUAL_STRING("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~", string);
}

// test if data_build fills in data array (filled with spaces) with space_filler's
void test_data_build_should_fill_all_with_space_filler_if_data_spaces_only()
{
    uint8_t string[64];
    strcpy(string, "                                                                ");
    data_build(string);

    TEST_ASSERT_EQUAL_STRING("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~", string);
}

// test if data_build fills in data array (half-filled) with space_filler's
void test_data_build_should_fill_only_second_half_with_space_filler_if_half_filled()
{
    uint8_t string[64];
    data_clear(string);
    strcpy(string, "01234567890123456789012345678901");
    data_build(string);

    TEST_ASSERT_EQUAL_STRING("01234567890123456789012345678901~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~", string);
}

int main()
{
    UNITY_BEGIN();

    RUN_TEST(test_data_length_should_be_zero);
    RUN_TEST(test_data_length_should_be_three);
    RUN_TEST(test_data_length_should_be_five);

    RUN_TEST(test_data_size_should_return_64);

    RUN_TEST(test_data_clear);

    RUN_TEST(test_data_build_should_fill_all_with_space_filler_if_data_empty);
    RUN_TEST(test_data_build_should_fill_all_with_space_filler_if_data_spaces_only);
    RUN_TEST(test_data_build_should_fill_only_second_half_with_space_filler_if_half_filled);

    UNITY_END();
}



#endif // UNIT_TEST