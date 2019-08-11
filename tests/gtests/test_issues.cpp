#include <gtest/gtest.h>
#include <fvar.hpp>
#include <admodel.h>

class test_issues: public ::testing::Test {};

TEST_F(test_issues, issue50)
{
  independent_variables independents(1, 3);
  independents(1) = 60;
  independents(2) = 61;
  independents(3) = 100;

  gradient_structure gs;
  dvar_vector values(independents);
  dvar_vector results = mfexp(values);
  dvector fd1 = value(results);
  fd1 /= std::exp(60.0);
  double dx = 1.0e-10;
  dvar_vector values2(1, 3);
  values2(1) = 60 + dx;
  values2(2) = 61 + dx;
  values2(3) = 100 + dx;
  dvector fd2 = value(mfexp(values2));
  fd2 /= std::exp(60.0);

  objective_function_value total;
  total = sum(results);
  double f = value(total);

  dvector gradients(1, 3);
  gradcalc(3, gradients);

  gradients /= std::exp(60);

  ASSERT_DOUBLE_EQ(gradients(1), std::pow(1.0 + independents(1) - 60.0, -2));
  ASSERT_DOUBLE_EQ(gradients(2), std::pow(1.0 + independents(2) - 60.0, -2));
  ASSERT_DOUBLE_EQ(gradients(3), std::pow(1.0 + independents(3) - 60.0, -2));
 
  dvector fd(1, 3);
  fd(1) = (fd2(1) - fd1(1)) / dx;
  fd(2) = (fd2(2) - fd1(2)) / dx;
  fd(3) = (fd2(3) - fd1(3)) / dx;

  ASSERT_NEAR(fd(1), gradients(1), 0.0001);
  ASSERT_NEAR(fd(2), gradients(2), 0.0001);
  ASSERT_NEAR(fd(3), gradients(3), 0.0001);
}
