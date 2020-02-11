#ifdef UNIT_TEST

#include <unity.h> // includes unit testing library
#include "stm32f4xx_hal.h"
#include "connector.h"

void setUp();// default setup function
void tearDown(); // default release function

// connector_parse() function will be called only if given command has at least 15 characters and the last character is \n (new line terminator)

/******************** connector parse ********************/

void test_connector_parse_should_give_null_if_white_spaces_only()
{
    uint8_t data[] = "              \n";
    uint8_t ***args = connector_parse(data);
    TEST_ASSERT_NULL(args);
}

void test_connector_parse_should_give_null_if_normal_text()
{
    uint8_t data[] = "aaaaaaaaaaaaaa\n";
    uint8_t ***args = connector_parse(data);
    TEST_ASSERT_NULL(args);
}

void test_connector_parse_should_give_null_if_pipes_only()
{
    uint8_t data[] = "||||||||||||||\n";
    uint8_t ***args = connector_parse(data);
    TEST_ASSERT_NULL(args);
}

void test_connector_parse_should_give_null_if_equal_signs_only()
{
    uint8_t data[] = "==============\n";
    uint8_t ***args = connector_parse(data);
    TEST_ASSERT_NULL(args);
}

void test_connector_parse_should_give_one_record()
{
    uint8_t data[] = "aaaaaaa=bbbbbb|\n";
    uint8_t ***args = connector_parse(data);

    TEST_ASSERT_EQUAL_STRING("aaaaaaa", args[0][0]);
    TEST_ASSERT_EQUAL_STRING("bbbbbb", args[0][1]);
}

void test_connector_parse_should_give_three_records()
{
    uint8_t data[] = "a1=b|c1=d|e1=f|\n";
    uint8_t ***args = connector_parse(data);

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
    uint8_t data[] = "aaaaaaaaaaaaaaa|\n";
    uint8_t *result = connector_manage(connector_parse(data));
    TEST_ASSERT_EQUAL_STRING("_ERROR_no_params", result);
}

void test_connector_manage_should_give_one_param_only_error()
{
    uint8_t data[] = "opt=aaaaaaaaaa|\n";

    uint8_t *result = connector_manage(connector_parse(data));

    TEST_ASSERT_EQUAL_STRING("_ERROR_one_param_only", result);
}

void test_connector_manage_should_give_to_many_arguments_error()
{
    uint8_t data[] = "abc=123|spp=12|spd=1|alf=56|\n";

    uint8_t *result = connector_manage(connector_parse(data));

    TEST_ASSERT_EQUAL_STRING("_ERROR_to_many_arguments", result);
}

void test_connector_manage_should_give_no_opt_key_error()
{
    uint8_t data[] = "abc=123|spp=12|\n";

    uint8_t *result = connector_manage(connector_parse(data));

    TEST_ASSERT_EQUAL_STRING("_ERROR_no_opt_key", result);
}

void test_connector_manage_should_give_invalid_opt_value_error()
{
    uint8_t data[] = "opt=123|spp=12|\n";

    uint8_t *result = connector_manage(connector_parse(data));

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
    RUN_TEST(test_connector_manage_should_give_to_many_arguments_error);
    RUN_TEST(test_connector_manage_should_give_no_opt_key_error);
    RUN_TEST(test_connector_manage_should_give_invalid_opt_value_error);
 
    UNITY_END();
}

#endif // UNIT_TEST