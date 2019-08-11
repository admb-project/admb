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
  objective_function_value total;
  total = sum(results);
  double f = value(total);

  dvector gradients(1, 3);
  gradcalc(3, gradients);

  gradients /= std::exp(60);
  
  ASSERT_DOUBLE_EQ(gradients(1), std::pow(1.0 + independents(1) - 60.0, -2));
  ASSERT_DOUBLE_EQ(gradients(2), std::pow(1.0 + independents(2) - 60.0, -2));
  ASSERT_DOUBLE_EQ(gradients(3), std::pow(1.0 + independents(3) - 60.0, -2));
}
