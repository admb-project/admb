#include <gtest/gtest.h>
#include <fvar.hpp>

extern "C"
{
  void test_ad_exit(const int exit_code);
}

class test_dvar_matrix:public ::testing::Test {};

TEST_F(test_dvar_matrix, square_multiplication)
{
  gradient_structure gs;

  dvar_matrix a(1, 2, 1, 2);
  a(1, 1) = 1;
  a(1, 2) = 2;
  a(2, 1) = 3;
  a(2, 2) = 4;

  dmatrix b(1, 2, 1, 2);
  b(1, 1) = 5;
  b(1, 2) = 6;
  b(2, 1) = 7;
  b(2, 2) = 8;
  
  dvar_matrix ab = a * b;
  ASSERT_DOUBLE_EQ(19, value(ab(1, 1)));
  ASSERT_DOUBLE_EQ(22, value(ab(1, 2)));
  ASSERT_DOUBLE_EQ(43, value(ab(2, 1)));
  ASSERT_DOUBLE_EQ(50, value(ab(2, 2)));

  dvar_matrix ba = b * a;
  ASSERT_DOUBLE_EQ(23, value(ba(1, 1)));
  ASSERT_DOUBLE_EQ(34, value(ba(1, 2)));
  ASSERT_DOUBLE_EQ(31, value(ba(2, 1)));
  ASSERT_DOUBLE_EQ(46, value(ba(2, 2)));
}
TEST_F(test_dvar_matrix, multiplication)
{
  gradient_structure gs;

  dvar_matrix a(1, 2, 1, 3);
  a(1, 1) = 1;
  a(1, 2) = 2;
  a(1, 3) = 3;
  a(2, 1) = 4;
  a(2, 2) = 5;
  a(2, 3) = 6;

  dmatrix b(1, 3, 1, 2);
  b(1, 1) = 7;
  b(1, 2) = 8;
  b(2, 1) = 9;
  b(2, 2) = 10;
  b(3, 1) = 11;
  b(3, 2) = 12;
  
  dvar_matrix ab = a * b;
  ASSERT_DOUBLE_EQ(58, value(ab(1, 1)));
  ASSERT_DOUBLE_EQ(64, value(ab(1, 2)));
  ASSERT_DOUBLE_EQ(139, value(ab(2, 1)));
  ASSERT_DOUBLE_EQ(154, value(ab(2, 2)));
}
TEST_F(test_dvar_matrix, incompatiblesize)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;

  dvar_matrix a(1, 6, 1, 6);
  a.initialize();
  dmatrix b;
  ASSERT_ANY_THROW(
    dvar_matrix ab = a * b;
  );
  ASSERT_ANY_THROW(
    dvar_matrix ba = b * a;
  );
}
TEST_F(test_dvar_matrix, mean_nullmatrix)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;

  dvar_matrix a;
  ASSERT_ANY_THROW(
    mean(a);
  );
}
TEST_F(test_dvar_matrix, mean_matrix)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;

  dvar_matrix a(1, 2, 1, 2);
  a(1, 1) = 1;
  a(1, 2) = 1;
  a(2, 1) = 1;
  a(2, 2) = 1;
  dvariable d = mean(a);

  ASSERT_DOUBLE_EQ(1, value(d));
}
TEST_F(test_dvar_matrix, column_vector)
{
  gradient_structure gs;

  dvar_vector v(1, 4);
  v(1) = 4;
  v(2) = 3;
  v(3) = 2;
  v(4) = 1;
  dvar_matrix ret = column_vector(v);
  ASSERT_EQ(1, ret.rowmin());
  ASSERT_EQ(4, ret.rowmax());
  ASSERT_EQ(1, ret(1).indexmin());
  ASSERT_EQ(1, ret(2).indexmin());
  ASSERT_EQ(1, ret(3).indexmin());
  ASSERT_EQ(1, ret(4).indexmin());
  ASSERT_EQ(1, ret(1).indexmax());
  ASSERT_EQ(1, ret(2).indexmax());
  ASSERT_EQ(1, ret(3).indexmax());
  ASSERT_EQ(1, ret(4).indexmax());
  ASSERT_DOUBLE_EQ(4, value(ret(1, 1)));
  ASSERT_DOUBLE_EQ(3, value(ret(2, 1)));
  ASSERT_DOUBLE_EQ(2, value(ret(3, 1)));
  ASSERT_DOUBLE_EQ(1, value(ret(4, 1)));
}
TEST_F(test_dvar_matrix, row_vector)
{
  gradient_structure gs;

  dvar_vector v(1, 4);
  v(1) = 4;
  v(2) = 3;
  v(3) = 2;
  v(4) = 1;
  dvar_matrix ret = row_vector(v);
  ASSERT_EQ(1, ret.rowmin());
  ASSERT_EQ(1, ret.rowmax());
  ASSERT_EQ(1, ret(1).indexmin());
  ASSERT_EQ(4, ret(1).indexmax());
  ASSERT_DOUBLE_EQ(4, value(ret(1, 1)));
  ASSERT_DOUBLE_EQ(3, value(ret(1, 2)));
  ASSERT_DOUBLE_EQ(2, value(ret(1, 3)));
  ASSERT_DOUBLE_EQ(1, value(ret(1, 4)));
}
