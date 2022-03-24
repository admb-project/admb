#include <gtest/gtest.h>

#include <df1b2fun.h>

class test_df3_two_matrix: public ::testing::Test {};

/*
TEST_F(test_df3_two_matrix, default_constructor)
{
  df3_two_matrix x;
  ASSERT_EQ(x.indexmin(), 0);
  ASSERT_EQ(x.indexmax(), -1);
  dmatrix m = value(x);
  ASSERT_EQ(m.rowmin(), 1);
  ASSERT_EQ(m.rowmax(), 0);
}
*/
TEST_F(test_df3_two_matrix, size_constructor)
{
  df3_two_matrix x(1, 5, 1, 2);
  ASSERT_EQ(x.indexmin(), 1);
  ASSERT_EQ(x.indexmax(), 5);
  x.initialize();
  ASSERT_DOUBLE_EQ(0, value(x(1, 1)));
  ASSERT_DOUBLE_EQ(0, value(x(1, 2)));
  ASSERT_DOUBLE_EQ(0, value(x(2, 1)));
  ASSERT_DOUBLE_EQ(0, value(x(2, 2)));
  ASSERT_DOUBLE_EQ(0, value(x(3, 1)));
  ASSERT_DOUBLE_EQ(0, value(x(3, 2)));
  ASSERT_DOUBLE_EQ(0, value(x(4, 1)));
  ASSERT_DOUBLE_EQ(0, value(x(4, 2)));
  ASSERT_DOUBLE_EQ(0, value(x(5, 1)));
  ASSERT_DOUBLE_EQ(0, value(x(5, 2)));
  dmatrix m = value(x);
  ASSERT_EQ(m.rowmin(), 1);
  ASSERT_EQ(m.rowmax(), 5);
  ASSERT_DOUBLE_EQ(0, m(1, 1));
  ASSERT_DOUBLE_EQ(0, m(1, 2));
  ASSERT_DOUBLE_EQ(0, m(2, 1));
  ASSERT_DOUBLE_EQ(0, m(2, 2));
  ASSERT_DOUBLE_EQ(0, m(3, 1));
  ASSERT_DOUBLE_EQ(0, m(3, 2));
  ASSERT_DOUBLE_EQ(0, m(4, 1));
  ASSERT_DOUBLE_EQ(0, m(4, 2));
  ASSERT_DOUBLE_EQ(0, m(5, 1));
  ASSERT_DOUBLE_EQ(0, m(5, 2));

  x.deallocate();
  ASSERT_EQ(x.indexmin(), 0);
  ASSERT_EQ(x.indexmax(), -1);
}
TEST_F(test_df3_two_matrix, copy)
{
  df3_two_matrix x(1, 5, 1, 2);
  df3_two_matrix y(x);

  ASSERT_TRUE(&x[1] == &y(1));
  ASSERT_TRUE(&x[2] == &y(2));
  ASSERT_TRUE(&x[3] == &y(3));
  ASSERT_TRUE(&x[4] == &y(4));
  ASSERT_TRUE(&x[5] == &y(5));
}
