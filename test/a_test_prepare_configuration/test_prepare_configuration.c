#ifdef UNIT_TEST

#include <unity.h> // includes unit testing
#include "command/cmd_builder.h"
#include "connector.h"

#include "device/device_manager.h"
#include "device/stepper/partial/stepper_helper.h"

void setUp() // default setup function
{
    cmd_builder_init();
    device_manager_init();
}

void tearDown(); // default release function

void test_prepare_configuration_should_give_no_stepper_key_error()
{
    uint8_t data[] = "idx=1|opt=cfg|abc=x|\n";
    TEST_ASSERT_EQUAL_STRING("idx=1|res=err|cod=10|\n", connector_manage(connector_parse(data)));
}

void test_prepare_configuration_should_give_invalid_stepper_value_eror()
{
    uint8_t data[] = "idx=1|opt=cfg|spp=a|\n";
    TEST_ASSERT_EQUAL_STRING("idx=1|res=err|cod=11|\n", connector_manage(connector_parse(data)));

    uint8_t data2[] = "idx=1|opt=cfg|spp=2|\n";
    TEST_ASSERT_EQUAL_STRING("idx=1|res=err|cod=11|\n", connector_manage(connector_parse(data2)));
}

void test_prepare_configuration_should_give_no_speed_key_error()
{
    uint8_t data[] = "idx=1|opt=cfg|spp=x|abc=4|acc=1|\n";
    TEST_ASSERT_EQUAL_STRING("idx=1|res=err|cod=12|\n", connector_manage(connector_parse(data)));
}

void test_prepare_configuration_should_give_invalid_speed_value_error()
{
    uint8_t data[] = "idx=1|opt=cfg|spp=x|spd=a|acc=1|\n";
    TEST_ASSERT_EQUAL_STRING("idx=1|res=err|cod=13|\n", connector_manage(connector_parse(data)));

    uint8_t data2[] = "idx=1|opt=cfg|spp=x|spd=0|acc=1|\n";
    TEST_ASSERT_EQUAL_STRING("idx=1|res=err|cod=13|\n", connector_manage(connector_parse(data2)));
}

void test_prepare_configuration_should_give_no_acceleration_key_error()
{
    uint8_t data[] = "idx=1|opt=cfg|spp=x|spd=4|axc=8|\n";
    TEST_ASSERT_EQUAL_STRING("idx=1|res=err|cod=14|\n", connector_manage(connector_parse(data)));
}

void test_prepare_configuration_should_give_invalid_acceleration_value_error()
{
    uint8_t data[] = "idx=1|opt=cfg|spp=x|spd=12|acc=a|\n";
    TEST_ASSERT_EQUAL_STRING("idx=1|res=err|cod=15|\n", connector_manage(connector_parse(data)));

    uint8_t data2[] = "idx=1|opt=cfg|spp=x|spd=12|acc=0|\n";
    TEST_ASSERT_EQUAL_STRING("idx=1|res=err|cod=15|\n", connector_manage(connector_parse(data2)));
}

void test_prepare_configuration_should_give_operation_not_allowed_value_error()
{
    Stepper *stepper = (Stepper *)device_manager_getStepper((uint8_t *)"x");
    stepper_setState(stepper, MOVING);

    uint8_t data[] = "idx=1|opt=cfg|spp=x|spd=12|acc=non|\n";
    TEST_ASSERT_EQUAL_STRING("idx=1|res=err|cod=22|\n", connector_manage(connector_parse(data)));

    stepper_setState(stepper, PAUSED);

    uint8_t data2[] = "idx=1|opt=cfg|spp=x|spd=12|acc=5|\n";
    TEST_ASSERT_EQUAL_STRING("idx=1|res=err|cod=22|\n", connector_manage(connector_parse(data2)));
}

void test_prepare_configuration_should_give_finished()
{
    uint8_t data[] = "idx=1|opt=cfg|spp=x|spd=50|acc=1|\n";
    TEST_ASSERT_EQUAL_STRING("idx=1|res=fin|\n", connector_manage(connector_parse(data)));

    uint8_t data2[] = "idx=1|opt=cfg|spp=x|spd=50|acc=non|\n";
    TEST_ASSERT_EQUAL_STRING("idx=1|res=fin|\n", connector_manage(connector_parse(data2)));
}

int main()
{
    HAL_Init();      // initialize the HAL library
    HAL_Delay(2000); // service delay

    UNITY_BEGIN();

    RUN_TEST(test_prepare_configuration_should_give_no_stepper_key_error);
    RUN_TEST(test_prepare_configuration_should_give_invalid_stepper_value_eror);

    RUN_TEST(test_prepare_configuration_should_give_no_speed_key_error);
    RUN_TEST(test_prepare_configuration_should_give_invalid_speed_value_error);

    RUN_TEST(test_prepare_configuration_should_give_no_acceleration_key_error);
    RUN_TEST(test_prepare_configuration_should_give_invalid_acceleration_value_error);
    RUN_TEST(test_prepare_configuration_should_give_operation_not_allowed_value_error);

    RUN_TEST(test_prepare_configuration_should_give_finished);

    UNITY_END();
}

#endif // UNIT_TEST