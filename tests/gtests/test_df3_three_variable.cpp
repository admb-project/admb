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
TEST_F(test_df3_three_variable, minus_equal_df3_three_variable)
{
  df3_three_variable y;
  *y.get_u() = 1;
  *y.get_u_x() = 2;
  *y.get_u_y() = 3;
  *y.get_u_z() = 4;
  *y.get_u_xx() = 5;
  *y.get_u_xy() = 6;
  *y.get_u_xz() = 7;
  *y.get_u_yy() = 8;
  *y.get_u_yz() = 9;
  *y.get_u_zz() = 10;
  *y.get_u_xxx() = 11;
  *y.get_u_xxy() = 12;
  *y.get_u_xxz() = 13;
  *y.get_u_xyy() = 14;
  *y.get_u_xyz() = 15;
  *y.get_u_xzz() = 16;
  *y.get_u_yyy() = 17;
  *y.get_u_yyz() = 18;
  *y.get_u_yzz() = 19;
  *y.get_u_zzz() = 20;

  df3_three_variable x;
  x -= y;
  ASSERT_DOUBLE_EQ(*x.get_u(), -1);
  ASSERT_DOUBLE_EQ(*x.get_u_x(), -2);
  ASSERT_DOUBLE_EQ(*x.get_u_y(), -3);
  ASSERT_DOUBLE_EQ(*x.get_u_z(), -4);
  ASSERT_DOUBLE_EQ(*x.get_u_xx(), -5);
  ASSERT_DOUBLE_EQ(*x.get_u_xy(), -6);
  ASSERT_DOUBLE_EQ(*x.get_u_xz(), -7);
  ASSERT_DOUBLE_EQ(*x.get_u_yy(), -8);
  ASSERT_DOUBLE_EQ(*x.get_u_yz(), -9);
  ASSERT_DOUBLE_EQ(*x.get_u_zz(), -10);
  ASSERT_DOUBLE_EQ(*x.get_u_xxx(), -11);
  ASSERT_DOUBLE_EQ(*x.get_u_xxy(), -12);
  ASSERT_DOUBLE_EQ(*x.get_u_xxz(), -13);
  ASSERT_DOUBLE_EQ(*x.get_u_xyy(), -14);
  ASSERT_DOUBLE_EQ(*x.get_u_xyz(), -15);
  ASSERT_DOUBLE_EQ(*x.get_u_xzz(), -16);
  ASSERT_DOUBLE_EQ(*x.get_u_yyy(), -17);
  ASSERT_DOUBLE_EQ(*x.get_u_yyz(), -18);
  ASSERT_DOUBLE_EQ(*x.get_u_yzz(), -19);
  ASSERT_DOUBLE_EQ(*x.get_u_zzz(), -20);
}
TEST_F(test_df3_three_variable, minus_equal_double)
{
  df3_three_variable x;
  *x.get_u() = 1;
  *x.get_u_x() = 2;
  *x.get_u_y() = 3;
  *x.get_u_z() = 4;
  *x.get_u_xx() = 5;
  *x.get_u_xy() = 6;
  *x.get_u_xz() = 7;
  *x.get_u_yy() = 8;
  *x.get_u_yz() = 9;
  *x.get_u_zz() = 10;
  *x.get_u_xxx() = 11;
  *x.get_u_xxy() = 12;
  *x.get_u_xxz() = 13;
  *x.get_u_xyy() = 14;
  *x.get_u_xyz() = 15;
  *x.get_u_xzz() = 16;
  *x.get_u_yyy() = 17;
  *x.get_u_yyz() = 18;
  *x.get_u_yzz() = 19;
  *x.get_u_zzz() = 20;

  double y = 5;
  x -= y;
  ASSERT_DOUBLE_EQ(*x.get_u(), -4);
  ASSERT_DOUBLE_EQ(*x.get_u_x(), 2);
  ASSERT_DOUBLE_EQ(*x.get_u_y(), 3);
  ASSERT_DOUBLE_EQ(*x.get_u_z(), 4);
  ASSERT_DOUBLE_EQ(*x.get_u_xx(), 5);
  ASSERT_DOUBLE_EQ(*x.get_u_xy(), 6);
  ASSERT_DOUBLE_EQ(*x.get_u_xz(), 7);
  ASSERT_DOUBLE_EQ(*x.get_u_yy(), 8);
  ASSERT_DOUBLE_EQ(*x.get_u_yz(), 9);
  ASSERT_DOUBLE_EQ(*x.get_u_zz(), 10);
  ASSERT_DOUBLE_EQ(*x.get_u_xxx(), 11);
  ASSERT_DOUBLE_EQ(*x.get_u_xxy(), 12);
  ASSERT_DOUBLE_EQ(*x.get_u_xxz(), 13);
  ASSERT_DOUBLE_EQ(*x.get_u_xyy(), 14);
  ASSERT_DOUBLE_EQ(*x.get_u_xyz(), 15);
  ASSERT_DOUBLE_EQ(*x.get_u_xzz(), 16);
  ASSERT_DOUBLE_EQ(*x.get_u_yyy(), 17);
  ASSERT_DOUBLE_EQ(*x.get_u_yyz(), 18);
  ASSERT_DOUBLE_EQ(*x.get_u_yzz(), 19);
  ASSERT_DOUBLE_EQ(*x.get_u_zzz(), 20);
}
TEST_F(test_df3_three_variable, plus_equal_double)
{
  df3_three_variable x;
  *x.get_u() = 1;
  *x.get_u_x() = 2;
  *x.get_u_y() = 3;
  *x.get_u_z() = 4;
  *x.get_u_xx() = 5;
  *x.get_u_xy() = 6;
  *x.get_u_xz() = 7;
  *x.get_u_yy() = 8;
  *x.get_u_yz() = 9;
  *x.get_u_zz() = 10;
  *x.get_u_xxx() = 11;
  *x.get_u_xxy() = 12;
  *x.get_u_xxz() = 13;
  *x.get_u_xyy() = 14;
  *x.get_u_xyz() = 15;
  *x.get_u_xzz() = 16;
  *x.get_u_yyy() = 17;
  *x.get_u_yyz() = 18;
  *x.get_u_yzz() = 19;
  *x.get_u_zzz() = 20;

  double y = 5;
  x += y;
  ASSERT_DOUBLE_EQ(*x.get_u(), 6);
  ASSERT_DOUBLE_EQ(*x.get_u_x(), 2);
  ASSERT_DOUBLE_EQ(*x.get_u_y(), 3);
  ASSERT_DOUBLE_EQ(*x.get_u_z(), 4);
  ASSERT_DOUBLE_EQ(*x.get_u_xx(), 5);
  ASSERT_DOUBLE_EQ(*x.get_u_xy(), 6);
  ASSERT_DOUBLE_EQ(*x.get_u_xz(), 7);
  ASSERT_DOUBLE_EQ(*x.get_u_yy(), 8);
  ASSERT_DOUBLE_EQ(*x.get_u_yz(), 9);
  ASSERT_DOUBLE_EQ(*x.get_u_zz(), 10);
  ASSERT_DOUBLE_EQ(*x.get_u_xxx(), 11);
  ASSERT_DOUBLE_EQ(*x.get_u_xxy(), 12);
  ASSERT_DOUBLE_EQ(*x.get_u_xxz(), 13);
  ASSERT_DOUBLE_EQ(*x.get_u_xyy(), 14);
  ASSERT_DOUBLE_EQ(*x.get_u_xyz(), 15);
  ASSERT_DOUBLE_EQ(*x.get_u_xzz(), 16);
  ASSERT_DOUBLE_EQ(*x.get_u_yyy(), 17);
  ASSERT_DOUBLE_EQ(*x.get_u_yyz(), 18);
  ASSERT_DOUBLE_EQ(*x.get_u_yzz(), 19);
  ASSERT_DOUBLE_EQ(*x.get_u_zzz(), 20);
}
TEST_F(test_df3_three_variable, add_equal_df3_three_variable)
{
  df3_three_variable y;
  *y.get_u() = 1;
  *y.get_u_x() = 2;
  *y.get_u_y() = 3;
  *y.get_u_z() = 4;
  *y.get_u_xx() = 5;
  *y.get_u_xy() = 6;
  *y.get_u_xz() = 7;
  *y.get_u_yy() = 8;
  *y.get_u_yz() = 9;
  *y.get_u_zz() = 10;
  *y.get_u_xxx() = 11;
  *y.get_u_xxy() = 12;
  *y.get_u_xxz() = 13;
  *y.get_u_xyy() = 14;
  *y.get_u_xyz() = 15;
  *y.get_u_xzz() = 16;
  *y.get_u_yyy() = 17;
  *y.get_u_yyz() = 18;
  *y.get_u_yzz() = 19;
  *y.get_u_zzz() = 20;

  df3_three_variable x;
  x += y;
  ASSERT_DOUBLE_EQ(*x.get_u(), 1);
  ASSERT_DOUBLE_EQ(*x.get_u_x(), 2);
  ASSERT_DOUBLE_EQ(*x.get_u_y(), 3);
  ASSERT_DOUBLE_EQ(*x.get_u_z(), 4);
  ASSERT_DOUBLE_EQ(*x.get_u_xx(), 5);
  ASSERT_DOUBLE_EQ(*x.get_u_xy(), 6);
  ASSERT_DOUBLE_EQ(*x.get_u_xz(), 7);
  ASSERT_DOUBLE_EQ(*x.get_u_yy(), 8);
  ASSERT_DOUBLE_EQ(*x.get_u_yz(), 9);
  ASSERT_DOUBLE_EQ(*x.get_u_zz(), 10);
  ASSERT_DOUBLE_EQ(*x.get_u_xxx(), 11);
  ASSERT_DOUBLE_EQ(*x.get_u_xxy(), 12);
  ASSERT_DOUBLE_EQ(*x.get_u_xxz(), 13);
  ASSERT_DOUBLE_EQ(*x.get_u_xyy(), 14);
  ASSERT_DOUBLE_EQ(*x.get_u_xyz(), 15);
  ASSERT_DOUBLE_EQ(*x.get_u_xzz(), 16);
  ASSERT_DOUBLE_EQ(*x.get_u_yyy(), 17);
  ASSERT_DOUBLE_EQ(*x.get_u_yyz(), 18);
  ASSERT_DOUBLE_EQ(*x.get_u_yzz(), 19);
  ASSERT_DOUBLE_EQ(*x.get_u_zzz(), 20);
}
TEST_F(test_df3_three_variable, muliplication_equal_double)
{
  df3_three_variable y;
  *y.get_u() = 1;
  *y.get_u_x() = 2;
  *y.get_u_y() = 3;
  *y.get_u_z() = 4;
  *y.get_u_xx() = 5;
  *y.get_u_xy() = 6;
  *y.get_u_xz() = 7;
  *y.get_u_yy() = 8;
  *y.get_u_yz() = 9;
  *y.get_u_zz() = 10;
  *y.get_u_xxx() = 11;
  *y.get_u_xxy() = 12;
  *y.get_u_xxz() = 13;
  *y.get_u_xyy() = 14;
  *y.get_u_xyz() = 15;
  *y.get_u_xzz() = 16;
  *y.get_u_yyy() = 17;
  *y.get_u_yyz() = 18;
  *y.get_u_yzz() = 19;
  *y.get_u_zzz() = 20;

  double x = 2;
  y *= x;
  ASSERT_DOUBLE_EQ(*y.get_u(), 2);
  ASSERT_DOUBLE_EQ(*y.get_u_x(), 4);
  ASSERT_DOUBLE_EQ(*y.get_u_y(), 6);
  ASSERT_DOUBLE_EQ(*y.get_u_z(), 8);
  ASSERT_DOUBLE_EQ(*y.get_u_xx(), 10);
  ASSERT_DOUBLE_EQ(*y.get_u_xy(), 12);
  ASSERT_DOUBLE_EQ(*y.get_u_xz(), 14);
  ASSERT_DOUBLE_EQ(*y.get_u_yy(), 16);
  ASSERT_DOUBLE_EQ(*y.get_u_yz(), 18);
  ASSERT_DOUBLE_EQ(*y.get_u_zz(), 20);
  ASSERT_DOUBLE_EQ(*y.get_u_xxx(), 22);
  ASSERT_DOUBLE_EQ(*y.get_u_xxy(), 24);
  ASSERT_DOUBLE_EQ(*y.get_u_xxz(), 26);
  ASSERT_DOUBLE_EQ(*y.get_u_xyy(), 28);
  ASSERT_DOUBLE_EQ(*y.get_u_xyz(), 30);
  ASSERT_DOUBLE_EQ(*y.get_u_xzz(), 32);
  ASSERT_DOUBLE_EQ(*y.get_u_yyy(), 34);
  ASSERT_DOUBLE_EQ(*y.get_u_yyz(), 36);
  ASSERT_DOUBLE_EQ(*y.get_u_yzz(), 38);
  ASSERT_DOUBLE_EQ(*y.get_u_zzz(), 40);
}
/*
TEST_F(test_df3_three_variable, multiply_equal_df3_three_variable)
{
  df3_three_variable y;
  *y.get_u() = 1;
  *y.get_u_x() = 2;
  *y.get_u_y() = 3;
  *y.get_u_z() = 4;
  *y.get_u_xx() = 5;
  *y.get_u_xy() = 6;
  *y.get_u_xz() = 7;
  *y.get_u_yy() = 8;
  *y.get_u_yz() = 9;
  *y.get_u_zz() = 10;
  *y.get_u_xxx() = 11;
  *y.get_u_xxy() = 12;
  *y.get_u_xxz() = 13;
  *y.get_u_xyy() = 14;
  *y.get_u_xyz() = 15;
  *y.get_u_xzz() = 16;
  *y.get_u_yyy() = 17;
  *y.get_u_yyz() = 18;
  *y.get_u_yzz() = 19;
  *y.get_u_zzz() = 20;

  df3_three_variable x;
  *x.get_u() = 2;
  *x.get_u_x() = 2;
  *x.get_u_y() = 2;
  *x.get_u_z() = 2;
  *x.get_u_xx() = 2;
  *x.get_u_xy() = 2;
  *x.get_u_xz() = 2;
  *x.get_u_yy() = 2;
  *x.get_u_yz() = 2;
  *x.get_u_zz() = 2;
  *x.get_u_xxx() = 2;
  *x.get_u_xxy() = 2;
  *x.get_u_xxz() = 2;
  *x.get_u_xyy() = 2;
  *x.get_u_xyz() = 2;
  *x.get_u_xzz() = 2;
  *x.get_u_yyy() = 2;
  *x.get_u_yyz() = 2;
  *x.get_u_yzz() = 2;
  *x.get_u_zzz() = 2;
  y *= x;
  ASSERT_DOUBLE_EQ(*y.get_u(), 2);
  ASSERT_DOUBLE_EQ(*y.get_u_x(), 4);
  ASSERT_DOUBLE_EQ(*y.get_u_y(), 6);
  ASSERT_DOUBLE_EQ(*y.get_u_z(), 8);
  ASSERT_DOUBLE_EQ(*y.get_u_xx(), 10);
  ASSERT_DOUBLE_EQ(*y.get_u_xy(), 12);
  ASSERT_DOUBLE_EQ(*y.get_u_xz(), 14);
  ASSERT_DOUBLE_EQ(*y.get_u_yy(), 16);
  ASSERT_DOUBLE_EQ(*y.get_u_yz(), 18);
  ASSERT_DOUBLE_EQ(*y.get_u_zz(), 20);
  ASSERT_DOUBLE_EQ(*y.get_u_xxx(), 22);
  ASSERT_DOUBLE_EQ(*y.get_u_xxy(), 24);
  ASSERT_DOUBLE_EQ(*y.get_u_xxz(), 26);
  ASSERT_DOUBLE_EQ(*y.get_u_xyy(), 28);
  ASSERT_DOUBLE_EQ(*y.get_u_xyz(), 30);
  ASSERT_DOUBLE_EQ(*y.get_u_xzz(), 32);
  ASSERT_DOUBLE_EQ(*y.get_u_yyy(), 34);
  ASSERT_DOUBLE_EQ(*y.get_u_yyz(), 36);
  ASSERT_DOUBLE_EQ(*y.get_u_yzz(), 38);
  ASSERT_DOUBLE_EQ(*y.get_u_zzz(), 40);
}
*/
TEST_F(test_df3_three_variable, assignment_operator)
{
  df3_three_variable y;
  *y.get_u() = 1;
  *y.get_u_x() = 2;
  *y.get_u_y() = 3;
  *y.get_u_z() = 4;
  *y.get_u_xx() = 5;
  *y.get_u_xy() = 6;
  *y.get_u_xz() = 7;
  *y.get_u_yy() = 8;
  *y.get_u_yz() = 9;
  *y.get_u_zz() = 10;
  *y.get_u_xxx() = 11;
  *y.get_u_xxy() = 12;
  *y.get_u_xxz() = 13;
  *y.get_u_xyy() = 14;
  *y.get_u_xyz() = 15;
  *y.get_u_xzz() = 16;
  *y.get_u_yyy() = 17;
  *y.get_u_yyz() = 18;
  *y.get_u_yzz() = 19;
  *y.get_u_zzz() = 20;

  df3_three_variable x;
  x = y;
  ASSERT_DOUBLE_EQ(*x.get_u(), 1);
  ASSERT_DOUBLE_EQ(*x.get_u_x(), 2);
  ASSERT_DOUBLE_EQ(*x.get_u_y(), 3);
  ASSERT_DOUBLE_EQ(*x.get_u_z(), 4);
  ASSERT_DOUBLE_EQ(*x.get_u_xx(), 5);
  ASSERT_DOUBLE_EQ(*x.get_u_xy(), 6);
  ASSERT_DOUBLE_EQ(*x.get_u_xz(), 7);
  ASSERT_DOUBLE_EQ(*x.get_u_yy(), 8);
  ASSERT_DOUBLE_EQ(*x.get_u_yz(), 9);
  ASSERT_DOUBLE_EQ(*x.get_u_zz(), 10);
  ASSERT_DOUBLE_EQ(*x.get_u_xxx(), 11);
  ASSERT_DOUBLE_EQ(*x.get_u_xxy(), 12);
  ASSERT_DOUBLE_EQ(*x.get_u_xxz(), 13);
  ASSERT_DOUBLE_EQ(*x.get_u_xyy(), 14);
  ASSERT_DOUBLE_EQ(*x.get_u_xyz(), 15);
  ASSERT_DOUBLE_EQ(*x.get_u_xzz(), 16);
  ASSERT_DOUBLE_EQ(*x.get_u_yyy(), 17);
  ASSERT_DOUBLE_EQ(*x.get_u_yyz(), 18);
  ASSERT_DOUBLE_EQ(*x.get_u_yzz(), 19);
  ASSERT_DOUBLE_EQ(*x.get_u_zzz(), 20);
}
