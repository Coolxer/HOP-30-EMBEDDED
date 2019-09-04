#ifdef UNIT_TEST

#include <unity.h> // includes unit testing library
#include <string.h>
#include "data_assistant.h"

#define DATA_SIZE 64

uint8_t data[DATA_SIZE];

void setUp();// default setup function
void tearDown(); // default release function

/**************************************** DATA_CLEAR TESTS *************************************************************/

// test if data_clear correctly clears the array
void test_data_clear()
{
    strcpy(data, "12345");
    data_clear(data, DATA_SIZE);

    TEST_ASSERT_EQUAL_STRING("", data);
}

/**************************************** DATA_BUILD TESTS **************************************************************/

// test if data_build fills in empty data array with space_filler's
void test_data_build_should_fill_all_with_space_filler_if_data_empty()
{
    data_clear(data, DATA_SIZE);
    data_build(data, DATA_SIZE);

    TEST_ASSERT_EQUAL_STRING("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~", data);
}

// test if data_build fills in data array (filled with spaces) with space_filler's
void test_data_build_should_fill_all_with_space_filler_if_data_spaces_only()
{
    strcpy(data, "                                                                ");
    data_build(data, DATA_SIZE);

    TEST_ASSERT_EQUAL_STRING("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~", data);
}

// test if data_build fills in data array (half-filled) with space_filler's
void test_data_build_should_fill_only_second_half_with_space_filler_if_half_filled()
{
    data_clear(data, DATA_SIZE);
    strcpy(data, "01234567890123456789012345678901");
    data_build(data, DATA_SIZE);

    TEST_ASSERT_EQUAL_STRING("01234567890123456789012345678901~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~", data);
}

int main()
{
    UNITY_BEGIN();

    RUN_TEST(test_data_clear);

    RUN_TEST(test_data_build_should_fill_all_with_space_filler_if_data_empty);
    RUN_TEST(test_data_build_should_fill_all_with_space_filler_if_data_spaces_only);
    RUN_TEST(test_data_build_should_fill_only_second_half_with_space_filler_if_half_filled);

    UNITY_END();
}



#endif // UNIT_TEST