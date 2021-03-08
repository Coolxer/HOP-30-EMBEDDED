#ifdef UNIT_TEST

#include <unity.h> // includes unit testing library
#include "device/stepper/enum/axis_type.h"
#include "device/device_manager.h"

void setUp() // default setup function
{
    device_manager_init();
}

void tearDown(); // default release function

/**************** linear stepper way calculator ********************/

void test_linear_stepper_way_calculator_1()
{
    Way params = calculate_way(LINEAR, 0.01f);

    TEST_ASSERT_EQUAL_UINT16(0, params.laps);
    TEST_ASSERT_EQUAL_UINT16(2, params.arr);
}

void test_linear_stepper_way_calculator_2()
{
    Way params = calculate_way(LINEAR, 0.1f);

    TEST_ASSERT_EQUAL_UINT16(0, params.laps);
    TEST_ASSERT_EQUAL_UINT16(15, params.arr);
}

void test_linear_stepper_way_calculator_3()
{
    Way params = calculate_way(LINEAR, 1.0f);

    TEST_ASSERT_EQUAL_UINT16(0, params.laps);
    TEST_ASSERT_EQUAL_UINT16(155, params.arr);
}

void test_linear_stepper_way_calculator_4()
{
    Way params = calculate_way(LINEAR, 10.0f);

    TEST_ASSERT_EQUAL_UINT16(0, params.laps);
    TEST_ASSERT_EQUAL_UINT16(1548, params.arr);
}

void test_linear_stepper_way_calculator_5()
{
    Way params = calculate_way(LINEAR, 100.0f);

    TEST_ASSERT_EQUAL_UINT16(0, params.laps);
    TEST_ASSERT_EQUAL_UINT16(15483, params.arr);
}

void test_linear_stepper_way_calculator_6()
{
    Way params = calculate_way(LINEAR, 500.0f);

    TEST_ASSERT_EQUAL_UINT16(1, params.laps);
    TEST_ASSERT_EQUAL_UINT16(11878, params.arr);
}

void test_linear_stepper_way_calculator_7()
{
    Way params = calculate_way(LINEAR, 1000.0f);

    TEST_ASSERT_EQUAL_UINT16(2, params.laps);
    TEST_ASSERT_EQUAL_UINT16(23756, params.arr);
}

/**************** circular stepper way calculator ********************/

void test_circular_stepper_way_calculator_1()
{
    Way params = calculate_way(CIRCULAR, 0.1f);

    TEST_ASSERT_EQUAL_UINT16(0, params.laps);
    TEST_ASSERT_EQUAL_UINT16(3, params.arr);
}

void test_circular_stepper_way_calculator_2()
{
    Way params = calculate_way(CIRCULAR, 1.0f);

    TEST_ASSERT_EQUAL_UINT16(0, params.laps);
    TEST_ASSERT_EQUAL_UINT16(34, params.arr);
}

void test_circular_stepper_way_calculator_3()
{
    Way params = calculate_way(CIRCULAR, 10.0f);

    TEST_ASSERT_EQUAL_UINT16(0, params.laps);
    TEST_ASSERT_EQUAL_UINT16(338, params.arr);
}

void test_circular_stepper_way_calculator_4()
{
    Way params = calculate_way(CIRCULAR, 100.0f);

    TEST_ASSERT_EQUAL_UINT16(0, params.laps);
    TEST_ASSERT_EQUAL_UINT16(3378, params.arr);
}

void test_circular_stepper_way_calculator_5()
{
    Way params = calculate_way(CIRCULAR, 360.0f);

    TEST_ASSERT_EQUAL_UINT16(0, params.laps);
    TEST_ASSERT_EQUAL_UINT16(12160, params.arr);
}

void test_circular_stepper_way_calculator_6()
{
    Way params = calculate_way(CIRCULAR, 720.0f);

    TEST_ASSERT_EQUAL_UINT16(0, params.laps);
    TEST_ASSERT_EQUAL_UINT16(24320, params.arr);
}

void test_circular_stepper_way_calculator_7()
{
    Way params = calculate_way(CIRCULAR, 1080.0f);

    TEST_ASSERT_EQUAL_UINT16(0, params.laps);
    TEST_ASSERT_EQUAL_UINT16(36480, params.arr);
}

int main()
{
    HAL_Init();      // initialize the HAL library
    HAL_Delay(2000); // service delay

    UNITY_BEGIN();

    // linear stepper way calculator
    RUN_TEST(test_linear_stepper_way_calculator_1);
    RUN_TEST(test_linear_stepper_way_calculator_2);
    RUN_TEST(test_linear_stepper_way_calculator_3);
    RUN_TEST(test_linear_stepper_way_calculator_4);
    RUN_TEST(test_linear_stepper_way_calculator_5);

    // circular stepper way calculator
    RUN_TEST(test_circular_stepper_way_calculator_1);
    RUN_TEST(test_circular_stepper_way_calculator_2);
    RUN_TEST(test_circular_stepper_way_calculator_3);
    RUN_TEST(test_circular_stepper_way_calculator_4);
    RUN_TEST(test_circular_stepper_way_calculator_5);

    UNITY_END();
}

#endif // UNIT_TEST