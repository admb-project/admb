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
