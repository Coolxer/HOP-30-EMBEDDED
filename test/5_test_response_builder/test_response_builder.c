#ifdef UNIT_TEST

#include <unity.h> // includes unit testing library

#include "stm32f4xx_hal.h"

#include "command/response/response_builder.h"
#include "command/cmd_manager.h"

void setUp()
{
    cmd_manager_init();
}

void tearDown();

/************************** BUILD PASS ****************************/

void test_response_builder_buildPas_1()
{
    TEST_ASSERT_EQUAL_STRING("idx=1|res=pas|@||||||||||||||||#", response_builder_buildPas((uint8_t *)"1"));
}

void test_response_builder_buildPas_2()
{
    TEST_ASSERT_EQUAL_STRING("idx=2|res=pas|@||||||||||||||||#", response_builder_buildPas((uint8_t *)"2"));
}

void test_response_builder_buildPas_3()
{
    TEST_ASSERT_EQUAL_STRING("idx=3|res=pas|@||||||||||||||||#", response_builder_buildPas((uint8_t *)"3"));
}

/************************** BUILD ERROR ****************************/

void test_response_builder_buildErr_1()
{
    TEST_ASSERT_EQUAL_STRING("idx=1|res=err|cod=2|@||||||||||#", response_builder_buildErr((uint8_t *)"1", ERR.NO_PARAMS));
}

void test_response_builder_buildErr_2()
{
    TEST_ASSERT_EQUAL_STRING("idx=2|res=err|cod=5|@||||||||||#", response_builder_buildErr((uint8_t *)"2", ERR.NO_INDEX_KEY));
}

void test_response_builder_buildErr_3()
{
    TEST_ASSERT_EQUAL_STRING("idx=3|res=err|cod=10|@|||||||||#", response_builder_buildErr((uint8_t *)"3", ERR.INCORRECT_STEPPER_VALUE));
}

/************************** BUILD FINISH ****************************/

void test_response_builder_buildFin_1()
{
    TEST_ASSERT_EQUAL_STRING("idx=1|res=fin|@||||||||||||||||#", response_builder_buildFin((uint8_t *)"1"));
}

void test_response_builder_buildFin_2()
{
    TEST_ASSERT_EQUAL_STRING("idx=2|res=fin|@||||||||||||||||#", response_builder_buildFin((uint8_t *)"2"));
}

void test_response_builder_buildFin_3()
{
    TEST_ASSERT_EQUAL_STRING("idx=3|res=fin|@||||||||||||||||#", response_builder_buildFin((uint8_t *)"3"));
}

/************************** BUILD VALUE ****************************/

void test_response_builder_buildVal_1()
{
    uint8_t states[13] = "000000000000\0";
    TEST_ASSERT_EQUAL_STRING("idx=1|res=val|stt=000000000000@#", response_builder_buildVal((uint8_t *)"1", states));
}

void test_response_builder_buildVal_2()
{
    uint8_t states[13] = "111111111111\0";
    TEST_ASSERT_EQUAL_STRING("idx=2|res=val|stt=111111111111@#", response_builder_buildVal((uint8_t *)"2", states));
}

void test_response_builder_buildVal_3()
{
    uint8_t states[13] = "000000111111\0";
    TEST_ASSERT_EQUAL_STRING("idx=3|res=val|stt=000000111111@#", response_builder_buildVal((uint8_t *)"3", states));
}

int main()
{
    HAL_Init();      // initialize the HAL library
    HAL_Delay(2000); // service delay

    UNITY_BEGIN();

    RUN_TEST(test_response_builder_buildPas_1);
    RUN_TEST(test_response_builder_buildPas_2);
    RUN_TEST(test_response_builder_buildPas_3);

    RUN_TEST(test_response_builder_buildErr_1);
    RUN_TEST(test_response_builder_buildErr_2);
    RUN_TEST(test_response_builder_buildErr_3);

    RUN_TEST(test_response_builder_buildFin_1);
    RUN_TEST(test_response_builder_buildFin_2);
    RUN_TEST(test_response_builder_buildFin_3);

    UNITY_END();
}

#endif // UNIT_TEST