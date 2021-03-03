#ifdef UNIT_TEST

#include <unity.h> // includes unit testing library
#include "enum/axis_type.h"
#include "device/device_manager.h"

void setUp() // default setup function
{
    device_manager_init();
}

void tearDown(); // default release function

/**************** linear stepper speed calculator ********************/

void test_linear_stepper_speed_calculator_1()
{
    Speed regs = calculate_speed(LINEAR, 0.1f);

    TEST_ASSERT_EQUAL_UINT16(39, regs.psc);
    TEST_ASSERT_EQUAL_UINT16(65535, regs.arr);
    TEST_ASSERT_EQUAL_UINT16(32768, regs.pul);
}

void test_linear_stepper_speed_calculator_2()
{
    Speed regs = calculate_speed(LINEAR, 1.0f);

    TEST_ASSERT_EQUAL_UINT16(4, regs.psc);
    TEST_ASSERT_EQUAL_UINT16(65535, regs.arr);
    TEST_ASSERT_EQUAL_UINT16(32768, regs.pul);
}

void test_linear_stepper_speed_calculator_3()
{
    Speed regs = calculate_speed(LINEAR, 5.0f);

    TEST_ASSERT_EQUAL_UINT16(0, regs.psc);
    TEST_ASSERT_EQUAL_UINT16(51670, regs.arr);
    TEST_ASSERT_EQUAL_UINT16(25835, regs.pul);
}

void test_linear_stepper_speed_calculator_4()
{
    Speed regs = calculate_speed(LINEAR, 10.0f);

    TEST_ASSERT_EQUAL_UINT16(0, regs.psc);
    TEST_ASSERT_EQUAL_UINT16(25834, regs.arr);
    TEST_ASSERT_EQUAL_UINT16(12917, regs.pul);
}

void test_linear_stepper_speed_calculator_5()
{
    Speed regs = calculate_speed(LINEAR, 100.0f);

    TEST_ASSERT_EQUAL_UINT16(0, regs.psc);
    TEST_ASSERT_EQUAL_UINT16(2583, regs.arr);
    TEST_ASSERT_EQUAL_UINT16(1292, regs.pul);
}

/**************** circular stepper speed calculator ********************/

void test_circular_stepper_speed_calculator_1()
{
    Speed regs = calculate_speed(CIRCULAR, 1.0f);

    TEST_ASSERT_EQUAL_UINT16(3, regs.psc);
    TEST_ASSERT_EQUAL_UINT16(65535, regs.arr);
    TEST_ASSERT_EQUAL_UINT16(32768, regs.pul);
}

void test_circular_stepper_speed_calculator_2()
{
    Speed regs = calculate_speed(CIRCULAR, 5.0f);

    TEST_ASSERT_EQUAL_UINT16(0, regs.psc);
    TEST_ASSERT_EQUAL_UINT16(39473, regs.arr);
    TEST_ASSERT_EQUAL_UINT16(19737, regs.pul);
}

void test_circular_stepper_speed_calculator_3()
{
    Speed regs = calculate_speed(CIRCULAR, 10.0f);

    TEST_ASSERT_EQUAL_UINT16(0, regs.psc);
    TEST_ASSERT_EQUAL_UINT16(19736, regs.arr);
    TEST_ASSERT_EQUAL_UINT16(9868, regs.pul);
}

void test_circular_stepper_speed_calculator_4()
{
    Speed regs = calculate_speed(CIRCULAR, 100.0f);

    TEST_ASSERT_EQUAL_UINT16(0, regs.psc);
    TEST_ASSERT_EQUAL_UINT16(1973, regs.arr);
    TEST_ASSERT_EQUAL_UINT16(987, regs.pul);
}

int main()
{
    HAL_Init();      // initialize the HAL library
    HAL_Delay(2000); // service delay

    UNITY_BEGIN();

    // linear stepper speed calculator
    RUN_TEST(test_linear_stepper_speed_calculator_1);
    RUN_TEST(test_linear_stepper_speed_calculator_2);
    RUN_TEST(test_linear_stepper_speed_calculator_3);
    RUN_TEST(test_linear_stepper_speed_calculator_4);
    RUN_TEST(test_linear_stepper_speed_calculator_5);

    // linear stepper steps calculator
    RUN_TEST(test_linear_stepper_speed_calculator_1);
    RUN_TEST(test_linear_stepper_speed_calculator_2);
    RUN_TEST(test_linear_stepper_speed_calculator_3);
    RUN_TEST(test_linear_stepper_speed_calculator_4);

    UNITY_END();
}

#endif // UNIT_TEST