#ifdef UNIT_TEST

#include <unity.h> // includes unit testing library

#include "stm32f4xx_hal.h"

#include "command/request/request_parser.h"

void setUp();
void tearDown();

void test_request_explode_should_give_null_if_white_spaces_only()
{
    uint8_t data[] = "              \n";
    uint8_t records = 0;

    TEST_ASSERT_NULL(request_explode(data, &records));
    TEST_ASSERT_EQUAL_UINT8(0, records);
}

void test_request_explode_should_give_null_if_normal_text()
{
    uint8_t data[] = "aaaaaaaaaaaaaa\n";
    uint8_t records = 0;

    TEST_ASSERT_NULL(request_explode(data, &records));
    TEST_ASSERT_EQUAL_UINT8(0, records);
}

void test_request_explode_should_give_null_if_pipes_only()
{
    uint8_t data[] = "||||||||||||||\n";
    uint8_t records = 0;

    TEST_ASSERT_NULL(request_explode(data, &records));
    TEST_ASSERT_EQUAL_UINT8(0, records);
}

void test_request_explode_should_give_null_if_equal_signs_only()
{
    uint8_t data[] = "==============\n";
    uint8_t records = 0;

    TEST_ASSERT_NULL(request_explode(data, &records));
    TEST_ASSERT_EQUAL_UINT8(0, records);
}

void test_request_explode_should_give_one_record()
{
    uint8_t data[] = "aaaaaaa=bbbbbb|\n";
    uint8_t records = 0;
    uint8_t ***args = request_explode(data, &records);

    TEST_ASSERT_EQUAL_STRING("aaaaaaa", args[0][0]);
    TEST_ASSERT_EQUAL_STRING("bbbbbb", args[0][1]);

    TEST_ASSERT_EQUAL_UINT8(1, records);
}

void test_request_explode_should_give_three_records()
{
    uint8_t data[] = "a1=b|c1=d|e1=f|\n";
    uint8_t records = 0;
    uint8_t ***args = request_explode(data, &records);

    TEST_ASSERT_EQUAL_STRING("a1", args[0][0]);
    TEST_ASSERT_EQUAL_STRING("b", args[0][1]);
    TEST_ASSERT_EQUAL_STRING("c1", args[1][0]);
    TEST_ASSERT_EQUAL_STRING("d", args[1][1]);
    TEST_ASSERT_EQUAL_STRING("e1", args[2][0]);
    TEST_ASSERT_EQUAL_STRING("f", args[2][1]);

    TEST_ASSERT_EQUAL_UINT8(3, records);
}

int main()
{
    HAL_Init();      // initialize the HAL library
    HAL_Delay(2000); // service delay

    UNITY_BEGIN();

    RUN_TEST(test_request_explode_should_give_null_if_white_spaces_only);
    RUN_TEST(test_request_explode_should_give_null_if_normal_text);
    RUN_TEST(test_request_explode_should_give_null_if_pipes_only);
    RUN_TEST(test_request_explode_should_give_null_if_equal_signs_only);
    RUN_TEST(test_request_explode_should_give_one_record);
    RUN_TEST(test_request_explode_should_give_three_records);

    UNITY_END();
}

#endif // UNIT_TEST