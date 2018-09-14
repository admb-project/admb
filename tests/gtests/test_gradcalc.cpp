#include <gtest/gtest.h>
#include <fvar.hpp>

extern "C"
{
  void test_ad_exit(const int exit_code);
}

class test_gradcalc: public ::testing::Test {};

TEST_F(test_gradcalc, nvarzero)
{
  ad_exit=&test_ad_exit;

  dvector g;

  //ASSERT_EQ(0, gradient_structure::NVAR);

  ASSERT_ANY_THROW({
    gradcalc(1, g);
  });
}
TEST_F(test_gradcalc, simple)
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

  dvar_vector yhat(1, 10);
  yhat = variables(1) + variables(2) * x;

  dvariable f = 0.0;
  f=regression(y,yhat);

  double result = value(f);

  dvector g(1, 2);
  gradcalc(2, g);

  ASSERT_DOUBLE_EQ(result, 24.980653039466869);
  ASSERT_DOUBLE_EQ(g(1), -0.7278138528138528);
  ASSERT_DOUBLE_EQ(g(2), -3.6126893939393945);

}
TEST_F(test_gradcalc, simple_final)
{
  ad_exit=&test_ad_exit;

  ASSERT_TRUE(gradient_structure::GRAD_STACK1 == NULL);

  gradient_structure gs;

  ASSERT_TRUE(gradient_structure::GRAD_STACK1 != NULL);

  const unsigned int NUM_RETURN_ARRAYS = 25;
  unsigned int expected_total = //1750
    NUM_RETURN_ARRAYS * gradient_structure::RETURN_ARRAYS_SIZE;
  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), expected_total);

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
  independents(1) = 4.07818;
  independents(2) = 1.90909;

  // Set gradient_structure::NVAR
  dvar_vector variables(independents);

  dvar_vector yhat(1, 10);
  yhat = variables(1) + variables(2) * x;
  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), expected_total + 3);

  ASSERT_DOUBLE_EQ(value(yhat(1)), independents(1) + independents(2) * x(1));
  ASSERT_DOUBLE_EQ(value(yhat(2)), independents(1) + independents(2) * x(2));
  ASSERT_DOUBLE_EQ(value(yhat(3)), independents(1) + independents(2) * x(3));
  ASSERT_DOUBLE_EQ(value(yhat(4)), independents(1) + independents(2) * x(4));
  ASSERT_DOUBLE_EQ(value(yhat(5)), independents(1) + independents(2) * x(5));
  ASSERT_DOUBLE_EQ(value(yhat(6)), independents(1) + independents(2) * x(6));
  ASSERT_DOUBLE_EQ(value(yhat(7)), independents(1) + independents(2) * x(7));
  ASSERT_DOUBLE_EQ(value(yhat(8)), independents(1) + independents(2) * x(8));
  ASSERT_DOUBLE_EQ(value(yhat(9)), independents(1) + independents(2) * x(9));
  ASSERT_DOUBLE_EQ(value(yhat(10)), independents(1) + independents(2) * x(10));

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), expected_total + 3);
  dvariable f = 0.0;
  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), expected_total + 4);
  f=regression(y,yhat);
  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), expected_total + 14);

  double result = value(f);
  ASSERT_DOUBLE_EQ(result, 3.4512604236817603);

  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), expected_total + 14);
  dvector g(1, 2);
  gradcalc(2, g);
  ASSERT_EQ(gradient_structure::GRAD_STACK1->total(), 0);

  ASSERT_DOUBLE_EQ(g(1), value(variables(1)));
  ASSERT_DOUBLE_EQ(g(2), value(variables(2)));

  ASSERT_DOUBLE_EQ(value(f), 0.0);
  ASSERT_DOUBLE_EQ(independents(1), 4.07818);
  ASSERT_DOUBLE_EQ(independents(2), 1.90909);
  ASSERT_DOUBLE_EQ(value(yhat(1)), 0.0);
  ASSERT_DOUBLE_EQ(value(yhat(2)), 0.0);
  ASSERT_DOUBLE_EQ(value(yhat(3)), 0.0);
  ASSERT_DOUBLE_EQ(value(yhat(4)), 0.0);
  ASSERT_DOUBLE_EQ(value(yhat(5)), 0.0);
  ASSERT_DOUBLE_EQ(value(yhat(6)), 0.0);
  ASSERT_DOUBLE_EQ(value(yhat(7)), 0.0);
  ASSERT_DOUBLE_EQ(value(yhat(8)), 0.0);
  ASSERT_DOUBLE_EQ(value(yhat(9)), 0.0);
  ASSERT_DOUBLE_EQ(value(yhat(10)), 0.0);
}
