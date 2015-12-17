#include <gtest/gtest.h>

#include <df13fun.h>

class test_df1_three_variable: public ::testing::Test {};

TEST_F(test_df1_three_variable, default_constructor)
{
  df1_three_variable x;
  
  ASSERT_EQ(0, value(x));
  ASSERT_EQ(0, *x.get_u());
  ASSERT_EQ(0, *x.get_u_x());
  ASSERT_EQ(0, *x.get_u_y());
  ASSERT_EQ(0, *x.get_u_z());
}
TEST_F(test_df1_three_variable, assignment)
{
  df1_three_variable x;
  x = 10;
  
  ASSERT_EQ(10, value(x));
  ASSERT_EQ(10, *x.get_u());
  ASSERT_EQ(0, *x.get_u_x());
  ASSERT_EQ(0, *x.get_u_y());
  ASSERT_EQ(0, *x.get_u_z());
  *x.get_u_x() = 3;
  *x.get_u_y() = 4;
  *x.get_u_z() = 5;
  ASSERT_EQ(3, *x.get_u_x());
  ASSERT_EQ(4, *x.get_u_y());
  ASSERT_EQ(5, *x.get_u_z());
}
TEST_F(test_df1_three_variable, operator_equal_minus)
{
  df1_three_variable x;

  df1_three_variable y;
  y = 10;
  *y.get_u_x() = 3;
  *y.get_u_y() = 4;
  *y.get_u_z() = 5;

  x -= y;

  ASSERT_EQ(-10, value(x));
  ASSERT_EQ(-10, *x.get_u());
  ASSERT_EQ(-3, *x.get_u_x());
  ASSERT_EQ(-4, *x.get_u_y());
  ASSERT_EQ(-5, *x.get_u_z());
}
TEST_F(test_df1_three_variable, operator_equal_plus)
{
  df1_three_variable x;

  df1_three_variable y;
  y = 10;
  *y.get_u_x() = 3;
  *y.get_u_y() = 4;
  *y.get_u_z() = 5;

  x += y;

  ASSERT_EQ(10, value(x));
  ASSERT_EQ(10, *x.get_u());
  ASSERT_EQ(3, *x.get_u_x());
  ASSERT_EQ(4, *x.get_u_y());
  ASSERT_EQ(5, *x.get_u_z());
}
TEST_F(test_df1_three_variable, operator_equal_multiplication)
{
  double x = -10;

  df1_three_variable y;
  y = 10;
  *y.get_u_x() = 3;
  *y.get_u_y() = 4;
  *y.get_u_z() = 5;

  y *= x;

  ASSERT_EQ(-100, value(y));
  ASSERT_EQ(-100, *y.get_u());
  ASSERT_EQ(-30, *y.get_u_x());
  ASSERT_EQ(-40, *y.get_u_y());
  ASSERT_EQ(-50, *y.get_u_z());
}
TEST_F(test_df1_three_variable, operator_equal_plus_double)
{
  double x = -10;

  df1_three_variable y;
  y = 1;
  *y.get_u_x() = 3;
  *y.get_u_y() = 4;
  *y.get_u_z() = 5;

  y += x;

  ASSERT_EQ(-9, value(y));
  ASSERT_EQ(-9, *y.get_u());
  ASSERT_EQ(3, *y.get_u_x());
  ASSERT_EQ(4, *y.get_u_y());
  ASSERT_EQ(5, *y.get_u_z());
}
TEST_F(test_df1_three_variable, operator_equal_minus_double)
{
  double x = -10;

  df1_three_variable y;
  y = 1;
  *y.get_u_x() = 3;
  *y.get_u_y() = 4;
  *y.get_u_z() = 5;

  y -= x;

  ASSERT_EQ(11, value(y));
  ASSERT_EQ(11, *y.get_u());
  ASSERT_EQ(3, *y.get_u_x());
  ASSERT_EQ(4, *y.get_u_y());
  ASSERT_EQ(5, *y.get_u_z());
}
