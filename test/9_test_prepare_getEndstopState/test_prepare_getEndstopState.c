#ifdef UNIT_TEST

#include <unity.h> // includes unit testing 
#include "connector.h"
#include "device_manager.h"

void setUp()// default setup function
{
    cmd_builder_init();
    device_manager_init();
}

void tearDown(); // default release function

void test_prepare_getEndstopState_should_give_14()
{
    uint8_t data[] = "idx=1|opt=ges|abc=x|\n";
    TEST_ASSERT_EQUAL_STRING("idx=1|res=err|cod=14|\n", connector_manage(connector_parse(data)));
}

void test_prepare_getEndstopState_should_give_15()
{
    uint8_t data[] = "idx=1|opt=ges|end=a|\n";
    TEST_ASSERT_EQUAL_STRING("idx=1|res=err|cod=15|\n", connector_manage(connector_parse(data)));
}

void test_prepare_getEndstopState_should_give_finished_0()
{
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, 0);

    uint8_t data[] = "idx=1|opt=ges|end=XL|\n";
    TEST_ASSERT_EQUAL_STRING("idx=1|res=fin|val=0|\n", connector_manage(connector_parse(data)));
}


int main()
{
    HAL_Init();         // initialize the HAL library
    HAL_Delay(2000);    // service delay

    UNITY_BEGIN();

    RUN_TEST(test_prepare_getEndstopState_should_give_14);
    RUN_TEST(test_prepare_getEndstopState_should_give_15);
    RUN_TEST(test_prepare_getEndstopState_should_give_finished_0);

    UNITY_END();
}

#endif // UNIT_TEST