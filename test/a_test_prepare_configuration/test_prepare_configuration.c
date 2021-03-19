#ifdef UNIT_TEST

#include <unity.h> // includes unit testing
#include "command/cmd_builder.h"
#include "connector.h"
#include "device/device_manager.h"

void setUp() // default setup function
{
    cmd_builder_init();
    device_manager_init();
}

void tearDown(); // default release function

void test_prepare_configuration_speed_should_give_no_stepper_key_error()
{
    uint8_t data[] = "idx=1|opt=ses|abc=x|\n";
    TEST_ASSERT_EQUAL_STRING("idx=1|res=err|cod=10|\n", connector_manage(connector_parse(data)));
}

void test_prepare_configuration_speed_should_give_invalid_stepper_value_eror()
{
    uint8_t data[] = "idx=1|opt=ses|spp=a|\n";
    TEST_ASSERT_EQUAL_STRING("idx=1|res=err|cod=11|\n", connector_manage(connector_parse(data)));
}

void test_prepare_configuration_speed_should_give_no_speed_key_error()
{
    uint8_t data[] = "idx=1|opt=ses|spp=x|abc=4|acc=1|\n";
    TEST_ASSERT_EQUAL_STRING("idx=1|res=err|cod=14|\n", connector_manage(connector_parse(data)));
}

void test_prepare_configuration_speed_should_give_invalid_stepper_value_error()
{
    uint8_t data[] = "idx=1|opt=ses|spp=x|spd=a|acc=1|\n";
    TEST_ASSERT_EQUAL_STRING("idx=1|res=err|cod=15|\n", connector_manage(connector_parse(data)));
}

void test_prepare_configuration_acceleration_should_give_no_acceleration_key_error()
{
    uint8_t data[] = "idx=1|opt=ses|spp=x|spd=4|axc=8\n";
    TEST_ASSERT_EQUAL_STRING("idx=1|res=err|cod=14|\n", connector_manage(connector_parse(data)));
}

void test_prepare_configuration_acceleration_should_give_invalid_acceleration_value_error()
{
    uint8_t data[] = "idx=1|opt=ses|spp=x|spd=a|acc=a\n";
    TEST_ASSERT_EQUAL_STRING("idx=1|res=err|cod=15|\n", connector_manage(connector_parse(data)));
}

void test_prepare_configuration_speed_acceleration_should_give_finished()
{
    uint8_t data[] = "idx=1|opt=ses|spp=x|spd=50|acc=1|\n";
    TEST_ASSERT_EQUAL_STRING("idx=1|res=fin|\n", connector_manage(connector_parse(data)));
}

int main()
{
    HAL_Init();      // initialize the HAL library
    HAL_Delay(2000); // service delay

    UNITY_BEGIN();

    // prepare settings spd
    RUN_TEST(test_prepare_configuration_speed_should_give_no_stepper_key_error);
    RUN_TEST(test_prepare_configuration_speed_should_give_invalid_stepper_value_eror);
    RUN_TEST(test_prepare_configuration_speed_should_give_no_speed_key_error);
    RUN_TEST(test_prepare_configuration_speed_should_give_invalid_speed_value_error);
    RUN_TEST(test_prepare_configuration_speed_should_give_no_acceleration_key_error);
    RUN_TEST(test_prepare_configuration_speed_should_give_invalid_acceleration_value_error);
    RUN_TEST(test_prepare_configuration_speed_acceleration_should_give_finished);

    UNITY_END();
}

#endif // UNIT_TEST