#include <gtest/gtest.h>
#include <fvar.hpp>

class test_return_arrays: public ::testing::Test {};

TEST_F(test_return_arrays, asin)
{
  gradient_structure gs;

  dvar_vector args(1, 5);
  args(1) = -1.0;
  args(2) = -0.5;
  args(3) = 0.0;
  args(4) = 0.5;
  args(5) = 1.0;

  dvar_vector results;
  results.allocate(args);
  results = asin(args);

  ASSERT_DOUBLE_EQ(value(results(1)), std::asin(-1.0));
  ASSERT_DOUBLE_EQ(value(results(2)), std::asin(-0.5));
  ASSERT_DOUBLE_EQ(value(results(3)), std::asin(0));
  ASSERT_DOUBLE_EQ(value(results(4)), std::asin(0.5));
  ASSERT_DOUBLE_EQ(value(results(5)), std::asin(1.0));
}
TEST_F(test_return_arrays, acos)
{
  gradient_structure gs;

  dvar_vector args(1, 5);
  args(1) = -1.0;
  args(2) = -0.5;
  args(3) = 0.0;
  args(4) = 0.5;
  args(5) = 1.0;

  dvar_vector results;
  results.allocate(args);
  results = acos(args);

  ASSERT_DOUBLE_EQ(value(results(1)), std::acos(-1.0));
  ASSERT_DOUBLE_EQ(value(results(2)), std::acos(-0.5));
  ASSERT_DOUBLE_EQ(value(results(3)), std::acos(0));
  ASSERT_DOUBLE_EQ(value(results(4)), std::acos(0.5));
  ASSERT_DOUBLE_EQ(value(results(5)), std::acos(1.0));
}
