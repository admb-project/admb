#include <gtest/gtest.h>
#include <fvar.hpp>

extern "C"
{
  void test_ad_exit(const int exit_code);
}

class test_funnels: public ::testing::Test {};

TEST_F(test_funnels, simple)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;

  dvector x(1, 10);
  x(1) = -1.0;
  x(2) = 0.0;
  x(3) = 1.0;
  x(4) = 2.0;
  x(5) = 3.0;
  x(6) = 4.0;
  x(7) = 5.0;
  x(8) = 6.0;
  x(9) = 7.0;
  x(10) = 8.0;

  dvector y(1, 10);
  y(1) = 1.4;
  y(2) = 4.7;
  y(3) = 5.1;
  y(4) = 8.3;
  y(5) = 9.0;
  y(6) = 14.5;
  y(7) = 14.0;
  y(8) = 13.4;
  y(9) = 19.2;
  y(10) = 18.0;

  independent_variables independents(1, 2);
  independents.initialize();

  // Set gradient_structure::NVAR
  dvar_vector variables(independents);

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 0);

  dvar_vector yhat(1, 10);

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 0);

  yhat = variables(1) + variables(2) * x;

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 3);

  dvariable f = 0.0;

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 4);

  funnel_dvariable Integral;

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 4);

  ad_begin_funnel();

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 5);

  dvariable tmp;
  tmp = regression(y,yhat);

  ASSERT_TRUE(gradient_structure::GRAD_STACK1->total() >= 13);

  Integral = tmp;

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 5);

  f = Integral;

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 6);

  double result = value(f);

  dvector g(1, 2);
  gradcalc(2, g);

  ASSERT_DOUBLE_EQ(result, 24.980653039466869);
  ASSERT_DOUBLE_EQ(g(1), -0.7278138528138528);
  ASSERT_DOUBLE_EQ(g(2), -3.6126893939393945);
}
