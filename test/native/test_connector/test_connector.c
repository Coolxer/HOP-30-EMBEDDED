#ifdef UNIT_TEST

#include <unity.h> // includes unit testing library
#include "connector.h"

void setUp()
{

}

void tearDown()
{

}


void test_connector_string_size_should_be_zero()
{
    uint8_t *string = "";
    TEST_ASSERT_EQUAL_UINT8(0, connector_string_size(string));
}

void test_connector_string_size_should_be_five()
{
    uint8_t *string = "12345";
    TEST_ASSERT_EQUAL_UINT8(0, connector_string_size(string));
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_connector_string_size_should_be_zero);
    RUN_TEST(test_connector_string_size_should_be_five);
    UNITY_END();
}

#endif // UNIT_TEST