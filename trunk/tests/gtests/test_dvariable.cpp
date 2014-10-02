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
TEST_F(test_dvariable, det)
{
  gradient_structure gs;

  dvar_matrix vm(1, 2, 1, 2);
  vm(1, 1) = 3;
  vm(1, 2) = 8;
  vm(2, 1) = 4;
  vm(2, 2) = 6;

  dvariable vdet = det(vm);
  ASSERT_DOUBLE_EQ(-14, value(vdet));

  dmatrix m(1, 2, 1, 2);
  m(1, 1) = 3;
  m(1, 2) = 8;
  m(2, 1) = 4;
  m(2, 2) = 6;
  double cdet = det(m);
  ASSERT_DOUBLE_EQ(-14, cdet);
}
