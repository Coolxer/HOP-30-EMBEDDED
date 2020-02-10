//#ifdef UNIT_TEST

#include <unity.h> // includes unit testing library
#include <string.h>
#include "connector.h"

#include "stm32f4xx_hal.h"

uint8_t ***args;
uint8_t *result;

void setUp()// default setup function
{
    args = NULL;
    result = "";
}

void tearDown(); // default release function

// connector_parse() function will be called only if givent command has at least 15 characters and the last character is \n (new line)

/******************** connector parse ********************/

void test_connector_parse_should_give_null_if_white_spaces_only()
{
    //args = connector_parse("              \n");
    uint8_t data[] = "              \n";
    args = connector_parse(data);
    TEST_ASSERT_NULL(args);
}

void test_connector_parse_should_give_null_if_normal_text()
{
    //args = connector_parse("aaaaaaaaaaaaaa\n");
    uint8_t data[] = "aaaaaaaaaaaaaa\n";
    args = connector_parse(data);
    TEST_ASSERT_NULL(args);
}

void test_connector_parse_should_give_null_if_pipes_only()
{
    //args = connector_parse("||||||||||||||\n");
    uint8_t data[] = "||||||||||||||\n";
    args = connector_parse(data);
    TEST_ASSERT_NULL(args);
}

void test_connector_parse_should_give_null_if_equal_signs_only()
{
    //args = connector_parse("==============\n");
    uint8_t data[] = "==============\n";
    args = connector_parse(data);
    TEST_ASSERT_NULL(args);
}

void test_connector_parse_should_give_one_record()
{
    //args = connector_parse("aaaaaaa=bbbbbb|\n");

    uint8_t data[] = "aaaaaaa=bbbbbb|\n";
    args = connector_parse(data);

    TEST_ASSERT_EQUAL_STRING("aaaaaaa", args[0][0]);
    TEST_ASSERT_EQUAL_STRING("bbbbbb", args[0][1]);
}

void test_connector_parse_should_give_three_records()
{
    //args = connector_parse("a1=b|c1=d|e1=f|\n");

    uint8_t data[] = "a1=b|c1=d|e1=f|\n";
    args = connector_parse(data);

    TEST_ASSERT_EQUAL_STRING("a1", args[0][0]);
    TEST_ASSERT_EQUAL_STRING("b", args[0][1]);
    TEST_ASSERT_EQUAL_STRING("c1", args[1][0]);
    TEST_ASSERT_EQUAL_STRING("d", args[1][1]);
    TEST_ASSERT_EQUAL_STRING("e1", args[2][0]);
    TEST_ASSERT_EQUAL_STRING("f", args[2][1]);
}

/*********************** connector manage  ********************/

void test_connector_manage_should_give_no_params_error()
{
    result = connector_manage(NULL);
    TEST_ASSERT_EQUAL_STRING("_ERROR_no_params", result);
}

void test_connector_manage_should_give_one_param_only_error()
{
    //args = connector_parse("opt=aaaaaaaaaa|\n");
    uint8_t data[] = "opt=aaaaaaaaaa|\n";
    args = connector_parse(data);

    result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_ERROR_one_param_only", result);
}

void test_connector_manage_should_give_no_opt_key_error()
{
    //args = connector_parse("abc=123|spp=12|\n");
    uint8_t data[] = "abc=123|spp=12|\n";
    args = connector_parse(data);

    result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_ERROR_no_opt_key", result);
}

void test_connector_manage_should_give_invalid_opt_value_error()
{
    //args = connector_parse("opt=123|spp=12|\n");
    uint8_t data[] = "opt=123|spp=12|\n";
    args = connector_parse(data);

    result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_ERROR:invalid_opt_value", result);
}

int main()
{
    HAL_Init();         // initialize the HAL library
    HAL_Delay(2000);    // service delay

    UNITY_BEGIN();

    RUN_TEST(test_connector_parse_should_give_null_if_white_spaces_only);
    RUN_TEST(test_connector_parse_should_give_null_if_normal_text);
    RUN_TEST(test_connector_parse_should_give_null_if_pipes_only);
    RUN_TEST(test_connector_parse_should_give_null_if_equal_signs_only);
    RUN_TEST(test_connector_parse_should_give_one_record);
    RUN_TEST(test_connector_parse_should_give_three_records);

    RUN_TEST(test_connector_manage_should_give_no_params_error);
    RUN_TEST(test_connector_manage_should_give_one_param_only_error);
    RUN_TEST(test_connector_manage_should_give_no_opt_key_error);
    RUN_TEST(test_connector_manage_should_give_invalid_opt_value_error);

    //RUN_TEST(test_led_state_low);

    UNITY_END();
}

//#endif // UNIT_TEST