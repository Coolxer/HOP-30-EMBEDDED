//#ifdef UNIT_TEST

#include <unity.h> // includes unit testing library
#include <string.h>
#include "connector.h"

void setUp();// default setup function
void tearDown(); // default release function


/*************************************** CONNECTOR_PARSE TESTS ***********************************************************/

// test if connector_parse returns NULL if the dialog is empty
void test_connector_parse_should_give_null_if_dialog_empty() 
{
    uint8_t ***args = NULL, dt[64], args_size = 0;
    strcpy(dt, ""); 
    args = connector_parse(dt, &args_size);
    TEST_ASSERT_NULL(args);
}

// test if connector_parse returns NULL if the dialog consists pipes only
void test_connector_parse_should_give_null_if_pipes_only() 
{
    uint8_t ***args = NULL, dt[64], args_size = 0; 
    strcpy(dt, "|||||");
    args = connector_parse(dt, &args_size);
    TEST_ASSERT_NULL(args);
}

// test if connector_parse returns 3 records with correct keys & values
void test_connector_parse_should_give_three_records() 
{
    uint8_t ***args = NULL, dt[64], args_size = 0;
    strcpy(dt, "key1=value1|key2=value2|key3=value3|");
    args = connector_parse(dt, &args_size);

    TEST_ASSERT_EQUAL_STRING("key1", args[0][0]);
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
    uint8_t ***args = NULL, dt[64], args_size = 0;
    strcpy(dt, "");
    connector_manage_data(NULL, &args_size);

    TEST_ASSERT_EQUAL_UINT8(0, args_size);
}

// test if connector_manage_data manipulate size from 3 to 2 if array has 3 records
void test_connector_manage_data_fixed_size_should_be_two_if_three_records() 
{
    uint8_t ***args = NULL, dt[64], args_size = 0;
    strcpy(dt, "opt=value1|key2=value2|key3=value3");
    connector_manage_data(connector_parse(dt, &args_size), &args_size);

    TEST_ASSERT_EQUAL_UINT8(2, args_size);
}

// test if connector_manage_data should throw ERROR_none_params
void test_connector_manage_data_should_throw_no_params_ERROR() 
{
    uint8_t ***args = NULL, dt[64], args_size = 0, *result; 
    strcpy(dt, "");
    result = connector_manage_data(connector_parse(dt, &args_size), &args_size);
    TEST_ASSERT_EQUAL_STRING("_ERROR_no_params", result);
}

// test if connector_manage_data should throw ERROR_one_param_only
void test_connector_manage_data_should_throw_one_param_only_ERROR() 
{
    uint8_t ***args = NULL, dt[64], args_size = 0, *result; 
    strcpy(dt, "opt=value1|");
    result = connector_manage_data(connector_parse(dt, &args_size), &args_size);
    TEST_ASSERT_EQUAL_STRING("_ERROR:one_param_only", result);
}

// test if connector_manage_data should throw ERROR_no_opt_key
void test_connector_manage_data_should_throw_no_opt_key_ERROR() 
{
    uint8_t ***args = NULL, dt[64], args_size = 0, *result; 
    strcpy(dt, "key1=value1|key2=value2|");
    result = connector_manage_data(connector_parse(dt, &args_size), &args_size);
    TEST_ASSERT_EQUAL_STRING("_ERROR:no_opt_key", result);
}

// test if connector_manage_data should throw COMBO ERROR_one_parameter_only && ERROR_no_opt_key
void test_connector_manage_data_should_throw_on_param_only_and_no_opt_key_ERROR() 
{
    uint8_t ***args = NULL, dt[64], args_size = 0, *result; 
    strcpy(dt, "key1=value1|");
    result = connector_manage_data(connector_parse(dt, &args_size), &args_size);
    TEST_ASSERT_EQUAL_STRING("_ERROR:one_param_only_ERROR:no_opt_key", result);
}

// test if strcpm builded in function property compares strings
void test_connector_manage_data_opt_value_should_be_mov() 
{
    uint8_t ***args = NULL, dt[64], args_size = 0, *result; 
    strcpy(dt, "opt=mov|key2=value2|key3=value3");

    args = connector_parse(dt, &args_size);

    TEST_ASSERT_TRUE(strcmp((void *)args[0][1], "mov") == 0);
}

/**************************************** CONNECTOR_CUT_DATA TESTS *******************************************************/

int main()
{
    UNITY_BEGIN();

    RUN_TEST(test_connector_parse_should_give_null_if_dialog_empty);
    RUN_TEST(test_connector_parse_should_give_null_if_pipes_only);
    RUN_TEST(test_connector_parse_should_give_three_records);

    RUN_TEST(test_connector_manage_data_fixed_size_should_be_zero);
    RUN_TEST(test_connector_manage_data_fixed_size_should_be_two_if_three_records);
    RUN_TEST(test_connector_manage_data_should_throw_no_params_ERROR);
    RUN_TEST(test_connector_manage_data_should_throw_one_param_only_ERROR);
    RUN_TEST(test_connector_manage_data_should_throw_no_opt_key_ERROR);
    RUN_TEST(test_connector_manage_data_should_throw_on_param_only_and_no_opt_key_ERROR);

    RUN_TEST(test_connector_manage_data_opt_value_should_be_mov);

    UNITY_END();
}

//#endif // UNIT_TEST