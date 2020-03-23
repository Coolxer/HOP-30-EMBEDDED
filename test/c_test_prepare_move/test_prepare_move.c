#ifdef UNIT_TEST

#include <unity.h> // includes unit testing library
#include "connector.h"
#include "device_manager.h"

void setUp()// default setup function
{
    cmd_builder_init();
    device_manager_init();
}

void tearDown(); // default release function

void test_prepare_move_should_give_8()
{
    uint8_t data[] = "idx=1|opt=mov|abc=x|\n";
    TEST_ASSERT_EQUAL_STRING("idx=1|res=err|cod=8|\n", connector_manage(connector_parse(data)));
}

void test_prepare_move_should_give_9()
{
    uint8_t data[] = "idx=1|opt=mov|spp=a|\n";
    TEST_ASSERT_EQUAL_STRING("idx=1|res=err|cod=9|\n", connector_manage(connector_parse(data)));
}

void test_prepare_move_should_give_19()
{
    uint8_t data[] = "idx=1|opt=mov|spp=x|abc=4|\n";
    TEST_ASSERT_EQUAL_STRING("idx=1|res=err|cod=19|\n", connector_manage(connector_parse(data)));
}

void test_prepare_move_should_give_20()
{
    uint8_t data[] = "idx=1|opt=mov|spp=x|stp=0|\n";
    TEST_ASSERT_EQUAL_STRING("idx=1|res=err|cod=20|\n", connector_manage(connector_parse(data)));
}

void test_prepare_move_should_give_18()
{
    Stepper *stepper = (Stepper*)device_manager_getStepper((uint8_t*)"x");
    stepper->state = HOMING;

    uint8_t data[] = "idx=1|opt=mov|spp=x|stp=89|\n";
    TEST_ASSERT_EQUAL_STRING("idx=1|res=err|cod=18|\n", connector_manage(connector_parse(data)));
}

void test_prepare_move_should_give_passed()
{
    uint8_t data[] = "idx=1|opt=mov|spp=x|stp=89|\n";
    TEST_ASSERT_EQUAL_STRING("idx=1|res=pas|\n", connector_manage(connector_parse(data)));
}

int main()
{
    HAL_Init();         // initialize the HAL library
    HAL_Delay(2000);    // service delay

    UNITY_BEGIN();

    RUN_TEST(test_prepare_move_should_give_8);
    RUN_TEST(test_prepare_move_should_give_9);
    RUN_TEST(test_prepare_move_should_give_19);
    RUN_TEST(test_prepare_move_should_give_20);
    RUN_TEST(test_prepare_move_should_give_18);

    RUN_TEST(test_prepare_move_should_give_passed);

    UNITY_END();
}

#endif // UNIT_TEST