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

/**************************************** DATA_FULLFILL TESTS **************************************************************/

// test if data_fullfill fills in empty data array with space_filler's
void test_data_fullfill_should_fill_all_with_space_filler_if_data_empty()
{
    data_clear(data, DATA_SIZE);
    data_fullfill(data, DATA_SIZE);

    TEST_ASSERT_EQUAL_STRING("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~", data);
}

// test if data_fullfill fills in data array (filled with spaces) with space_filler's
void test_data_fullfill_should_fill_all_with_space_filler_if_data_spaces_only()
{
    strcpy(data, "                                                                ");
    data_fullfill(data, DATA_SIZE);

    TEST_ASSERT_EQUAL_STRING("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~", data);
}

// test if data_fullfill fills in data array (half-filled) with space_filler's
void test_data_fullfill_should_fill_only_second_half_with_space_filler_if_half_filled()
{
    data_clear(data, DATA_SIZE);
    strcpy(data, "01234567890123456789012345678901");
    data_fullfill(data, DATA_SIZE);

    TEST_ASSERT_EQUAL_STRING("01234567890123456789012345678901~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~", data);
}

/**************************************** DATA_CROP TESTS **************************************************************/

// test if data_crop should nothing crop, because data is empty
void test_data_crop_should_do_nothing_if_data_empty()
{
    data_clear(data, DATA_SIZE);
    data_crop(data, DATA_SIZE);

    TEST_ASSERT_EQUAL_STRING("", data);
}

// test if data_crop should cut second half, because only first half consists right content
void test_data_crop_should_crop_space_filler_if_half_is_right_content()
{
    data_clear(data, DATA_SIZE);
    strcpy(data, "01234567890123456789012345678901~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    data_crop(data, DATA_SIZE);

    TEST_ASSERT_EQUAL_STRING("01234567890123456789012345678901", data);
}

int main()
{
    UNITY_BEGIN();

    RUN_TEST(test_data_clear);

    RUN_TEST(test_data_fullfill_should_fill_all_with_space_filler_if_data_empty);
    RUN_TEST(test_data_fullfill_should_fill_all_with_space_filler_if_data_spaces_only);
    RUN_TEST(test_data_fullfill_should_fill_only_second_half_with_space_filler_if_half_filled);

    RUN_TEST(test_data_crop_should_do_nothing_if_data_empty);
    RUN_TEST(test_data_crop_should_crop_space_filler_if_half_is_right_content);

    UNITY_END();
}

#endif // UNIT_TEST