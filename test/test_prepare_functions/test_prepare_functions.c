//#ifdef UNIT_TEST

#include <unity.h> // includes unit testing library
#include <string.h>
#include "prepare_functions.h"

#include "stm32f4xx_hal.h"

#include "device_manager.h"

uint8_t ***args;
uint8_t *result;

void setUp()// default setup function
{
    device_manager_init();

    args = NULL;
    result = "";
}

void tearDown(); // default release function

/*********************** prepare_settings sth ***************************************/

void test_prepare_settings_switch_should_give_no_spp_key_error()
{
    uint8_t data[] = "opt=sth|abc=x|\n";
    args = connector_parse(data);

    result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_ERROR_no_spp_key", result);
}

void test_prepare_settings_switch_should_give_invalid_stepper_name_error()
{
    uint8_t data[] = "opt=sth|spp=a|\n";
    args = connector_parse(data);

    result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_ERROR_invalid_stepper_name", result);
}

void test_prepare_settings_switch_should_give_unknown_key_error()
{
    uint8_t data[] = "opt=sth|spp=x|abc=4\n";
    args = connector_parse(data);

    result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_ERROR_unknown_key", result);
}

void test_prepare_settings_switch_should_give_invalid_stt_value()
{
    uint8_t data[] = "opt=sth|spp=x|stt=4\n";
    args = connector_parse(data);

    result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_ERROR_invalid_stt_key", result);
}

int main()
{
    HAL_Init();         // initialize the HAL library
    HAL_Delay(2000);    // service delay

    UNITY_BEGIN();
    
    RUN_TEST(test_prepare_settings_switch_should_give_no_spp_key_error);
    RUN_TEST(test_prepare_settings_switch_should_give_invalid_stepper_name_error);
    RUN_TEST(test_prepare_settings_switch_should_give_unknown_key_error);
    RUN_TEST(test_prepare_settings_switch_should_give_invalid_stt_value);

    UNITY_END();
}

//#endif // UNIT_TEST