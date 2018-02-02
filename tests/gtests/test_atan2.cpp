#include <gtest/gtest.h>
#include <fvar.hpp>
#include <cmath>

extern "C"
{
  void test_ad_exit(const int exit_code);
}

class test_atan2: public ::testing::Test {};

/**
 * Test atan2 for x greater than zero.
 */
TEST_F(test_atan2, x_greater_than_zero)
{
  gradient_structure gs(1500000L);
  dvariable y = 10.0;
  dvariable x = 10.0;
  const double v = value(atan2(y, x));
  const double expected = std::atan2(value(y), value(x));

  ASSERT_DOUBLE_EQ(v, expected);
}
/**
 * Test atan2 for x greater than zero.
 */
TEST_F(test_atan2, y_greater_than_or_equal_zero_x_less_than_zero)
{
  gradient_structure gs(1500000L);
  dvariable y = 10.0;
  dvariable x = -10.0;
  const double v = value(atan2(y, x));
  const double expected = std::atan2(value(y), value(x));

  ASSERT_DOUBLE_EQ(v, expected);
}
/**
 * Test atan2 for x greater than zero.
 */
TEST_F(test_atan2, y_and_x_less_than_zero)
{
  gradient_structure gs(1500000L);
  dvariable y = -10.0;
  dvariable x = -10.0;
  const double v = value(atan2(y, x));
  const double expected = std::atan2(value(y), value(x));

  ASSERT_DOUBLE_EQ(v, expected);
}
/**
 * Test atan2 for x greater than zero.
 */
TEST_F(test_atan2, y_greater_than_zero_and_x_equal_zero)
{
  gradient_structure gs(1500000L);
  dvariable y = 10.0;
  dvariable x = 0.0;
  const double v = value(atan2(y, x));
  const double expected = std::atan2(value(y), value(x));

  ASSERT_DOUBLE_EQ(v, expected);
}
/**
 * Test atan2 for x greater than zero.
 */
TEST_F(test_atan2, y_equal_zero_and_x_less_than_zero)
{
  gradient_structure gs(1500000L);
  dvariable y = 0.0;
  dvariable x = -1.0;
  const double v = value(atan2(y, x));
  const double expected = std::atan2(value(y), value(x));

  ASSERT_DOUBLE_EQ(v, expected);
}
/**
 * Test atan2 for x greater than zero.
 */
TEST_F(test_atan2, y_equal_zero_and_x_greater_than_zero)
{
  gradient_structure gs(1500000L);
  dvariable y = 0.0;
  dvariable x = 1.0;
  const double v = value(atan2(y, x));
  const double expected = std::atan2(value(y), value(x));

  ASSERT_DOUBLE_EQ(v, expected);
}
/**
 * Test atan2 for x greater than zero.
 */
TEST_F(test_atan2, y_less_than_zero_and_x_equal_zero)
{
  gradient_structure gs(1500000L);
  dvariable y = -10.0;
  dvariable x = 0.0;
  const double v = value(atan2(y, x));
  const double expected = std::atan2(value(y), value(x));

  ASSERT_DOUBLE_EQ(v, expected);
}
/**
 * Test atan2 for x and y equal zero.
 */
TEST_F(test_atan2, y_and_x_equal_zero)
{
  gradient_structure gs(1500000L);
  ad_exit=&test_ad_exit;
  dvariable y = 0.0;
  dvariable x = 0.0;
  ASSERT_ANY_THROW({
    atan2(y, x);
  });
}
