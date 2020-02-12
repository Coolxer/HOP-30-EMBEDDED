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
    TEST_ASSERT_EQUAL_STRING("_ERROR_no_spp_key", connector_manage(connector_parse(data)));
}

/************************* switch all ********************************/

void test_prepare_switch_all_should_give_no_stt_key_error()
{
    uint8_t data[] = "opt=sth|spp=all|abc=1|\n";
    TEST_ASSERT_EQUAL_STRING("_ERROR_no_stt_key", connector_manage(connector_parse(data)));
}

void test_prepare_switch_all_should_give_invalid_stt_value_error()
{
    uint8_t data[] = "opt=sth|spp=all|stt=a|\n";
    TEST_ASSERT_EQUAL_STRING("_ERROR_invalid_stt_value", connector_manage(connector_parse(data)));
}

void test_prepare_switch_all_should_give_success_if_0()
{
    uint8_t data[] = "opt=sth|spp=all|stt=0|\n";
    TEST_ASSERT_EQUAL_STRING("_SUCCESS", connector_manage(connector_parse(data)));
}

void test_prepare_switch_all_should_give_success_if_1()
{
    uint8_t data[] = "opt=sth|spp=all|stt=1|\n";
    TEST_ASSERT_EQUAL_STRING("_SUCCESS", connector_manage(connector_parse(data)));
}

/*********************** switch individual ****************************/

void test_prepare_switch_should_give_invalid_spp_value_error()
{
    uint8_t data[] = "opt=sth|spp=a|\n";
    TEST_ASSERT_EQUAL_STRING("_ERROR_invalid_spp_value", connector_manage(connector_parse(data)));
}

void test_prepare_switch_should_give_no_stt_key_error()
{
    uint8_t data[] = "opt=sth|spp=x|abc=4|\n";
    TEST_ASSERT_EQUAL_STRING("_ERROR_no_stt_key", connector_manage(connector_parse(data)));
}

void test_prepare_switch_should_give_invalid_stt_value()
{
    uint8_t data[] = "opt=sth|spp=x|stt=4|\n";
    TEST_ASSERT_EQUAL_STRING("_ERROR_invalid_stt_value", connector_manage(connector_parse(data)));
}

void test_prepare_switch_should_give_operation_not_allowed_error()
{
    Stepper *stepper = (Stepper*)device_manager_getStepper((uint8_t*)"x");
    stepper->state = HOMING;

    uint8_t data[] = "opt=sth|spp=x|stt=1|\n";
    TEST_ASSERT_EQUAL_STRING("_ERROR_operation_not_allowed", connector_manage(connector_parse(data)));
}

void test_prepare_switch_should_give_success()
{
    Stepper *stepper = (Stepper*)device_manager_getStepper((uint8_t*)"x");
    stepper->state = ON;

    uint8_t data[] = "opt=sth|spp=x|stt=1|\n";
    TEST_ASSERT_EQUAL_STRING("_SUCCESS", connector_manage(connector_parse(data)));
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
    RUN_TEST(test_prepare_switch_all_should_give_success_if_0);
    RUN_TEST(test_prepare_switch_all_should_give_success_if_1);

    // switch individual
    RUN_TEST(test_prepare_switch_should_give_invalid_spp_value_error);
    RUN_TEST(test_prepare_switch_should_give_no_stt_key_error);
    RUN_TEST(test_prepare_switch_should_give_invalid_stt_value);
    RUN_TEST(test_prepare_switch_should_give_operation_not_allowed_error);
    RUN_TEST(test_prepare_switch_should_give_success);

    UNITY_END();
}

#endif // UNIT_TEST