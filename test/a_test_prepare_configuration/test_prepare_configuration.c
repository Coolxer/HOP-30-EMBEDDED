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

void test_prepare_configuration_speed_should_give_9()
{
    uint8_t data[] = "idx=1|opt=ses|abc=x|\n";
    TEST_ASSERT_EQUAL_STRING("idx=1|res=err|cod=9|\n", connector_manage(connector_parse(data)));
}

void test_prepare_configuration_speed_should_give_10()
{
    uint8_t data[] = "idx=1|opt=ses|spp=a|\n";
    TEST_ASSERT_EQUAL_STRING("idx=1|res=err|cod=10|\n", connector_manage(connector_parse(data)));
}

void test_prepare_configuration_speed_should_give_11()
{
    uint8_t data[] = "idx=1|opt=ses|spp=x|abc=4|\n";
    TEST_ASSERT_EQUAL_STRING("idx=1|res=err|cod=11|\n", connector_manage(connector_parse(data)));
}

void test_prepare_configuration_speed_should_give_12()
{
    uint8_t data[] = "idx=1|opt=ses|spp=x|spd=a|\n";
    TEST_ASSERT_EQUAL_STRING("idx=1|res=err|cod=12|\n", connector_manage(connector_parse(data)));
}

void test_prepare_configuration_speed_should_give_finished()
{
    uint8_t data[] = "idx=1|opt=ses|spp=x|spd=50|\n";
    TEST_ASSERT_EQUAL_STRING("idx=1|res=fin|\n", connector_manage(connector_parse(data)));
}

int main()
{
    HAL_Init();      // initialize the HAL library
    HAL_Delay(2000); // service delay

    UNITY_BEGIN();

    // prepare settings spd
    RUN_TEST(test_prepare_configuration_speed_should_give_9);
    RUN_TEST(test_prepare_configuration_speed_should_give_10);
    RUN_TEST(test_prepare_configuration_speed_should_give_11);
    RUN_TEST(test_prepare_configuration_speed_should_give_12);
    RUN_TEST(test_prepare_configuration_speed_should_give_finished);

    UNITY_END();
}

#endif // UNIT_TEST