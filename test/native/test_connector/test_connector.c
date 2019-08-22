//#ifdef UNIT_TEST

#include <unity.h> // includes unit testing library
#include <string.h>
#include "connector.h"

void setUp();// default setup function
void tearDown(); // default release function

/************************************** CONNECTOR_STRING_SIZE TESTS ******************************************************/

// test if the string is empty
void test_connector_string_size_should_be_zero() 
{
    uint8_t string[] = "";
    TEST_ASSERT_EQUAL_UINT8(0, connector_string_size(string));
}

// test if the string is length is 3
void test_connector_string_size_should_be_three() 
{
    uint8_t string[] = "123";
    TEST_ASSERT_EQUAL_UINT8(3, connector_string_size(string));
}

// test if the string length is 5
void test_connector_string_size_should_be_five() 
{
    uint8_t string[] = "12345";
    TEST_ASSERT_EQUAL_UINT8(5, connector_string_size(string));
}

/*************************************** CONNECTOR_PARSE TESTS ***********************************************************/

// test if connector_parse returns NULL if the dialog is empty
void test_connector_parse_should_give_null_if_dialog_empty() 
{
    uint8_t ***args = NULL, size = 0;
    args = connector_parse(&size);
    TEST_ASSERT_NULL(args);
}

// test if connector_parse returns NULL if the dialog consists pipes only
void test_connector_parse_should_give_null_if_pipes_only() 
{
    uint8_t ***args = NULL, size = 0;
    strcpy(data, "|||||");
    args = connector_parse(&size);
    TEST_ASSERT_NULL(args);
}

// test if connector_parse returns NULL if only 1 record (that's incorrect, because you cannnot build correct, working command with only one sentence)
void test_connector_parse_should_give_null_if_one_record_only() 
{
    uint8_t ***args = NULL, size = 0;
    strcpy(data, "opt=value1|");
    args = connector_parse(&size);
    TEST_ASSERT_NULL(args);
}

// test if connector_parse return NULL if there is no opt parameter at start
void test_connector_parse_should_give_null_if_no_opt_parameter() 
{
    uint8_t ***args = NULL, size = 0;
    strcpy(data, "key1=value1|");
    args = connector_parse(&size);
    TEST_ASSERT_NULL(args); 
}

// test if connector_parse returns 3 records with correct keys & values
void test_connector_parse_should_give_three_records() 
{
    uint8_t ***args = NULL, size = 0;
    strcpy(data, "opt=value1|key2=value2|key3=value3|");
    args = connector_parse(&size);

    TEST_ASSERT_EQUAL_STRING("opt", args[0][0]);
    TEST_ASSERT_EQUAL_STRING("value1", args[0][1]);
    TEST_ASSERT_EQUAL_STRING("key2", args[1][0]);
    TEST_ASSERT_EQUAL_STRING("value2", args[1][1]);
    TEST_ASSERT_EQUAL_STRING("key3", args[2][0]);
    TEST_ASSERT_EQUAL_STRING("value3", args[2][1]);
}

/********************************* CONNECTOR_MANAGE_DATA TESTS ***********************************************************/

// test if connector_manage_data no manipulate size if input array is NULL
void test_connector_manage_data_fixed_size_should_be_zero() 
{
    uint8_t size = 0;
    connector_manage_data(NULL, &size);

    TEST_ASSERT_EQUAL_UINT8(0, size);
}

// test if connector_manage_data manipulate size from 3 to 2 if array has 3 records
void test_connector_manage_data_fixed_size_should_be_two_if_three_records() 
{
    uint8_t ***args = NULL, size = 0;
    strcpy(data, "opt=value1|key2=value2|key3=value3");
    connector_manage_data(connector_parse(&size), &size);

    TEST_ASSERT_EQUAL_UINT8(2, size);
}

// test if strcpm builded in function property compares strings
void test_connector_manage_data_opt_value_should_be_mov() 
{
    uint8_t ***args = NULL, size = 0;
    strcpy(data, "opt=mov|key2=value2|key3=value3");

    args = connector_parse(&size);

    TEST_ASSERT_TRUE(strcmp((void *)args[0][1], "mov") == 0);
}

/**************************************** CONNECTOR_CLEAR_DATA TESTS ****************************************************/

void test_connector_clear_data()
{
    strcpy(data, "01234567890012345678900123345564");

    connector_clear_data();

    TEST_ASSERT_EQUAL_STRING("", data);
}

/**************************************** CONNECTOR_BUILD_DATA TESTS *****************************************************/

// test if connector_build_data fills in empty data array with space_filler's
void test_connector_build_data_should_fill_all_with_space_filler_if_data_empty()
{
    connector_clear_data();
    connector_build_data();

    TEST_ASSERT_EQUAL_STRING("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~", data);
}

// test if connector_build_data fills in data array (filled with spaces) with space_filler's
void test_connector_build_data_should_fill_all_with_space_filler_if_data_spaces_only()
{
    strcpy(data, "                                                                ");
    connector_build_data();

    TEST_ASSERT_EQUAL_STRING("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~", data);
}

// test if connector_build_data fills in data array (half-filled) with space_filler's
void test_connector_build_data_should_fill_only_second_half_with_space_filler_if_half_filled()
{
    strcpy(data, "01234567890123456789012345678901");
    connector_build_data();

    TEST_ASSERT_EQUAL_STRING("01234567890123456789012345678901~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~", data);
}

/**************************************** CONNECTOR_CUT_DATA TESTS *******************************************************/



int main()
{
    UNITY_BEGIN();

    RUN_TEST(test_connector_string_size_should_be_zero);
    RUN_TEST(test_connector_string_size_should_be_three);
    RUN_TEST(test_connector_string_size_should_be_five);

    RUN_TEST(test_connector_parse_should_give_null_if_dialog_empty);
    RUN_TEST(test_connector_parse_should_give_null_if_pipes_only);
    RUN_TEST(test_connector_parse_should_give_null_if_one_record_only);
    RUN_TEST(test_connector_parse_should_give_null_if_no_opt_parameter);
    RUN_TEST(test_connector_parse_should_give_three_records);

    RUN_TEST(test_connector_manage_data_fixed_size_should_be_zero);
    RUN_TEST(test_connector_manage_data_fixed_size_should_be_two_if_three_records);
    RUN_TEST(test_connector_manage_data_opt_value_should_be_mov);

    RUN_TEST(test_connector_clear_data);

    RUN_TEST(test_connector_build_data_should_fill_all_with_space_filler_if_data_empty);
    RUN_TEST(test_connector_build_data_should_fill_all_with_space_filler_if_data_spaces_only);
    RUN_TEST(test_connector_build_data_should_fill_only_second_half_with_space_filler_if_half_filled);

    UNITY_END();
}

//#endif // UNIT_TEST