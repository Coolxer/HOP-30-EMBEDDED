#ifdef UNIT_TEST

#include <unity.h> // includes unit testing library
#include "connector.h"
#include "device_manager.h"

void setUp()// default setup function
{
    device_manager_init();
}

void tearDown(); // default release function

/*********************** prepare_settings speed ***************************************/

void test_prepare_settings_speed_should_give_no_spp_key_error()
{
    uint8_t data[] = "opt=ses|abc=x|\n";
    TEST_ASSERT_EQUAL_STRING("_ERROR_no_spp_key", connector_manage(connector_parse(data)));
}

void test_prepare_settings_speed_should_give_invalid_spp_value_error()
{
    uint8_t data[] = "opt=ses|spp=a|\n";
    TEST_ASSERT_EQUAL_STRING("_ERROR_invalid_spp_value", connector_manage(connector_parse(data)));
}

void test_prepare_settings_speed_should_give_no_spd_key_error()
{
    uint8_t data[] = "opt=ses|spp=x|abc=4|\n";
    TEST_ASSERT_EQUAL_STRING("_ERROR_no_spd_key", connector_manage(connector_parse(data)));
}

void test_prepare_settings_speed_should_give_invalid_spd_value()
{
    uint8_t data[] = "opt=ses|spp=x|spd=a|\n";
    TEST_ASSERT_EQUAL_STRING("_ERROR_invalid_spd_value", connector_manage(connector_parse(data)));
}

void test_prepare_settings_speed_should_give_success()
{
    uint8_t data[] = "opt=ses|spp=x|spd=50|\n";
    TEST_ASSERT_EQUAL_STRING("_SUCCESS", connector_manage(connector_parse(data)));
}

/*********************** prepare_settings microstepping ***************************************/

void test_prepare_settings_microstepping_should_give_no_spp_key_error()
{
    uint8_t data[] = "opt=sem|abc=x|\n";
    TEST_ASSERT_EQUAL_STRING("_ERROR_no_spp_key", connector_manage(connector_parse(data)));
}

void test_prepare_settings_microstepping_should_give_invalid_spp_value_error()
{
    uint8_t data[] = "opt=sem|spp=a|\n";
    TEST_ASSERT_EQUAL_STRING("_ERROR_invalid_spp_value", connector_manage(connector_parse(data)));
}

void test_prepare_settings_microstepping_should_give_no_msp_key_error()
{
    uint8_t data[] = "opt=sem|spp=x|abc=4|\n";
    TEST_ASSERT_EQUAL_STRING("_ERROR_no_msp_key", connector_manage(connector_parse(data)));
}

void test_prepare_settings_microstepping_should_give_invalid_msp_value()
{
    uint8_t data[] = "opt=sem|spp=x|msp=a|\n";
    TEST_ASSERT_EQUAL_STRING("_ERROR_invalid_msp_value", connector_manage(connector_parse(data)));
}

void test_prepare_settings_microstepping_should_give_success()
{
    uint8_t data[] = "opt=sem|spp=x|msp=101|\n";
    TEST_ASSERT_EQUAL_STRING("_SUCCESS", connector_manage(connector_parse(data)));
}

int main()
{
    HAL_Init();         // initialize the HAL library
    HAL_Delay(2000);    // service delay

    UNITY_BEGIN();

    // prepare settings spd
    RUN_TEST(test_prepare_settings_speed_should_give_no_spp_key_error);
    RUN_TEST(test_prepare_settings_speed_should_give_invalid_spp_value_error);
    RUN_TEST(test_prepare_settings_speed_should_give_no_spd_key_error);
    RUN_TEST(test_prepare_settings_speed_should_give_invalid_spd_value);
    RUN_TEST(test_prepare_settings_speed_should_give_success);

    // prepare settings msp
    RUN_TEST(test_prepare_settings_microstepping_should_give_no_spp_key_error);
    RUN_TEST(test_prepare_settings_microstepping_should_give_invalid_spp_value_error);
    RUN_TEST(test_prepare_settings_microstepping_should_give_no_msp_key_error);
    RUN_TEST(test_prepare_settings_microstepping_should_give_invalid_msp_value);
    RUN_TEST(test_prepare_settings_microstepping_should_give_success);

    UNITY_END();
}

#endif // UNIT_TEST