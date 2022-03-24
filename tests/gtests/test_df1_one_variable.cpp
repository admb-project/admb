#include <gtest/gtest.h>

#include <df11fun.h>

class test_df1_one_variable: public ::testing::Test {};

TEST_F(test_df1_one_variable, default_constructor)
{
  df1_one_variable x;
  
  ASSERT_EQ(0, value(x));
  ASSERT_EQ(0, *x.get_u());
  ASSERT_EQ(0, *x.get_u_x());
  ASSERT_EQ(0, *x.get_udot());
}
TEST_F(test_df1_one_variable, assignment)
{
  df1_one_variable x;
  x = 10;
  
  ASSERT_EQ(10, value(x));
  ASSERT_EQ(10, *x.get_u());
  ASSERT_EQ(0, *x.get_u_x());
  ASSERT_EQ(0, *x.get_udot());
  *x.get_u_x() = 3;
  ASSERT_EQ(3, *x.get_u_x());
  ASSERT_EQ(3, *x.get_udot());
  *x.get_udot() = 4;
  ASSERT_EQ(4, *x.get_u_x());
  ASSERT_EQ(4, *x.get_udot());
}
TEST_F(test_df1_one_variable, operator_equal_minus)
{
  df1_one_variable x;

  df1_one_variable y;
  y = 10;
  *y.get_u_x() = 3;

  x -= y;

  ASSERT_EQ(-10, value(x));
  ASSERT_EQ(-10, *x.get_u());
  ASSERT_EQ(-3, *x.get_u_x());
}
TEST_F(test_df1_one_variable, operator_equal_minus_double)
{
  double x = -1;

  df1_one_variable y;
  y = 10;
  *y.get_u_x() = 3;

  y -= x;

  ASSERT_EQ(11, value(y));
  ASSERT_EQ(11, *y.get_u());
  //\todo should be 4???
  ASSERT_EQ(3, *y.get_u_x());
}
TEST_F(test_df1_one_variable, operator_equal_plus)
{
  df1_one_variable x;

  df1_one_variable y;
  y = 10;
  *y.get_u_x() = 3;

  x += y;

  ASSERT_EQ(10, value(x));
  ASSERT_EQ(10, *x.get_u());
  ASSERT_EQ(3, *x.get_u_x());
}
TEST_F(test_df1_one_variable, operator_equal_plus_double)
{
  double x = 0;

  df1_one_variable y;
  y = 10;
  *y.get_u_x() = 3;

  y += x;

  ASSERT_EQ(10, value(y));
  ASSERT_EQ(10, *y.get_u());
  ASSERT_EQ(3, *y.get_u_x());
}
TEST_F(test_df1_one_variable, operator_equal_multiply)
{
  df1_one_variable x;
  x = 2;
  *x.get_u_x() = 1;

  df1_one_variable y;
  y = 10;
  *y.get_u_x() = 3;

  x *= y;

  ASSERT_EQ(20, value(x));
  ASSERT_EQ(20, *x.get_u());
  //\todo can't understand how it got 16???
  ASSERT_EQ(16, *x.get_u_x());
}
/*
TEST_F(test_df1_one_variable, init_df1_one_variable)
{
  gradient_structure gs;
  dvariable variable;
  variable = 4.5;
  ASSERT_EQ(0, df1_one_variable::num_ind_var);
  ASSERT_TRUE(df1_one_variable::ind_var[0] == NULL);
  init_df1_one_variable n(variable);
  ASSERT_DOUBLE_EQ(4.5, *(n.get_u()));
  ASSERT_DOUBLE_EQ(1, *(n.get_u_x()));
  ASSERT_EQ(1, df1_one_variable::num_ind_var);
  ASSERT_TRUE(&variable == df1_one_variable::ind_var[0]);
  try
  {
    init_df1_one_variable n2(variable);
  }
  catch (const int exit_code)
  {
    return;
  }
  FAIL();
}
*/
TEST_F(test_df1_one_variable, operator_negative)
{
  df1_one_variable x;
  x = 2;
  *x.get_u_x() = -1;

  df1_one_variable y;

  y = -x;

  ASSERT_DOUBLE_EQ(-2, value(y));
  ASSERT_DOUBLE_EQ(-2, *y.get_u());
  ASSERT_DOUBLE_EQ(1, *y.get_u_x());
  ASSERT_DOUBLE_EQ(1, *y.get_udot());
}
TEST_F(test_df1_one_variable, operator_multiply)
{
  df1_one_variable x;
  x = 2;
  *x.get_u_x() = -1;

  df1_one_variable y;

  y = 2.0 * x;

  ASSERT_DOUBLE_EQ(4, value(y));
  ASSERT_DOUBLE_EQ(4, *y.get_u());
  ASSERT_DOUBLE_EQ(-2, *y.get_u_x());
  ASSERT_DOUBLE_EQ(-2, *y.get_udot());
}
TEST_F(test_df1_one_variable, operator_multiply2)
{
  df1_one_variable x;
  x = 2;
  *x.get_u_x() = -1;

  df1_one_variable y;

  y = x * 2.0;

  ASSERT_DOUBLE_EQ(4, value(y));
  ASSERT_DOUBLE_EQ(4, *y.get_u());
  ASSERT_DOUBLE_EQ(-2, *y.get_u_x());
  ASSERT_DOUBLE_EQ(-2, *y.get_udot());
}
TEST_F(test_df1_one_variable, operator_plus)
{
  df1_one_variable x;
  x = 2;
  *x.get_u_x() = -1;

  df1_one_variable y;

  y = 2.0 + x;

  ASSERT_DOUBLE_EQ(4, value(y));
  ASSERT_DOUBLE_EQ(4, *y.get_u());
  ASSERT_DOUBLE_EQ(-1, *y.get_u_x());
  ASSERT_DOUBLE_EQ(-1, *y.get_udot());
}
TEST_F(test_df1_one_variable, operator_plus2)
{
  df1_one_variable x;
  x = 2;
  *x.get_u_x() = -1;

  df1_one_variable y;

  y = x + 2.0;

  ASSERT_DOUBLE_EQ(4, value(y));
  ASSERT_DOUBLE_EQ(4, *y.get_u());
  ASSERT_DOUBLE_EQ(-1, *y.get_u_x());
  ASSERT_DOUBLE_EQ(-1, *y.get_udot());
}
TEST_F(test_df1_one_variable, operator_minus)
{
  df1_one_variable x;
  x = 2;
  *x.get_u_x() = -1;

  df1_one_variable y;

  y = 2.0 - x;

  ASSERT_DOUBLE_EQ(0, value(y));
  ASSERT_DOUBLE_EQ(0, *y.get_u());
  ASSERT_DOUBLE_EQ(1, *y.get_u_x());
  ASSERT_DOUBLE_EQ(1, *y.get_udot());
}
TEST_F(test_df1_one_variable, operator_minus2)
{
  df1_one_variable x;
  x = 2;
  *x.get_u_x() = -1;

  df1_one_variable y;

  y = x - 2.0;

  ASSERT_DOUBLE_EQ(0, value(y));
  ASSERT_DOUBLE_EQ(0, *y.get_u());
  ASSERT_DOUBLE_EQ(-1, *y.get_u_x());
  ASSERT_DOUBLE_EQ(-1, *y.get_udot());
}
