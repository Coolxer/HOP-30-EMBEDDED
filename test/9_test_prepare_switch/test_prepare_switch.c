#ifdef UNIT_TEST

#include <unity.h> // includes unit testing
#include "command/cmd_builder.h"
#include "connector.h"
#include "device_manager.h"

void setUp() // default setup function
{
    cmd_builder_init();
    device_manager_init();
}

void tearDown(); // default release function

void test_prepare_switch_should_give_8()
{
    uint8_t data[] = "idx=1|opt=sth|abc=x|\n";
    TEST_ASSERT_EQUAL_STRING("idx=1|res=err|cod=8|\n", connector_manage(connector_parse(data)));
}

void test_prepare_switch_should_give_9()
{
    uint8_t data[] = "idx=1|opt=sth|spp=a|\n";
    TEST_ASSERT_EQUAL_STRING("idx=1|res=err|cod=9|\n", connector_manage(connector_parse(data)));
}

void test_prepare_switch_should_give_16()
{
    uint8_t data[] = "idx=1|opt=sth|spp=x|abc=4|\n";
    TEST_ASSERT_EQUAL_STRING("idx=1|res=err|cod=16|\n", connector_manage(connector_parse(data)));
}

void test_prepare_switch_should_give_17()
{
    uint8_t data[] = "idx=1|opt=sth|spp=x|stt=4|\n";
    TEST_ASSERT_EQUAL_STRING("idx=1|res=err|cod=17|\n", connector_manage(connector_parse(data)));
}

void test_prepare_switch_should_give_18()
{
    Stepper *stepper = (Stepper *)device_manager_getStepper((uint8_t *)"x");
    stepper->state = HOMING;

    uint8_t data[] = "idx=1|opt=sth|spp=x|stt=1|\n";
    TEST_ASSERT_EQUAL_STRING("idx=1|res=err|cod=18|\n", connector_manage(connector_parse(data)));
}

void test_prepare_switch_should_give_finished()
{
    Stepper *stepper = (Stepper *)device_manager_getStepper((uint8_t *)"x");
    stepper->state = ON;

    uint8_t data[] = "idx=1|opt=sth|spp=x|stt=1|\n";
    TEST_ASSERT_EQUAL_STRING("idx=1|res=fin|\n", connector_manage(connector_parse(data)));
}

int main()
{
    HAL_Init();      // initialize the HAL library
    HAL_Delay(2000); // service delay

    UNITY_BEGIN();

    RUN_TEST(test_prepare_switch_should_give_8);
    RUN_TEST(test_prepare_switch_should_give_9);
    RUN_TEST(test_prepare_switch_should_give_16);
    RUN_TEST(test_prepare_switch_should_give_17);
    RUN_TEST(test_prepare_switch_should_give_18);
    RUN_TEST(test_prepare_switch_should_give_finished);

    UNITY_END();
}

#endif // UNIT_TEST