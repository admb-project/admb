#include <gtest/gtest.h>
#include <df1b2fun.h>

class test_df3_one_variable: public ::testing::Test {};

TEST_F(test_df3_one_variable, default_constructor)
{
  df3_one_variable x;

  ASSERT_DOUBLE_EQ(*x.get_u(), 0);
  ASSERT_DOUBLE_EQ(*x.get_udot(), 0);
  ASSERT_DOUBLE_EQ(*x.get_udot2(), 0);
  ASSERT_DOUBLE_EQ(*x.get_udot3(), 0);
}
TEST_F(test_df3_one_variable, equal_minus_double)
{
  df3_one_variable x;

  double d = -6.5;
  x -= d;

  ASSERT_DOUBLE_EQ(*x.get_u(), 6.5);
  ASSERT_DOUBLE_EQ(*x.get_udot(), 0);
  ASSERT_DOUBLE_EQ(*x.get_udot2(), 0);
  ASSERT_DOUBLE_EQ(*x.get_udot3(), 0);
}
TEST_F(test_df3_one_variable, equal_minus_df3_one_variable)
{
  df3_one_variable x;
  *x.get_u() = -1;
  *x.get_udot() = 1;
  *x.get_udot2() = 2;
  *x.get_udot3() = 3;
  df3_one_variable y;
  *y.get_u() = 1;
  *y.get_udot() = -1;
  *y.get_udot2() = -2;
  *y.get_udot3() = -3;
  x -= y;

  ASSERT_DOUBLE_EQ(*x.get_u(), -2);
  ASSERT_DOUBLE_EQ(*x.get_udot(), 2);
  ASSERT_DOUBLE_EQ(*x.get_udot2(), 4);
  ASSERT_DOUBLE_EQ(*x.get_udot3(), 6);
}
TEST_F(test_df3_one_variable, equal_add_df3_one_variable)
{
  df3_one_variable x;
  *x.get_u() = 1;
  *x.get_udot() = 1;
  *x.get_udot2() = 2;
  *x.get_udot3() = 3;
  df3_one_variable y;
  *y.get_u() = 1;
  *y.get_udot() = 1;
  *y.get_udot2() = 2;
  *y.get_udot3() = 3;
  x += y;

  ASSERT_DOUBLE_EQ(*x.get_u(), 2);
  ASSERT_DOUBLE_EQ(*x.get_udot(), 2);
  ASSERT_DOUBLE_EQ(*x.get_udot2(), 4);
  ASSERT_DOUBLE_EQ(*x.get_udot3(), 6);
}
