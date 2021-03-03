#ifdef UNIT_TEST

#include <unity.h> // includes unit testing library
#include "command/cmd_builder.h"
#include "connector.h"

#include "device/device_manager.h"
#include "device/stepper/partial/stepper_state_manager.h"

void setUp() // default setup function
{
    cmd_builder_init();
    device_manager_init();
}

void tearDown(); // default release function

void test_prepare_home_should_give_no_stepper_key_error()
{
    uint8_t data[] = "idx=1|opt=hom|abc=x|\n";
    TEST_ASSERT_EQUAL_STRING("idx=1|res=err|cod=10|\n", connector_manage(connector_parse(data)));
}

void test_prepare_home_should_give_invalid_stepper_value_error()
{
    uint8_t data[] = "idx=1|opt=hom|spp=a|\n";
    TEST_ASSERT_EQUAL_STRING("idx=1|res=err|cod=11|\n", connector_manage(connector_parse(data)));
}

void test_prepare_home_should_give_operation_not_allowed_error()
{
    Stepper *stepper = (Stepper *)device_manager_getStepper((uint8_t *)"x");
    stepper_setState(stepper, HOMING);

    stepper_setHomeStep(stepper, FAST);
    stepper_updateLastHomeStep(stepper);

    uint8_t data[] = "idx=1|opt=hom|spp=x|\n";
    TEST_ASSERT_EQUAL_STRING("idx=1|res=err|cod=20|\n", connector_manage(connector_parse(data)));
}

void test_prepare_home_should_give_passed()
{
    Stepper *stepper = (Stepper *)device_manager_getStepper((uint8_t *)"x");
    stepper_setState(stepper, ON);

    stepper_setHomeStep(stepper, PRECISE);
    stepper_updateLastHomeStep(stepper);

    uint8_t data[] = "idx=1|opt=hom|spp=x|\n";
    TEST_ASSERT_EQUAL_STRING("idx=1|res=pas|\n", connector_manage(connector_parse(data)));
}

int main()
{
    HAL_Init();      // initialize the HAL library
    HAL_Delay(2000); // service delay

    UNITY_BEGIN();

    RUN_TEST(test_prepare_home_should_give_no_stepper_key_error);
    RUN_TEST(test_prepare_home_should_give_invalid_stepper_value_error);
    RUN_TEST(test_prepare_home_should_give_operation_not_allowed_error);
    RUN_TEST(test_prepare_home_should_give_passed);

    UNITY_END();
}

#endif // UNIT_TEST