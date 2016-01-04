#include <gtest/gtest.h>

#include <df12fun.h>

class test_df1_two_variable: public ::testing::Test {};

TEST_F(test_df1_two_variable, default_constructor)
{
  df1_two_variable x;
  
  ASSERT_EQ(0, value(x));
  ASSERT_EQ(0, *x.get_u());
  ASSERT_EQ(0, *x.get_u_x());
  ASSERT_EQ(0, *x.get_u_y());
}
TEST_F(test_df1_two_variable, plus_equal_operator)
{
  df1_two_variable x;
  df1_two_variable y;

  *x.get_u() = 1;
  *x.get_u_x() = 2;
  *x.get_u_y() = 3;
  *y.get_u() = 1;
  *y.get_u_x() = 2;
  *y.get_u_y() = 3;

  x += y;
  
  ASSERT_EQ(*x.get_u(), value(x));
  ASSERT_EQ(2, *x.get_u());
  ASSERT_EQ(4, *x.get_u_x());
  ASSERT_EQ(6, *x.get_u_y());
}
TEST_F(test_df1_two_variable, minus_equal_operator)
{
  df1_two_variable x;
  df1_two_variable y;

  *x.get_u() = 1;
  *x.get_u_x() = 2;
  *x.get_u_y() = 3;
  *y.get_u() = 1;
  *y.get_u_x() = 2;
  *y.get_u_y() = 3;

  x -= y;
  
  ASSERT_EQ(*x.get_u(), value(x));
  ASSERT_EQ(0, *x.get_u());
  ASSERT_EQ(0, *x.get_u_x());
  ASSERT_EQ(0, *x.get_u_y());
}
TEST_F(test_df1_two_variable, plus_equal_double_operator)
{
  df1_two_variable x;
  double y = 5;

  *x.get_u() = 1;
  *x.get_u_x() = 2;
  *x.get_u_y() = 3;

  x += y;
  
  ASSERT_EQ(*x.get_u(), value(x));
  ASSERT_EQ(6, *x.get_u());
  ASSERT_EQ(2, *x.get_u_x());
  ASSERT_EQ(3, *x.get_u_y());
}
TEST_F(test_df1_two_variable, minus_equal_double_operator)
{
  df1_two_variable x;
  double y = 5;

  *x.get_u() = 1;
  *x.get_u_x() = 2;
  *x.get_u_y() = 3;

  x -= y;
  
  ASSERT_EQ(*x.get_u(), value(x));
  ASSERT_EQ(-4, *x.get_u());
  ASSERT_EQ(2, *x.get_u_x());
  ASSERT_EQ(3, *x.get_u_y());
}
