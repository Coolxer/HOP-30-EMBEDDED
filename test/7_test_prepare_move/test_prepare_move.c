#ifdef UNIT_TEST

#include <unity.h> // includes unit testing library
#include "connector.h"
#include "device_manager.h"

void setUp()// default setup function
{
    device_manager_init();
}

void tearDown(); // default release function

void test_prepare_move_should_give_no_spp_key_error()
{
    uint8_t data[] = "opt=mov|abc=x|\n";
    uint8_t ***args = connector_parse(data);

    uint8_t *result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_ERROR_no_spp_key", result);
}

void test_prepare_move_should_give_invalid_spp_value_error()
{
    uint8_t data[] = "opt=mov|spp=a|\n";
    uint8_t ***args = connector_parse(data);

    uint8_t *result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_ERROR_invalid_spp_value", result);
}

void test_prepare_move_should_give_no_stp_key_error()
{
    uint8_t data[] = "opt=mov|spp=x|abc=4|\n";
    uint8_t ***args = connector_parse(data);

    uint8_t *result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_ERROR_no_stp_key", result);
}

void test_prepare_move_should_give_move_by_0_steps_error()
{
    uint8_t data[] = "opt=mov|spp=x|stp=0|\n";
    uint8_t ***args = connector_parse(data);

    uint8_t *result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_ERROR_move_by_0_steps", result);
}

void test_prepare_move_should_give_valid_command_if_negative_steps()
{
    uint8_t data[] = "opt=mov|spp=x|stp=-25|\n";
    uint8_t ***args = connector_parse(data);

    uint8_t *result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_VALID_COMMAND", result);
}

void test_prepare_move_should_give_valid_command_if_positive_steps()
{
    uint8_t data[] = "opt=mov|spp=x|stp=89|\n";
    uint8_t ***args = connector_parse(data);

    uint8_t *result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_VALID_COMMAND", result);
}

int main()
{
    HAL_Init();         // initialize the HAL library
    HAL_Delay(2000);    // service delay

    UNITY_BEGIN();

    RUN_TEST(test_prepare_move_should_give_no_spp_key_error);
    RUN_TEST(test_prepare_move_should_give_invalid_spp_value_error);
    RUN_TEST(test_prepare_move_should_give_move_by_0_steps_error);
    RUN_TEST(test_prepare_move_should_give_valid_command_if_negative_steps);
    RUN_TEST(test_prepare_move_should_give_valid_command_if_positive_steps);

    UNITY_END();
}

#endif // UNIT_TEST