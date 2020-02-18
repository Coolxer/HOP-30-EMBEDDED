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
    TEST_ASSERT_EQUAL_STRING("_ERROR_no_spp_key", connector_manage(connector_parse(data)));
}

void test_prepare_move_should_give_invalid_spp_value_error()
{
    uint8_t data[] = "opt=mov|spp=a|\n";
    TEST_ASSERT_EQUAL_STRING("_ERROR_invalid_spp_value", connector_manage(connector_parse(data)));
}

void test_prepare_move_should_give_no_stp_key_error()
{
    uint8_t data[] = "opt=mov|spp=x|abc=4|\n";
    TEST_ASSERT_EQUAL_STRING("_ERROR_no_stp_key", connector_manage(connector_parse(data)));
}

void test_prepare_move_should_give_move_by_0_steps_error()
{
    uint8_t data[] = "opt=mov|spp=x|stp=0|\n";
    TEST_ASSERT_EQUAL_STRING("_ERROR_move_by_0_steps", connector_manage(connector_parse(data)));
}

void test_prepare_move_should_give_operation_not_allowed_error()
{
    Stepper *stepper = (Stepper*)device_manager_getStepper((uint8_t*)"x");
    stepper->state = HOMING;

    uint8_t data[] = "opt=mov|spp=x|stp=89|\n";
    TEST_ASSERT_EQUAL_STRING("_ERROR_operation_not_allowed", connector_manage(connector_parse(data)));
}

void test_prepare_move_should_give_valid_command()
{
    uint8_t data[] = "opt=mov|spp=x|stp=89|\n";
    TEST_ASSERT_EQUAL_STRING("_VALID_COMMAND", connector_manage(connector_parse(data)));
}

int main()
{
    HAL_Init();         // initialize the HAL library
    HAL_Delay(2000);    // service delay

    UNITY_BEGIN();

    RUN_TEST(test_prepare_move_should_give_no_spp_key_error);
    RUN_TEST(test_prepare_move_should_give_invalid_spp_value_error);
    RUN_TEST(test_prepare_move_should_give_move_by_0_steps_error);
    RUN_TEST(test_prepare_move_should_give_operation_not_allowed_error);
    RUN_TEST(test_prepare_move_should_give_valid_command);

    UNITY_END();
}

#endif // UNIT_TEST