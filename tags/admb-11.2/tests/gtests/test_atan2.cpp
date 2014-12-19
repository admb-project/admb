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
  //const double v2 = 2.0 * std::atan((std::sqrt(value(x) * value(x) + value(y) * value(y)) - value(x)) / value(y));
  //std::cout << v << ' ' << expected << ' ' << v2 << std::endl;
  if (expected - 0.000000001 < v && v < expected + 0.000000001)
  {
    SUCCEED();
    return;
  }
  std::cout << v << ' ' << expected << std::endl;
  FAIL();
}
/**
 * Test atan2 for x greater than zero.
 */
TEST_F(test_atan2, y_greater_than_or_equal_zero_x_less_than_zero)
{
  gradient_structure gs(1500000L);
  dvariable y = 10.0;
  dvariable x = -10.0;
  //const double pi = std::atan(1.0)*4.0;
  //const double v = value(atan2(y, x)) + pi ;
  const double v = value(atan2(y, x));
  const double expected = std::atan2(value(y), value(x));
  //const double v2 = 2.0 * std::atan((std::sqrt(value(x) * value(x) + value(y) * value(y)) - value(x)) / value(y));
  //std::cout << v << ' ' << expected << ' ' << v2 << std::endl;
  if (v == expected)
  {
    SUCCEED();
    return;
  }
  std::cout << v << ' ' << expected << std::endl;
  FAIL();
}
/**
 * Test atan2 for x greater than zero.
 */
TEST_F(test_atan2, y_and_x_less_than_zero)
{
  gradient_structure gs(1500000L);
  dvariable y = -10.0;
  dvariable x = -10.0;
  //const double pi = std::atan(1.0)*4.0;
  //const double v = value(atan2(y, x)) - pi;
  const double v = value(atan2(y, x));
  const double expected = std::atan2(value(y), value(x));
  //const double v2 = 2.0 * std::atan((std::sqrt(value(x) * value(x) + value(y) * value(y)) - value(x)) / value(y));
  //std::cout << v << ' ' << expected << ' ' << v2 << std::endl;
  if (v == expected)
  {
    SUCCEED();
    return;
  }
  std::cout << v << ' ' << expected << std::endl;
  FAIL();
}
/**
 * Test atan2 for x greater than zero.
 */
TEST_F(test_atan2, y_greater_than_zero_and_x_equal_zero)
{
  gradient_structure gs(1500000L);
  dvariable y = 10.0;
  dvariable x = 0.0;
  //const double pi_2 = std::atan(1.0)*2.0;
  const double v = value(atan2(y, x));
  //const double v = pi_2;
  const double expected = std::atan2(value(y), value(x));
  //const double v2 = 2.0 * std::atan((std::sqrt(value(x) * value(x) + value(y) * value(y)) - value(x)) / value(y));
  //std::cout << v << ' ' << expected << ' ' << v2 << std::endl;
  if (v == expected)
  {
    SUCCEED();
    return;
  }
  std::cout << v << ' ' << expected << std::endl;
  FAIL();
}
/**
 * Test atan2 for x greater than zero.
 */
TEST_F(test_atan2, y_equal_zero_and_x_less_than_zero)
{
  gradient_structure gs(1500000L);
  dvariable y = 0.0;
  dvariable x = -1.0;
  //const double pi_2 = -1.0*std::atan(1.0)*2.0;
  const double v = value(atan2(y, x));
  //const double v = pi_2;
  const double expected = std::atan2(value(y), value(x));
  //const double v2 = 2.0 * std::atan((std::sqrt(value(x) * value(x) + value(y) * value(y)) - value(x)) / value(y));
  //std::cout << v << ' ' << expected << ' ' << v2 << std::endl;
  if (v == expected)
  {
    SUCCEED();
    return;
  }
  std::cout << v << ' ' << expected << std::endl;
  FAIL();
}
/**
 * Test atan2 for x greater than zero.
 */
TEST_F(test_atan2, y_equal_zero_and_x_greater_than_zero)
{
  gradient_structure gs(1500000L);
  dvariable y = 0.0;
  dvariable x = 1.0;
  //const double pi_2 = -1.0*std::atan(1.0)*2.0;
  const double v = value(atan2(y, x));
  //const double v = pi_2;
  const double expected = std::atan2(value(y), value(x));
  //const double v2 = 2.0 * std::atan((std::sqrt(value(x) * value(x) + value(y) * value(y)) - value(x)) / value(y));
  //std::cout << v << ' ' << expected << ' ' << v2 << std::endl;
  if (v == expected)
  {
    SUCCEED();
    return;
  }
  std::cout << v << ' ' << expected << std::endl;
  FAIL();
}
/**
 * Test atan2 for x greater than zero.
 */
TEST_F(test_atan2, y_less_than_zero_and_x_equal_zero)
{
  gradient_structure gs(1500000L);
  dvariable y = -10.0;
  dvariable x = 0.0;
  //const double pi_2 = -1.0*std::atan(1.0)*2.0;
  const double v = value(atan2(y, x));
  //const double v = pi_2;
  const double expected = std::atan2(value(y), value(x));
  //const double v2 = 2.0 * std::atan((std::sqrt(value(x) * value(x) + value(y) * value(y)) - value(x)) / value(y));
  //std::cout << v << ' ' << expected << ' ' << v2 << std::endl;
  if (v == expected)
  {
    SUCCEED();
    return;
  }
  std::cout << v << ' ' << expected << std::endl;
  FAIL();
}
/**
 * Test atan2 for x and y equal zero.
 */
TEST_F(test_atan2, y_and_x_equal_zero)
{
  gradient_structure gs(1500000L);
  ad_exit=&test_ad_exit;
  try
  {
    dvariable y = 0.0;
    dvariable x = 0.0;
    atan2(y, x);
  }
  catch (const int exit_code)          
  {   
    const int expected_exit_code = 1;
    if (exit_code == expected_exit_code)
    {
      SUCCEED();
      return;
    }
  }
  FAIL();
}
