#include <gtest/gtest.h>
#include <df1b2fun.h>
#include <df33fun.h>

class test_df3_three_variable: public ::testing::Test {};

TEST_F(test_df3_three_variable, default_constructor)
{
  df3_three_variable x;
  ASSERT_DOUBLE_EQ(*x.get_u(), 0);
  ASSERT_DOUBLE_EQ(*x.get_u_x(), 0);
  ASSERT_DOUBLE_EQ(*x.get_u_y(), 0);
  ASSERT_DOUBLE_EQ(*x.get_u_z(), 0);
  ASSERT_DOUBLE_EQ(*x.get_u_xx(), 0);
  ASSERT_DOUBLE_EQ(*x.get_u_xy(), 0);
  ASSERT_DOUBLE_EQ(*x.get_u_xz(), 0);
  ASSERT_DOUBLE_EQ(*x.get_u_yy(), 0);
  ASSERT_DOUBLE_EQ(*x.get_u_yz(), 0);
  ASSERT_DOUBLE_EQ(*x.get_u_zz(), 0);
  ASSERT_DOUBLE_EQ(*x.get_u_xxx(), 0);
  ASSERT_DOUBLE_EQ(*x.get_u_xxy(), 0);
  ASSERT_DOUBLE_EQ(*x.get_u_xxz(), 0);
  ASSERT_DOUBLE_EQ(*x.get_u_xyy(), 0);
  ASSERT_DOUBLE_EQ(*x.get_u_xyz(), 0);
  ASSERT_DOUBLE_EQ(*x.get_u_xzz(), 0);
  ASSERT_DOUBLE_EQ(*x.get_u_yyy(), 0);
  ASSERT_DOUBLE_EQ(*x.get_u_yyz(), 0);
  ASSERT_DOUBLE_EQ(*x.get_u_yzz(), 0);
  ASSERT_DOUBLE_EQ(*x.get_u_zzz(), 0);
}
