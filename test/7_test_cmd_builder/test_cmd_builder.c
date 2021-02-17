#ifdef UNIT_TEST

#include <unity.h> // includes unit testing
#include "stm32f4xx_hal.h"
#include "command/cmd_builder.h"

void setUp()
{
    cmd_builder_init();
}

void tearDown(); // default release function

// cmd_builder pas

void cmd_builder_buildPas_1()
{
    TEST_ASSERT_EQUAL_STRING("idx=1|res=pas|\n", cmd_builder_buildPas((uint8_t *)"1"));
}

void cmd_builder_buildPas_2()
{
    TEST_ASSERT_EQUAL_STRING("idx=2|res=pas|\n", cmd_builder_buildPas((uint8_t *)"2"));
}

void cmd_builder_buildPas_3()
{
    TEST_ASSERT_EQUAL_STRING("idx=5|res=pas|\n", cmd_builder_buildPas((uint8_t *)"5"));
}

// cmd_builder err

void cmd_builder_buildErr_1()
{
    TEST_ASSERT_EQUAL_STRING("idx=0|res=err|cod=1|\n", cmd_builder_buildErr((uint8_t *)"0", (uint8_t *)"1"));
}

void cmd_builder_buildErr_2()
{
    TEST_ASSERT_EQUAL_STRING("idx=1|res=err|cod=1|\n", cmd_builder_buildErr((uint8_t *)"1", (uint8_t *)"1"));
}

void cmd_builder_buildErr_3()
{
    TEST_ASSERT_EQUAL_STRING("idx=5|res=err|cod=2|\n", cmd_builder_buildErr((uint8_t *)"5", (uint8_t *)"2"));
}

// cmd_builder fin

void cmd_builder_buildFin_1()
{
    TEST_ASSERT_EQUAL_STRING("idx=1|res=fin|\n", cmd_builder_buildFin((uint8_t *)"1", (uint8_t *)"2"));
}

void cmd_builder_buildFin_2()
{
    TEST_ASSERT_EQUAL_STRING("idx=2|res=fin|\n", cmd_builder_buildFin((uint8_t *)"2", (uint8_t *)"2"));
}

void cmd_builder_buildFin_3()
{
    TEST_ASSERT_EQUAL_STRING("idx=2|res=fin|val=0|\n", cmd_builder_buildFin((uint8_t *)"2", (uint8_t *)"0"));
}

int main()
{
    HAL_Init();      // initialize the HAL library
    HAL_Delay(2000); // service delay

    UNITY_BEGIN();

    RUN_TEST(cmd_builder_buildPas_1);
    RUN_TEST(cmd_builder_buildPas_2);
    RUN_TEST(cmd_builder_buildPas_3);

    RUN_TEST(cmd_builder_buildErr_1);
    RUN_TEST(cmd_builder_buildErr_2);
    RUN_TEST(cmd_builder_buildErr_3);

    RUN_TEST(cmd_builder_buildFin_1);
    RUN_TEST(cmd_builder_buildFin_2);
    RUN_TEST(cmd_builder_buildFin_3);

    UNITY_END();
}

#endif // UNIT_TEST