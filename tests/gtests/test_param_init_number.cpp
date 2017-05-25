#include <gtest/gtest.h>
#include "admodel.h"

class test_param_init_number: public ::testing::Test {};

TEST_F(test_param_init_number, constructor)
{
  gradient_structure gs;
  dll_param_init_number n;
}
TEST_F(test_param_init_number, allocate_assignments)
{
  gradient_structure gs;
  dll_param_init_number n;

  double expected_pd = 5;
  n.allocate(&expected_pd, "test_param_init_number");
  ASSERT_DOUBLE_EQ(expected_pd, value(n));

  n = 10;
  ASSERT_DOUBLE_EQ(10, value(n));

  dvariable var = 20;
  n = var;
  ASSERT_DOUBLE_EQ(value(var), value(n));
}
