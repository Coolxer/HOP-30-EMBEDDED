//#ifdef UNIT_TEST

#include <unity.h> // includes unit testing library
#include <string.h>
#include "stm32f4xx_hal.h"

#include "connector.h"
#include "device_manager.h"

void setUp()// default setup function
{
    device_manager_init();
}

void tearDown(); // default release function

/*********************** prepare_settings sth ***************************************/

void test_prepare_settings_switch_should_give_no_spp_key_error()
{
    uint8_t data[] = "opt=sth|abc=x|\n";
    uint8_t ***args = connector_parse(data);

    uint8_t *result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_ERROR_no_spp_key", result);
}

void test_prepare_settings_switch_should_give_invalid_stepper_name_error()
{
    uint8_t data[] = "opt=sth|spp=a|\n";
    uint8_t ***args = connector_parse(data);

    uint8_t *result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_ERROR_invalid_stepper_name", result);
}

void test_prepare_settings_switch_should_give_unknown_key_error()
{
    uint8_t data[] = "opt=sth|spp=x|abc=4|\n";
    uint8_t ***args = connector_parse(data);

    uint8_t *result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_ERROR_unknown_key", result);
}

void test_prepare_settings_switch_should_give_invalid_stt_value()
{
    uint8_t data[] = "opt=sth|spp=x|stt=4|\n";
    uint8_t ***args = connector_parse(data);

    uint8_t *result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_ERROR_invalid_stt_value", result);
}

void test_prepare_settings_switch_should_give_success()
{
    uint8_t data[] = "opt=sth|spp=x|stt=1|\n";
    uint8_t ***args = connector_parse(data);

    uint8_t *result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_SUCCESS", result);
}

/*********************** prepare_settings speed ***************************************/

void test_prepare_settings_speed_should_give_no_spp_key_error()
{
    uint8_t data[] = "opt=spd|abc=x|\n";
    uint8_t ***args = connector_parse(data);

    uint8_t *result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_ERROR_no_spp_key", result);
}

void test_prepare_settings_spd_should_give_invalid_stepper_name_error()
{
    uint8_t data[] = "opt=spd|spp=a|\n";
    uint8_t ***args = connector_parse(data);

    uint8_t *result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_ERROR_invalid_stepper_name", result);
}

void test_prepare_settings_speed_should_give_unknown_key_error()
{
    uint8_t data[] = "opt=spd|spp=x|abc=4|\n";
    uint8_t ***args = connector_parse(data);

    uint8_t *result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_ERROR_unknown_key", result);
}

void test_prepare_settings_speed_should_give_invalid_spd_value()
{
    uint8_t data[] = "opt=spd|spp=x|spd=a|\n";
    uint8_t ***args = connector_parse(data);

    uint8_t *result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_ERROR_invalid_spd_value", result);
}

void test_prepare_settings_speed_should_give_invalid_spd_value_if_negative()
{
    uint8_t data[] = "opt=spd|spp=x|spd=-1|\n";
    uint8_t ***args = connector_parse(data);

    uint8_t *result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_ERROR_invalid_spd_value", result);
}

void test_prepare_settings_speed_should_give_invalid_spd_value_if_zero()
{
    uint8_t data[] = "opt=spd|spp=x|spd=0|\n";
    uint8_t ***args = connector_parse(data);

    uint8_t *result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_ERROR_invalid_spd_value", result);
}

void test_prepare_settings_speed_should_give_invalid_spd_value_if_over()
{
    uint8_t data[] = "opt=spd|spp=x|spd=101|\n";
    uint8_t ***args = connector_parse(data);

    uint8_t *result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_ERROR_invalid_spd_value", result);
}

void test_prepare_settings_speed_should_give_success()
{
    uint8_t data[] = "opt=spd|spp=x|spd=50|\n";
    uint8_t ***args = connector_parse(data);

    uint8_t *result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_SUCCESS", result);
}

/*********************** prepare_settings microstepping ***************************************/

void test_prepare_settings_microstepping_should_give_no_spp_key_error()
{
    uint8_t data[] = "opt=msp|abc=x|\n";
    uint8_t ***args = connector_parse(data);

    uint8_t *result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_ERROR_no_spp_key", result);
}

void test_prepare_settings_microstepping_should_give_invalid_stepper_name_error()
{
    uint8_t data[] = "opt=msp|spp=a|\n";
    uint8_t ***args = connector_parse(data);

    uint8_t *result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_ERROR_invalid_stepper_name", result);
}

void test_prepare_settings_microstepping_should_give_unknown_key_error()
{
    uint8_t data[] = "opt=msp|spp=x|abc=4|\n";
    uint8_t ***args = connector_parse(data);

    uint8_t *result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_ERROR_unknown_key", result);
}

void test_prepare_settings_microstepping_should_give_invalid_msp_value()
{
    uint8_t data[] = "opt=msp|spp=x|msp=a|\n";
    uint8_t ***args = connector_parse(data);

    uint8_t *result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_ERROR_invalid_msp_value", result);
}

void test_prepare_settings_microstepping_should_give_invalid_msp_value_if_random_numbers()
{
    uint8_t data[] = "opt=msp|spp=x|msp=406\n";
    uint8_t ***args = connector_parse(data);

    uint8_t *result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_ERROR_invalid_msp_value", result);
}

void test_prepare_settings_microstepping_should_give_invalid_msp_value_if_too_many_characters()
{
    uint8_t data[] = "opt=msp|spp=x|msp=01010101|\n";
    uint8_t ***args = connector_parse(data);

    uint8_t *result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_ERROR_invalid_msp_value", result);
}

void test_prepare_settings_microstepping_should_give_invalid_msp_value_if_mix()
{
    uint8_t data[] = "opt=msp|spp=x|msp=10a|\n";
    uint8_t ***args = connector_parse(data);

    uint8_t *result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_ERROR_invalid_msp_value", result);
}

void test_prepare_settings_microstepping_should_give_success()
{
    uint8_t data[] = "opt=msp|spp=x|msp=101|\n";
    uint8_t ***args = connector_parse(data);

    uint8_t *result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_SUCCESS", result);
}

/*********************** prepare_home  ***************************************/

void test_prepare_home_should_give_no_spp_key_error()
{
    uint8_t data[] = "opt=hom|abc=x|\n";
    uint8_t ***args = connector_parse(data);

    uint8_t *result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_ERROR_no_spp_key", result);
}

void test_prepare_home_should_give_invalid_stepper_name_error()
{
    uint8_t data[] = "opt=hom|spp=a|\n";
    uint8_t ***args = connector_parse(data);

    uint8_t *result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_ERROR_invalid_stepper_name", result);
}

void test_prepare_home_should_give_valid_command()
{
    uint8_t data[] = "opt=msp|spp=x|\n";
    uint8_t ***args = connector_parse(data);

    uint8_t *result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_VALID_COMMAND", result);
}

/*********************** prepare_move ***************************************/

void test_prepare_move_should_give_no_spp_key_error()
{
    uint8_t data[] = "opt=mov|abc=x|\n";
    uint8_t ***args = connector_parse(data);

    uint8_t *result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_ERROR_no_spp_key", result);
}

void test_prepare_move_should_give_invalid_stepper_name_error()
{
    uint8_t data[] = "opt=mov|spp=a|\n";
    uint8_t ***args = connector_parse(data);

    uint8_t *result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_ERROR_invalid_stepper_name", result);
}

void test_prepare_move_should_give_unknown_key_error()
{
    uint8_t data[] = "opt=mov|spp=x|abc=4|\n";
    uint8_t ***args = connector_parse(data);

    uint8_t *result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_ERROR_unknown_key", result);
}

void test_prepare_move_should_give_move_by_0_steps_error()
{
    uint8_t data[] = "opt=mov|spp=x|stp=0|\n";
    uint8_t ***args = connector_parse(data);

    uint8_t *result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_ERROR_move_by_0_steps", result);
}

void test_prepare_move_should_give_success_if_negative_steps()
{
    uint8_t data[] = "opt=mov|spp=x|stp=-25|\n";
    uint8_t ***args = connector_parse(data);

    uint8_t *result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_SUCCESS", result);
}

void test_prepare_move_should_give_success_if_positive_steps()
{
    uint8_t data[] = "opt=mov|spp=x|stp=89|\n";
    uint8_t ***args = connector_parse(data);

    uint8_t *result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_SUCCESS", result);
}

/*********************** prepare_process ***************************************/

void test_prepare_process_should_give_no_dir_key_error()
{
    uint8_t data[] = "opt=pro|spp=x|\n";
    uint8_t ***args = connector_parse(data);

    uint8_t *result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_ERROR_no_dir_key", result);
}

void test_prepare_process_should_give_invalid_dir_value_error()
{
    uint8_t data[] = "opt=pro|dir=x|\n";
    uint8_t ***args = connector_parse(data);

    uint8_t *result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_ERROR_invalid_dir_value", result);
}

int main()
{
    HAL_Init();         // initialize the HAL library
    HAL_Delay(2000);    // service delay

    UNITY_BEGIN();
    
    // prepare settings sth
    RUN_TEST(test_prepare_settings_switch_should_give_no_spp_key_error);
    RUN_TEST(test_prepare_settings_switch_should_give_invalid_stepper_name_error);
    RUN_TEST(test_prepare_settings_switch_should_give_unknown_key_error);
    RUN_TEST(test_prepare_settings_switch_should_give_invalid_stt_value);
    RUN_TEST(test_prepare_settings_switch_should_give_success);

    // prepare settings spd
    RUN_TEST(test_prepare_settings_speed_should_give_no_spp_key_error);
    RUN_TEST(test_prepare_settings_spd_should_give_invalid_stepper_name_error);
    RUN_TEST(test_prepare_settings_speed_should_give_unknown_key_error);
    RUN_TEST(test_prepare_settings_speed_should_give_invalid_spd_value);
    RUN_TEST(test_prepare_settings_speed_should_give_invalid_spd_value_if_negative);
    RUN_TEST(test_prepare_settings_speed_should_give_invalid_spd_value_if_zero);
    RUN_TEST(test_prepare_settings_speed_should_give_invalid_spd_value_if_over);
    RUN_TEST(test_prepare_settings_speed_should_give_success);

    // prepare settings msp
    RUN_TEST(test_prepare_settings_microstepping_should_give_no_spp_key_error);
    RUN_TEST(test_prepare_settings_microstepping_should_give_invalid_stepper_name_error);
    RUN_TEST(test_prepare_settings_microstepping_should_give_unknown_key_error);
    RUN_TEST(test_prepare_settings_microstepping_should_give_invalid_msp_value);
    RUN_TEST(test_prepare_settings_microstepping_should_give_invalid_msp_value_if_random_numbers);
    RUN_TEST(test_prepare_settings_microstepping_should_give_invalid_msp_value_if_too_many_characters);
    RUN_TEST(test_prepare_settings_microstepping_should_give_invalid_msp_value_if_mix);
    RUN_TEST(test_prepare_settings_microstepping_should_give_success);

    // prepare home
    RUN_TEST(test_prepare_home_should_give_no_spp_key_error);
    RUN_TEST(test_prepare_home_should_give_invalid_stepper_name_error);
    RUN_TEST(test_prepare_home_should_give_valid_command);

    // prepare move
    RUN_TEST(test_prepare_move_should_give_no_spp_key_error);
    RUN_TEST(test_prepare_move_should_give_invalid_stepper_name_error);
    RUN_TEST(test_prepare_move_should_give_move_by_0_steps_error);
    RUN_TEST(test_prepare_move_should_give_success_if_negative_steps);
    RUN_TEST(test_prepare_move_should_give_success_if_positive_steps);
    

    UNITY_END();
}

//#endif // UNIT_TEST