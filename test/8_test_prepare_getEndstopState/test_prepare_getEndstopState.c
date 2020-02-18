#ifdef UNIT_TEST

#include <unity.h> // includes unit testing library
#include "connector.h"
#include "device_manager.h"

void setUp()// default setup function
{
    device_manager_init();
}

void tearDown(); // default release function

void test_prepare_getEndstopState_should_give_no_end_key_error()
{
    uint8_t data[] = "opt=ges|abc=x|\n";
    TEST_ASSERT_EQUAL_STRING("_ERROR_no_end_key", connector_manage(connector_parse(data)));
}

void test_prepare_getEndstopState_should_give_invalid_end_value_error()
{
    uint8_t data[] = "opt=ges|end=a|\n";
    TEST_ASSERT_EQUAL_STRING("_ERROR_invalid_end_value", connector_manage(connector_parse(data)));
}

void test_prepare_getEndstopState_should_give_success_0()
{
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, 0);

    uint8_t data[] = "opt=ges|end=XL|\n";
    TEST_ASSERT_EQUAL_STRING("_SUCCESS_XL_STATE_0", connector_manage(connector_parse(data)));
}


int main()
{
    HAL_Init();         // initialize the HAL library
    HAL_Delay(2000);    // service delay

    UNITY_BEGIN();

    RUN_TEST(test_prepare_getEndstopState_should_give_no_end_key_error);
    RUN_TEST(test_prepare_getEndstopState_should_give_invalid_end_value_error);
    RUN_TEST(test_prepare_getEndstopState_should_give_success_0);

    UNITY_END();
}

#endif // UNIT_TEST