#ifdef UNIT_TEST

#include <unity.h> // includes unit testing library
#include "connector.h"
#include "device_manager.h"

void setUp()// default setup function
{
    device_manager_init();
}

void tearDown(); // default release function

void test_prepare_switch_should_give_no_spp_key_error()
{
    uint8_t data[] = "opt=sth|abc=x|\n";
    uint8_t ***args = connector_parse(data);

    uint8_t *result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_ERROR_no_spp_key", result);
}

/************************* switch all ********************************/

void test_prepare_switch_all_should_give_no_stt_key_error()
{
    uint8_t data[] = "opt=sth|spp=all|abc=1|\n";
    uint8_t ***args = connector_parse(data);

    uint8_t *result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_ERROR_no_stt_key", result);
}

void test_prepare_switch_all_should_give_invalid_stt_value_error()
{
    uint8_t data[] = "opt=sth|spp=all|stt=a|\n";
    uint8_t ***args = connector_parse(data);

    uint8_t *result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_ERROR_invalid_stt_value", result);
}

void test_prepare_switch_all_should_give_success()
{
    uint8_t data[] = "opt=sth|spp=all|stt=1|\n";
    uint8_t ***args = connector_parse(data);

    uint8_t *result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_SUCCESS", result);
}

/*********************** switch individual ****************************/

void test_prepare_switch_should_give_invalid_spp_value_error()
{
    uint8_t data[] = "opt=sth|spp=a|\n";
    uint8_t ***args = connector_parse(data);

    uint8_t *result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_ERROR_invalid_spp_value", result);
}

void test_prepare_switch_should_give_no_stt_key_error()
{
    uint8_t data[] = "opt=sth|spp=x|abc=4|\n";
    uint8_t ***args = connector_parse(data);

    uint8_t *result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_ERROR_no_stt_key", result);
}

void test_prepare_switch_should_give_invalid_stt_value()
{
    uint8_t data[] = "opt=sth|spp=x|stt=4|\n";
    uint8_t ***args = connector_parse(data);

    uint8_t *result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_ERROR_invalid_stt_value", result);
}

void test_prepare_switch_should_give_success()
{
    uint8_t data[] = "opt=sth|spp=x|stt=1|\n";
    uint8_t ***args = connector_parse(data);

    uint8_t *result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_SUCCESS", result);
}

int main()
{
    HAL_Init();         // initialize the HAL library
    HAL_Delay(2000);    // service delay

    UNITY_BEGIN();

    RUN_TEST(test_prepare_switch_should_give_no_spp_key_error);

    // switch all
    RUN_TEST(test_prepare_switch_all_should_give_no_stt_key_error);
    RUN_TEST(test_prepare_switch_all_should_give_invalid_stt_value_error);
    RUN_TEST(test_prepare_switch_all_should_give_success);

    // switch individual
    RUN_TEST(test_prepare_switch_should_give_invalid_spp_value_error);
    RUN_TEST(test_prepare_switch_should_give_no_stt_key_error);
    RUN_TEST(test_prepare_switch_should_give_invalid_stt_value);
    RUN_TEST(test_prepare_switch_should_give_success);

    UNITY_END();
}

#endif // UNIT_TEST