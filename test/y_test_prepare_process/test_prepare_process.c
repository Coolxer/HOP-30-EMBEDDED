#ifdef UNIT_TEST

#include <unity.h> // includes unit testing library
#include "connector.h"
#include "device_manager.h"

void setUp()// default setup function
{
    device_manager_init();
}

void tearDown(); // default release function

void test_prepare_process_should_give_no_dir_key_error()
{
    uint8_t data[] = "opt=pro|spp=x|\n";
    TEST_ASSERT_EQUAL_STRING("_ERROR_no_dir_key", connector_manage(connector_parse(data)));
}

void test_prepare_process_should_give_invalid_dir_value_error()
{
    uint8_t data[] = "opt=pro|dir=x|\n";
    TEST_ASSERT_EQUAL_STRING("_ERROR_invalid_dir_value", connector_manage(connector_parse(data)));
}

void test_prepare_process_should_give_valid_command()
{
    uint8_t data[] = "opt=pro|dir=1|\n";
    TEST_ASSERT_EQUAL_STRING("_VALID_COMMAND", connector_manage(connector_parse(data)));
}

int main()
{
    HAL_Init();         // initialize the HAL library
    HAL_Delay(2000);    // service delay

    UNITY_BEGIN();

    RUN_TEST(test_prepare_process_should_give_no_dir_key_error);
    RUN_TEST(test_prepare_process_should_give_invalid_dir_value_error);
    RUN_TEST(test_prepare_process_should_give_valid_command);

    UNITY_END();
}

#endif // UNIT_TEST