#ifdef UNIT_TEST

#include <unity.h> // includes unit testing library

#include "device/device_manager.h"
#include "device/low_voltage/stepper/enum/axis_type.h"
#include "device/low_voltage/stepper/partial/stepper_calculator.h"

void setUp() // default setup function
{
    device_manager_init();
}

void tearDown(); // default release function

/**************** LINEAR stepper speed calculator ********************/

void test_linear_stepper_speed_calculator_1()
{
    Speed_params regs = convertSpeedToRegisters(LINEAR, 0.1f);

    TEST_ASSERT_EQUAL_UINT16(158, regs.psc);
    TEST_ASSERT_EQUAL_UINT16(65535, regs.arr);
    TEST_ASSERT_EQUAL_UINT16(32768, regs.pul);
}

void test_linear_stepper_speed_calculator_2()
{
    Speed_params regs = convertSpeedToRegisters(LINEAR, 1.0f);

    TEST_ASSERT_EQUAL_UINT16(16, regs.psc);
    TEST_ASSERT_EQUAL_UINT16(65535, regs.arr);
    TEST_ASSERT_EQUAL_UINT16(32768, regs.pul);
}

void test_linear_stepper_speed_calculator_3()
{
    Speed_params regs = convertSpeedToRegisters(LINEAR, 5.0f);

    TEST_ASSERT_EQUAL_UINT16(3, regs.psc);
    TEST_ASSERT_EQUAL_UINT16(65535, regs.arr);
    TEST_ASSERT_EQUAL_UINT16(32768, regs.pul);
}

void test_linear_stepper_speed_calculator_4()
{
    Speed_params regs = convertSpeedToRegisters(LINEAR, 10.0f);

    TEST_ASSERT_EQUAL_UINT16(2, regs.psc);
    TEST_ASSERT_EQUAL_UINT16(65535, regs.arr);
    TEST_ASSERT_EQUAL_UINT16(32768, regs.pul);
}

void test_linear_stepper_speed_calculator_5()
{
    Speed_params regs = convertSpeedToRegisters(LINEAR, 100.0f);

    TEST_ASSERT_EQUAL_UINT16(0, regs.psc);
    TEST_ASSERT_EQUAL_UINT16(10333, regs.arr);
    TEST_ASSERT_EQUAL_UINT16(5167, regs.pul);
}

/**************** CIRCULAR stepper speed calculator ********************/

void test_circular_stepper_speed_calculator_1()
{
    Speed_params regs = convertSpeedToRegisters(CIRCULAR, 1.0f);

    TEST_ASSERT_EQUAL_UINT16(12, regs.psc);
    TEST_ASSERT_EQUAL_UINT16(65535, regs.arr);
    TEST_ASSERT_EQUAL_UINT16(32768, regs.pul);
}

void test_circular_stepper_speed_calculator_2()
{
    Speed_params regs = convertSpeedToRegisters(CIRCULAR, 5.0f);

    TEST_ASSERT_EQUAL_UINT16(2, regs.psc);
    TEST_ASSERT_EQUAL_UINT16(65535, regs.arr);
    TEST_ASSERT_EQUAL_UINT16(32768, regs.pul);
}

void test_circular_stepper_speed_calculator_3()
{
    Speed_params regs = convertSpeedToRegisters(CIRCULAR, 10.0f);

    TEST_ASSERT_EQUAL_UINT16(1, regs.psc);
    TEST_ASSERT_EQUAL_UINT16(65535, regs.arr);
    TEST_ASSERT_EQUAL_UINT16(32768, regs.pul);
}

void test_circular_stepper_speed_calculator_4()
{
    Speed_params regs = convertSpeedToRegisters(CIRCULAR, 100.0f);

    TEST_ASSERT_EQUAL_UINT16(0, regs.psc);
    TEST_ASSERT_EQUAL_UINT16(7894, regs.arr);
    TEST_ASSERT_EQUAL_UINT16(3947, regs.pul);
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
    RUN_TEST(test_circular_stepper_speed_calculator_1);
    RUN_TEST(test_circular_stepper_speed_calculator_2);
    RUN_TEST(test_circular_stepper_speed_calculator_3);
    RUN_TEST(test_circular_stepper_speed_calculator_4);

    UNITY_END();
}

#endif // UNIT_TEST