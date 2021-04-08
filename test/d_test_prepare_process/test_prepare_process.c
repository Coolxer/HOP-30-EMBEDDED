#ifdef UNIT_TEST

#include <unity.h> // includes unit testing library
#include "command/cmd_builder.h"
#include "connector.h"
#include "device/device_manager.h"

void setUp() // default setup function
{
    cmd_builder_init();
    device_manager_init();
}

void tearDown(); // default release function

void test_prepare_process_should_give_no_direction_key_error()
{
    uint8_t data[] = "idx=1|opt=pro|spp=x|\n";
    TEST_ASSERT_EQUAL_STRING("idx=1|res=err|cod=20|\n", connector_manage(connector_parse(data)));
}

void test_prepare_process_should_give_invalid_direction_value_error()
{
    uint8_t data[] = "idx=1|opt=pro|dir=x|\n";
    TEST_ASSERT_EQUAL_STRING("idx=1|res=err|cod=21|\n", connector_manage(connector_parse(data)));
}

void test_prepare_process_should_give_operation_not_allowed_error()
{
    Stepper *stepper = (Stepper *)device_manager_getStepper((uint8_t *)"x");
    stepper_setState(stepper, MOVING);

    uint8_t data[] = "idx=1|opt=pro|dir=1|\n";
    TEST_ASSERT_EQUAL_STRING("idx=1|res=err|cod=22|\n", connector_manage(connector_parse(data)));
}

void test_prepare_process_should_give_passed()
{
    uint8_t data[] = "idx=1|opt=pro|dir=1|\n";
    TEST_ASSERT_EQUAL_STRING("idx=1|res=pas|\n", connector_manage(connector_parse(data)));
}

int main()
{
    HAL_Init();      // initialize the HAL library
    HAL_Delay(2000); // service delay

    UNITY_BEGIN();

    RUN_TEST(test_prepare_process_should_give_no_direction_key_error);
    RUN_TEST(test_prepare_process_should_give_invalid_direction_value_error);
    RUN_TEST(test_prepare_process_should_give_operation_not_allowed_error);
    RUN_TEST(test_prepare_process_should_give_passed);

    UNITY_END();
}

#endif // UNIT_TEST