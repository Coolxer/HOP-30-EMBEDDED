//#ifdef UNIT_TEST

#include <unity.h> // includes unit testing library
#include "connector.h"

void setUp(); // default setup function
void tearDown(); // de

/* CONNECTOR_STRING_SIZE TESTS ******************************************************/

void test_connector_string_size_should_be_zero() // test if the string is empty
{
    uint8_t *string = "";
    TEST_ASSERT_EQUAL_UINT8(0, connector_string_size(string));
}

void test_connector_string_size_should_be_three() // test if the string is length is 3
{
    uint8_t *string = "123";
    TEST_ASSERT_EQUAL_UINT8(3, connector_string_size(string));
}

void test_connector_string_size_should_be_five() // test if the string length is 5
{
    uint8_t *string = "12345";
    TEST_ASSERT_EQUAL_UINT8(5, connector_string_size(string));
}

/* CONNECTOR_PARSE TESTS ***********************************************************/

void test_connector_parse_should_give_null() // test if connector_parse returns NULL if the dialog is empty
{
    uint8_t ***args = NULL, *dialog = "";
    args = connector_parse(dialog);
    TEST_ASSERT_NULL(args);
}

void test_connector_parse_should_give_three_records() // test if connector_parse returns 3 records with correct keys & values
{
    uint8_t ***args = NULL, i;
    uint8_t dialog[] = "key1=value1|key2=value2|key3=value3|";

    args = connector_parse(dialog);

    TEST_ASSERT_EQUAL_STRING("key1", args[0][0]);
    TEST_ASSERT_EQUAL_STRING("value1", args[0][1]);
    TEST_ASSERT_EQUAL_STRING("key2", args[1][0]);
    TEST_ASSERT_EQUAL_STRING("value2", args[1][1]);
    TEST_ASSERT_EQUAL_STRING("key3", args[2][0]);
    TEST_ASSERT_EQUAL_STRING("value3", args[2][1]);
}

void test_connector_parse_should_give_five_records() // test if connector_parse returns 5 records with correct keys & values
{
    uint8_t ***args = NULL, i;
    uint8_t dialog[] = "key1=value1|key2=value2|key3=value3|key4=value4|key5=value5|";

    args = connector_parse(dialog);

    TEST_ASSERT_EQUAL_STRING("key1", args[0][0]);
    TEST_ASSERT_EQUAL_STRING("value1", args[0][1]);
    TEST_ASSERT_EQUAL_STRING("key2", args[1][0]);
    TEST_ASSERT_EQUAL_STRING("value2", args[1][1]);
    TEST_ASSERT_EQUAL_STRING("key3", args[2][0]);
    TEST_ASSERT_EQUAL_STRING("value3", args[2][1]);
    TEST_ASSERT_EQUAL_STRING("key4", args[3][0]);
    TEST_ASSERT_EQUAL_STRING("value4", args[3][1]);
    TEST_ASSERT_EQUAL_STRING("key5", args[4][0]);
    TEST_ASSERT_EQUAL_STRING("value5", args[4][1]);
}

int main()
{
    UNITY_BEGIN();

    RUN_TEST(test_connector_string_size_should_be_zero);
    RUN_TEST(test_connector_string_size_should_be_three);
    RUN_TEST(test_connector_string_size_should_be_five);

    RUN_TEST(test_connector_parse_should_give_null);
    RUN_TEST(test_connector_parse_should_give_three_records);
    RUN_TEST(test_connector_parse_should_give_five_records);

    UNITY_END();
}

//#endif // UNIT_TEST