#ifdef UNIT_TEST

#include <unity.h> // includes unit testing library
#include "command/cmd_builder.h"
#include "connector.h"
#include "device_manager.h"

void setUp() // default setup function
{
    cmd_builder_init();
    device_manager_init();
}

void tearDown(); // default release function

void test_prepare_process_should_give_21()
{
    uint8_t data[] = "idx=1|opt=pro|spp=x|\n";
    TEST_ASSERT_EQUAL_STRING("idx=1|res=err|cod=21|\n", connector_manage(connector_parse(data)));
}

void test_prepare_process_should_give_22()
{
    uint8_t data[] = "idx=1|opt=pro|dir=x|\n";
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

    RUN_TEST(test_prepare_process_should_give_21);
    RUN_TEST(test_prepare_process_should_give_22);
    RUN_TEST(test_prepare_process_should_give_passed);

    UNITY_END();
}

#endif // UNIT_TEST