//#ifdef UNIT_TEST

#include <unity.h> // includes unit testing library
#include <string.h>
#include "connector.h"

#include "stm32f4xx_hal.h"

uint8_t data[64];
uint8_t ***args;
uint8_t *result;

void setUp()// default setup function
{
    args = NULL;
}

void tearDown(); // default release function

// connector_parse() function will be called only if givent command has at least 15 characters and the last character is \n (new line)

/******************** connector parse ********************/

void test_connector_parse_should_give_null_if_white_spaces_only()
{
    strcpy(data, "              \n");
    args = connector_parse(data);

    TEST_ASSERT_NULL(args);
}

void test_connector_parse_should_give_null_if_normal_text()
{
    strcpy(data, "aaaaaaaaaaaaaa\n");
    args = connector_parse(data);

    TEST_ASSERT_NULL(args);
}

void test_connector_parse_should_give_null_if_pipes_only()
{
    strcpy(data, "||||||||||||||\n");
    args = connector_parse(data);

    TEST_ASSERT_NULL(args);
}

void test_connector_parse_should_give_null_if_equal_signs_only()
{
    strcpy(data, "==============\n");
    args = connector_parse(data);

    TEST_ASSERT_NULL(args);
}

void test_connector_parse_should_give_one_record()
{
    strcpy(data, "aaaaaaa=bbbbbb|\n");
    args = connector_parse(data);

    TEST_ASSERT_EQUAL_STRING("aaaaaaa", args[0][0]);
    TEST_ASSERT_EQUAL_STRING("bbbbbb", args[0][1]);
}

void test_connector_parse_should_give_three_records()
{
    strcpy(data, "a1=b|c1=d|e1=f|\n");
    args = connector_parse(data);

    TEST_ASSERT_EQUAL_STRING("a1", args[0][0]);
    TEST_ASSERT_EQUAL_STRING("b", args[0][1]);
    TEST_ASSERT_EQUAL_STRING("c1", args[1][0]);
    TEST_ASSERT_EQUAL_STRING("d", args[1][1]);
    TEST_ASSERT_EQUAL_STRING("e1", args[2][0]);
    TEST_ASSERT_EQUAL_STRING("f", args[2][1]);
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

    //RUN_TEST(test_led_state_low);

    UNITY_END();
}

//#endif // UNIT_TEST