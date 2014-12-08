#include <gtest/gtest.h>

#include <df1b2fun.h>

class test_df3_two_variable: public ::testing::Test {};

/*
TEST_F(test_df3_two_variable, default_constructor)
{
  df3_two_variable v;
  ASSERT_EQ(0, *v.get_u());
  ASSERT_EQ(0, *v.get_u_x());
  ASSERT_EQ(0, *v.get_u_y());
  ASSERT_EQ(0, *v.get_u_xx());
  ASSERT_EQ(0, *v.get_u_xy());
  ASSERT_EQ(0, *v.get_u_yy());
  ASSERT_EQ(0, *v.get_u_xxx());
  ASSERT_EQ(0, *v.get_u_xxy());
  ASSERT_EQ(0, *v.get_u_xyy());
  ASSERT_EQ(0, *v.get_u_yyy());
}
*/
TEST_F(test_df3_two_variable, operator_equal_double)
{
  df3_two_variable v;
  v = 5;
  ASSERT_EQ(5, *v.get_u());
  ASSERT_EQ(0, *v.get_u_x());
  ASSERT_EQ(0, *v.get_u_y());
  ASSERT_EQ(0, *v.get_u_xx());
  ASSERT_EQ(0, *v.get_u_xy());
  ASSERT_EQ(0, *v.get_u_yy());
  ASSERT_EQ(0, *v.get_u_xxx());
  ASSERT_EQ(0, *v.get_u_xxy());
  ASSERT_EQ(0, *v.get_u_xyy());
  ASSERT_EQ(0, *v.get_u_yyy());
}
TEST_F(test_df3_two_variable, operator_equal_df3_two_variable)
{
  df3_two_variable copy;
  copy = 5;
  df3_two_variable v;
  v = copy;
  ASSERT_EQ(5, *v.get_u());
  ASSERT_EQ(0, *v.get_u_x());
  ASSERT_EQ(0, *v.get_u_y());
  ASSERT_EQ(0, *v.get_u_xx());
  ASSERT_EQ(0, *v.get_u_xy());
  ASSERT_EQ(0, *v.get_u_yy());
  ASSERT_EQ(0, *v.get_u_xxx());
  ASSERT_EQ(0, *v.get_u_xxy());
  ASSERT_EQ(0, *v.get_u_xyy());
  ASSERT_EQ(0, *v.get_u_yyy());
}
TEST_F(test_df3_two_variable, copy_constructor)
{
  df3_two_variable copy;
  copy = 5;
  df3_two_variable v(copy);
  ASSERT_EQ(5, *v.get_u());
  ASSERT_EQ(0, *v.get_u_x());
  ASSERT_EQ(0, *v.get_u_y());
  ASSERT_EQ(0, *v.get_u_xx());
  ASSERT_EQ(0, *v.get_u_xy());
  ASSERT_EQ(0, *v.get_u_yy());
  ASSERT_EQ(0, *v.get_u_xxx());
  ASSERT_EQ(0, *v.get_u_xxy());
  ASSERT_EQ(0, *v.get_u_xyy());
  ASSERT_EQ(0, *v.get_u_yyy());
}
TEST_F(test_df3_two_variable, operator_plus_equal_df3_two_variable)
{
  df3_two_variable x;
  x = 5;
  df3_two_variable y;
  y = 2;
  
  x += y;
  
  ASSERT_EQ(7, *x.get_u());
  ASSERT_EQ(0, *x.get_u_x());
  ASSERT_EQ(0, *x.get_u_y());
  ASSERT_EQ(0, *x.get_u_xx());
  ASSERT_EQ(0, *x.get_u_xy());
  ASSERT_EQ(0, *x.get_u_yy());
  ASSERT_EQ(0, *x.get_u_xxx());
  ASSERT_EQ(0, *x.get_u_xxy());
  ASSERT_EQ(0, *x.get_u_xyy());
  ASSERT_EQ(0, *x.get_u_yyy());
}
TEST_F(test_df3_two_variable, operator_plus_equal_double)
{
  df3_two_variable x;
  x = 5;
  double y = 2;
  
  x += y;
  
  ASSERT_EQ(7, *x.get_u());
  ASSERT_EQ(0, *x.get_u_x());
  ASSERT_EQ(0, *x.get_u_y());
  ASSERT_EQ(0, *x.get_u_xx());
  ASSERT_EQ(0, *x.get_u_xy());
  ASSERT_EQ(0, *x.get_u_yy());
  ASSERT_EQ(0, *x.get_u_xxx());
  ASSERT_EQ(0, *x.get_u_xxy());
  ASSERT_EQ(0, *x.get_u_xyy());
  ASSERT_EQ(0, *x.get_u_yyy());
}
TEST_F(test_df3_two_variable, operator_minus_equal_df3_two_variable)
{
  df3_two_variable x;
  x = 5;
  df3_two_variable y;
  y = 2;
  
  x -= y;
  
  ASSERT_EQ(3, *x.get_u());
  ASSERT_EQ(0, *x.get_u_x());
  ASSERT_EQ(0, *x.get_u_y());
  ASSERT_EQ(0, *x.get_u_xx());
  ASSERT_EQ(0, *x.get_u_xy());
  ASSERT_EQ(0, *x.get_u_yy());
  ASSERT_EQ(0, *x.get_u_xxx());
  ASSERT_EQ(0, *x.get_u_xxy());
  ASSERT_EQ(0, *x.get_u_xyy());
  ASSERT_EQ(0, *x.get_u_yyy());
}
TEST_F(test_df3_two_variable, operator_minus_equal_double)
{
  df3_two_variable x;
  x = 5;
  double y = 2;
  
  x -= y;
  
  ASSERT_EQ(3, *x.get_u());
  ASSERT_EQ(0, *x.get_u_x());
  ASSERT_EQ(0, *x.get_u_y());
  ASSERT_EQ(0, *x.get_u_xx());
  ASSERT_EQ(0, *x.get_u_xy());
  ASSERT_EQ(0, *x.get_u_yy());
  ASSERT_EQ(0, *x.get_u_xxx());
  ASSERT_EQ(0, *x.get_u_xxy());
  ASSERT_EQ(0, *x.get_u_xyy());
  ASSERT_EQ(0, *x.get_u_yyy());
}
TEST_F(test_df3_two_variable, operator_multiply_equal_df3_two_variable)
{
  df3_two_variable x;
  x = 5;
  df3_two_variable y;
  y = 2;
  
  x *= y;
  
  ASSERT_EQ(10, *x.get_u());
  ASSERT_EQ(0, *x.get_u_x());
  ASSERT_EQ(0, *x.get_u_y());
  ASSERT_EQ(0, *x.get_u_xx());
  ASSERT_EQ(0, *x.get_u_xy());
  ASSERT_EQ(0, *x.get_u_yy());
  ASSERT_EQ(0, *x.get_u_xxx());
  ASSERT_EQ(0, *x.get_u_xxy());
  ASSERT_EQ(0, *x.get_u_xyy());
  ASSERT_EQ(0, *x.get_u_yyy());
}
TEST_F(test_df3_two_variable, operator_multiply_equal_double)
{
  df3_two_variable x;
  x = 5;
  double y = 2;
  
  x *= y;
  
  ASSERT_EQ(10, *x.get_u());
  ASSERT_EQ(0, *x.get_u_x());
  ASSERT_EQ(0, *x.get_u_y());
  ASSERT_EQ(0, *x.get_u_xx());
  ASSERT_EQ(0, *x.get_u_xy());
  ASSERT_EQ(0, *x.get_u_yy());
  ASSERT_EQ(0, *x.get_u_xxx());
  ASSERT_EQ(0, *x.get_u_xxy());
  ASSERT_EQ(0, *x.get_u_xyy());
  ASSERT_EQ(0, *x.get_u_yyy());
}
TEST_F(test_df3_two_variable, operator_division_equal_df3_two_variable)
{
  df3_two_variable x;
  x = 10;
  df3_two_variable y;
  y = 2;
  
  x /= y;
  
  ASSERT_EQ(5, *x.get_u());
  ASSERT_EQ(0, *x.get_u_x());
  ASSERT_EQ(0, *x.get_u_y());
  ASSERT_EQ(0, *x.get_u_xx());
  ASSERT_EQ(0, *x.get_u_xy());
  ASSERT_EQ(0, *x.get_u_yy());
  ASSERT_EQ(0, *x.get_u_xxx());
  ASSERT_EQ(0, *x.get_u_xxy());
  ASSERT_EQ(0, *x.get_u_xyy());
  ASSERT_EQ(0, *x.get_u_yyy());
}
/*
TEST_F(test_df3_two_variable, operator_division_equal_double)
{
  df3_two_variable x;
  x = 10;
  double y = 2;
  
  x /= y;
  
  ASSERT_EQ(5, *x.get_u());
  ASSERT_EQ(0, *x.get_u_x());
  ASSERT_EQ(0, *x.get_u_y());
  ASSERT_EQ(0, *x.get_u_xx());
  ASSERT_EQ(0, *x.get_u_xy());
  ASSERT_EQ(0, *x.get_u_yy());
  ASSERT_EQ(0, *x.get_u_xxx());
  ASSERT_EQ(0, *x.get_u_xxy());
  ASSERT_EQ(0, *x.get_u_xyy());
  ASSERT_EQ(0, *x.get_u_yyy());
}
*/
TEST_F(test_df3_two_variable, operator_plus_d3_two_variable_d3_two_variable)
{
  df3_two_variable x;
  x = 10;
  df3_two_variable y;
  y = 15;

  df3_two_variable z;
  z = x + y;
  
  ASSERT_EQ(25, value(z));
  ASSERT_EQ(0, *z.get_u_x());
  ASSERT_EQ(0, *z.get_u_y());
  ASSERT_EQ(0, *z.get_u_xx());
  ASSERT_EQ(0, *z.get_u_xy());
  ASSERT_EQ(0, *z.get_u_yy());
  ASSERT_EQ(0, *z.get_u_xxx());
  ASSERT_EQ(0, *z.get_u_xxy());
  ASSERT_EQ(0, *z.get_u_xyy());
  ASSERT_EQ(0, *z.get_u_yyy());
}
TEST_F(test_df3_two_variable, operator_plus_double_d3_two_variable)
{
  double x = 10;
  df3_two_variable y;
  y = 15;

  df3_two_variable z;
  z = x + y;
  
  ASSERT_EQ(25, value(z));
  ASSERT_EQ(0, *z.get_u_x());
  ASSERT_EQ(0, *z.get_u_y());
  ASSERT_EQ(0, *z.get_u_xx());
  ASSERT_EQ(0, *z.get_u_xy());
  ASSERT_EQ(0, *z.get_u_yy());
  ASSERT_EQ(0, *z.get_u_xxx());
  ASSERT_EQ(0, *z.get_u_xxy());
  ASSERT_EQ(0, *z.get_u_xyy());
  ASSERT_EQ(0, *z.get_u_yyy());
}
TEST_F(test_df3_two_variable, operator_plus_d3_two_variable_double)
{
  df3_two_variable x;
  x = 10;
  double y = 15;

  df3_two_variable z;
  z = x + y;
  
  ASSERT_EQ(25, value(z));
  ASSERT_EQ(0, *z.get_u_x());
  ASSERT_EQ(0, *z.get_u_y());
  ASSERT_EQ(0, *z.get_u_xx());
  ASSERT_EQ(0, *z.get_u_xy());
  ASSERT_EQ(0, *z.get_u_yy());
  ASSERT_EQ(0, *z.get_u_xxx());
  ASSERT_EQ(0, *z.get_u_xxy());
  ASSERT_EQ(0, *z.get_u_xyy());
  ASSERT_EQ(0, *z.get_u_yyy());
}
TEST_F(test_df3_two_variable, operator_minus_d3_two_variable_d3_two_variable)
{
  df3_two_variable x;
  x = 10;
  df3_two_variable y;
  y = 15;

  df3_two_variable z;
  z = x - y;
  
  ASSERT_EQ(-5, value(z));
  ASSERT_EQ(0, *z.get_u_x());
  ASSERT_EQ(0, *z.get_u_y());
  ASSERT_EQ(0, *z.get_u_xx());
  ASSERT_EQ(0, *z.get_u_xy());
  ASSERT_EQ(0, *z.get_u_yy());
  ASSERT_EQ(0, *z.get_u_xxx());
  ASSERT_EQ(0, *z.get_u_xxy());
  ASSERT_EQ(0, *z.get_u_xyy());
  ASSERT_EQ(0, *z.get_u_yyy());
}
TEST_F(test_df3_two_variable, operator_minus_double_d3_two_variable)
{
  double x = 10;
  df3_two_variable y;
  y = 15;

  df3_two_variable z;
  z = x - y;
  
  ASSERT_EQ(-5, value(z));
  ASSERT_EQ(0, *z.get_u_x());
  ASSERT_EQ(0, *z.get_u_y());
  ASSERT_EQ(0, *z.get_u_xx());
  ASSERT_EQ(0, *z.get_u_xy());
  ASSERT_EQ(0, *z.get_u_yy());
  ASSERT_EQ(0, *z.get_u_xxx());
  ASSERT_EQ(0, *z.get_u_xxy());
  ASSERT_EQ(0, *z.get_u_xyy());
  ASSERT_EQ(0, *z.get_u_yyy());
}
TEST_F(test_df3_two_variable, operator_minus_d3_two_variable_double)
{
  df3_two_variable x;
  x = 10;
  double y = 15;

  df3_two_variable z;
  z = x - y;
  
  ASSERT_EQ(-5, value(z));
  ASSERT_EQ(0, *z.get_u_x());
  ASSERT_EQ(0, *z.get_u_y());
  ASSERT_EQ(0, *z.get_u_xx());
  ASSERT_EQ(0, *z.get_u_xy());
  ASSERT_EQ(0, *z.get_u_yy());
  ASSERT_EQ(0, *z.get_u_xxx());
  ASSERT_EQ(0, *z.get_u_xxy());
  ASSERT_EQ(0, *z.get_u_xyy());
  ASSERT_EQ(0, *z.get_u_yyy());
}
TEST_F(test_df3_two_variable, operator_multiply_d3_two_variable_d3_two_variable)
{
  df3_two_variable x;
  x = 10;
  df3_two_variable y;
  y = 15;

  df3_two_variable z;
  z = x * y;
  
  ASSERT_EQ(150, value(z));
  ASSERT_EQ(0, *z.get_u_x());
  ASSERT_EQ(0, *z.get_u_y());
  ASSERT_EQ(0, *z.get_u_xx());
  ASSERT_EQ(0, *z.get_u_xy());
  ASSERT_EQ(0, *z.get_u_yy());
  ASSERT_EQ(0, *z.get_u_xxx());
  ASSERT_EQ(0, *z.get_u_xxy());
  ASSERT_EQ(0, *z.get_u_xyy());
  ASSERT_EQ(0, *z.get_u_yyy());
}
TEST_F(test_df3_two_variable, operator_multiply_double_d3_two_variable)
{
  double x = 10;
  df3_two_variable y;
  y = 15;

  df3_two_variable z;
  z = x * y;
  
  ASSERT_EQ(150, value(z));
  ASSERT_EQ(0, *z.get_u_x());
  ASSERT_EQ(0, *z.get_u_y());
  ASSERT_EQ(0, *z.get_u_xx());
  ASSERT_EQ(0, *z.get_u_xy());
  ASSERT_EQ(0, *z.get_u_yy());
  ASSERT_EQ(0, *z.get_u_xxx());
  ASSERT_EQ(0, *z.get_u_xxy());
  ASSERT_EQ(0, *z.get_u_xyy());
  ASSERT_EQ(0, *z.get_u_yyy());
}
TEST_F(test_df3_two_variable, operator_multiply_d3_two_variable_double)
{
  df3_two_variable x;
  x = 10;
  double y = 15;

  df3_two_variable z;
  z = x * y;
  
  ASSERT_EQ(150, value(z));
  ASSERT_EQ(0, *z.get_u_x());
  ASSERT_EQ(0, *z.get_u_y());
  ASSERT_EQ(0, *z.get_u_xx());
  ASSERT_EQ(0, *z.get_u_xy());
  ASSERT_EQ(0, *z.get_u_yy());
  ASSERT_EQ(0, *z.get_u_xxx());
  ASSERT_EQ(0, *z.get_u_xxy());
  ASSERT_EQ(0, *z.get_u_xyy());
  ASSERT_EQ(0, *z.get_u_yyy());
}
TEST_F(test_df3_two_variable, operator_division_d3_two_variable_d3_two_variable)
{
  df3_two_variable x;
  x = 10;
  df3_two_variable y;
  y = 5;

  df3_two_variable z;
  z = x / y;
  
  ASSERT_EQ(2, value(z));
  ASSERT_EQ(0, *z.get_u_x());
  ASSERT_EQ(0, *z.get_u_y());
  ASSERT_EQ(0, *z.get_u_xx());
  ASSERT_EQ(0, *z.get_u_xy());
  ASSERT_EQ(0, *z.get_u_yy());
  ASSERT_EQ(0, *z.get_u_xxx());
  ASSERT_EQ(0, *z.get_u_xxy());
  ASSERT_EQ(0, *z.get_u_xyy());
  ASSERT_EQ(0, *z.get_u_yyy());
}
TEST_F(test_df3_two_variable, operator_division_double_d3_two_variable)
{
  double x = 10;
  df3_two_variable y;
  y = 5;

  df3_two_variable z;
  z = x / y;
  
  ASSERT_EQ(2, value(z));
  ASSERT_EQ(0, *z.get_u_x());
  ASSERT_EQ(0, *z.get_u_y());
  ASSERT_EQ(0, *z.get_u_xx());
  ASSERT_EQ(0, *z.get_u_xy());
  ASSERT_EQ(0, *z.get_u_yy());
  ASSERT_EQ(0, *z.get_u_xxx());
  ASSERT_EQ(0, *z.get_u_xxy());
  ASSERT_EQ(0, *z.get_u_xyy());
  ASSERT_EQ(0, *z.get_u_yyy());
}
TEST_F(test_df3_two_variable, operator_division_d3_two_variable_double)
{
  df3_two_variable x;
  x = 10;
  double y = 5;

  df3_two_variable z;
  z = x / y;
  
  ASSERT_EQ(2, value(z));
  ASSERT_EQ(0, *z.get_u_x());
  ASSERT_EQ(0, *z.get_u_y());
  ASSERT_EQ(0, *z.get_u_xx());
  ASSERT_EQ(0, *z.get_u_xy());
  ASSERT_EQ(0, *z.get_u_yy());
  ASSERT_EQ(0, *z.get_u_xxx());
  ASSERT_EQ(0, *z.get_u_xxy());
  ASSERT_EQ(0, *z.get_u_xyy());
  ASSERT_EQ(0, *z.get_u_yyy());
}
TEST_F(test_df3_two_variable, operator_minus)
{
  df3_two_variable x;
  x = 10;

  df3_two_variable z;
  z = -x;
  
  ASSERT_EQ(-10, value(z));
  ASSERT_EQ(0, *z.get_u_x());
  ASSERT_EQ(0, *z.get_u_y());
  ASSERT_EQ(0, *z.get_u_xx());
  ASSERT_EQ(0, *z.get_u_xy());
  ASSERT_EQ(0, *z.get_u_yy());
  ASSERT_EQ(0, *z.get_u_xxx());
  ASSERT_EQ(0, *z.get_u_xxy());
  ASSERT_EQ(0, *z.get_u_xyy());
  ASSERT_EQ(0, *z.get_u_yyy());
}
