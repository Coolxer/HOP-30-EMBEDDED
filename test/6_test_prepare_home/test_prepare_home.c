#ifdef UNIT_TEST

#include <unity.h> // includes unit testing library
#include "connector.h"
#include "device_manager.h"

void setUp()// default setup function
{
    device_manager_init();
}

void tearDown(); // default release function

void test_prepare_home_should_give_no_spp_key_error()
{
    uint8_t data[] = "opt=hom|abc=x|\n";
    uint8_t ***args = connector_parse(data);

    uint8_t *result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_ERROR_no_spp_key", result);
}

/*********************** home all ***************************/

void test_prepare_home_all_should_give_valid_command()
{
    uint8_t data[] = "opt=hom|spp=all|\n";
    uint8_t ***args = connector_parse(data);

    uint8_t *result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_VALID_COMMAND", result); 
}

/******************** home individual ************************/

void test_prepare_home_should_give_invalid_spp_value_error()
{
    uint8_t data[] = "opt=hom|spp=a|\n";
    uint8_t ***args = connector_parse(data);

    uint8_t *result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_ERROR_invalid_spp_value", result);
}

void test_prepare_home_should_give_valid_command()
{
    uint8_t data[] = "opt=hom|spp=x|\n";
    uint8_t ***args = connector_parse(data);

    uint8_t *result = connector_manage(args);

    TEST_ASSERT_EQUAL_STRING("_VALID_COMMAND", result);
}

int main()
{
    HAL_Init();         // initialize the HAL library
    HAL_Delay(2000);    // service delay

    UNITY_BEGIN();

    RUN_TEST(test_prepare_home_should_give_no_spp_key_error);

    RUN_TEST(test_prepare_home_all_should_give_valid_command);

    RUN_TEST(test_prepare_home_should_give_invalid_spp_value_error);
    RUN_TEST(test_prepare_home_should_give_valid_command);

    UNITY_END();
}

#endif // UNIT_TEST