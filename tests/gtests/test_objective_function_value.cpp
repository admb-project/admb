#include <gtest/gtest.h>
#include <admodel.h>

extern "C"
{
  void test_ad_exit(const int exit_code);
}

class test_objective_function_value: public ::testing::Test {};

TEST_F(test_objective_function_value, default_constructor)
{
  gradient_structure gs;
  objective_function_value ofv;

  ASSERT_EQ(objective_function_value::pobjfun, &ofv);
  ASSERT_DOUBLE_EQ(objective_function_value::gmax, 0);
}
TEST_F(test_objective_function_value, operator_equal_double)
{
  gradient_structure gs;
  objective_function_value ofv;
  double v = 5;
  ofv = v;
  ASSERT_DOUBLE_EQ(value(ofv), v);
}
TEST_F(test_objective_function_value, operator_equal_prevariable)
{
  gradient_structure gs;
  objective_function_value ofv;

  dvariable p = -25.0;
  ofv = p;
  ASSERT_DOUBLE_EQ(value(ofv), value(p));
}
TEST_F(test_objective_function_value, default_constructor_no_gradient_structure)
{
  ad_exit=&test_ad_exit;
  try
  {
    objective_function_value ofv;
  }
  catch (const int exit_code)
  {
    return;
  }
  FAIL();
}
