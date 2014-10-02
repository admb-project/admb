#include <gtest/gtest.h>
#include <fvar.hpp>

class test_dvariable: public ::testing::Test {};

TEST_F(test_dvariable, fmax)
{
  gradient_structure gs;

  dvariable fmax(double x,double* y);
  double x = 10;
  double y = 20;
  dvariable d = fmax(x, &y);
  ASSERT_EQ(y, value(d));
  d = fmax(y, &x);
  ASSERT_EQ(y, value(d));
  d = fmax(x, &x);
  ASSERT_EQ(x, value(d));
}
