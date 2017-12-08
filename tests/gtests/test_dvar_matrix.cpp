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
TEST_F(test_dvar_matrix, fill)
{
  gradient_structure gs;

  //2 x 2 matrix
  dvar_matrix ret(1, 2, 1, 2);
  ret.fill("{1,2}{3,4}");
  ASSERT_DOUBLE_EQ(1, value(ret(1, 1)));
  ASSERT_DOUBLE_EQ(2, value(ret(1, 2)));
  ASSERT_DOUBLE_EQ(3, value(ret(2, 1)));
  ASSERT_DOUBLE_EQ(4, value(ret(2, 2)));
}
TEST_F(test_dvar_matrix, extract_diagonal)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;

  dvar_matrix a(1, 3, 1, 3);
  a(1, 1) = 1;
  a(1, 2) = 2;
  a(1, 3) = 3;
  a(2, 1) = 4;
  a(2, 2) = 5;
  a(2, 3) = 6;
  a(3, 1) = 7;
  a(3, 2) = 8;
  a(3, 3) = 9;

  dvar_vector extract_diagonal(const dvar_matrix& m);

  dvar_vector result = extract_diagonal(a);

  ASSERT_TRUE(result.indexmin() == 1);
  ASSERT_TRUE(result.indexmax() == 3);

  ASSERT_DOUBLE_EQ(1, value(result(1)));
  ASSERT_DOUBLE_EQ(5, value(result(2)));
  ASSERT_DOUBLE_EQ(9, value(result(3)));
}
TEST_F(test_dvar_matrix, extract_diagonal_not_square)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;

  dvar_matrix a(1, 3, 1, 2);
  a(1, 1) = 1;
  a(1, 2) = 2;
  a(2, 1) = 4;
  a(2, 2) = 5;
  a(3, 1) = 4;
  a(3, 2) = 5;

  dvar_vector extract_diagonal(const dvar_matrix& m);
  ASSERT_THROW(extract_diagonal(a), int);
}
TEST_F(test_dvar_matrix, negativeoperator)
{
  gradient_structure gs;

  dvar_matrix a(1, 2, 1, 2);
  a(1, 1) = 1;
  a(1, 2) = 2;
  a(2, 1) = 3;
  a(2, 2) = 4;

  dvar_matrix a2 = -a;
  ASSERT_DOUBLE_EQ(-1, value(a2(1, 1)));
  ASSERT_DOUBLE_EQ(-2, value(a2(1, 2)));
  ASSERT_DOUBLE_EQ(-3, value(a2(2, 1)));
  ASSERT_DOUBLE_EQ(-4, value(a2(2, 2)));
}
TEST_F(test_dvar_matrix, empty)
{
  gradient_structure gs;

  dvar_matrix a;
  a.allocate(1, 0);

  ASSERT_EQ(1, a.rowmin());
  ASSERT_EQ(0, a.rowmax());
  ASSERT_EQ(0, a.rowsize());
  ASSERT_FALSE(allocated(a));
}
TEST_F(test_dvar_matrix, empty2)
{
  gradient_structure gs;

  dvar_matrix a;

  ASSERT_EQ(1, a.rowmin());
  ASSERT_EQ(0, a.rowmax());
  ASSERT_EQ(0, a.rowsize());
  ASSERT_FALSE(allocated(a));
}
TEST_F(test_dvar_matrix, emptycolumns)
{
  gradient_structure gs;

  dvar_matrix a;
  a.allocate(1, 3);

  ASSERT_EQ(1, a.rowmin());
  ASSERT_EQ(3, a.rowmax());
  ASSERT_TRUE(allocated(a));
  ASSERT_TRUE(sub_unallocated(a));
  ASSERT_FALSE(allocated(a(1)));
  ASSERT_FALSE(allocated(a(2)));
  ASSERT_FALSE(allocated(a(3)));
}
TEST_F(test_dvar_matrix, ad_integeremptycolumns)
{
  gradient_structure gs;

  dvar_matrix a;
  ad_integer min = 1;
  ad_integer max = 3;
  a.allocate(min, max);

  ASSERT_EQ(1, a.rowmin());
  ASSERT_EQ(3, a.rowmax());
  ASSERT_TRUE(allocated(a));
  ASSERT_TRUE(sub_unallocated(a));
  ASSERT_FALSE(allocated(a(1)));
  ASSERT_FALSE(allocated(a(2)));
  ASSERT_FALSE(allocated(a(3)));
}
TEST_F(test_dvar_matrix, allocate4xint)
{
  gradient_structure gs;

  dvar_matrix a;
  a.allocate(1, 3, 1, 4);

  ASSERT_EQ(1, a.rowmin());
  ASSERT_EQ(3, a.rowmax());
  ASSERT_EQ(1, a.colmin());
  ASSERT_EQ(4, a.colmax());
  ASSERT_TRUE(allocated(a));
  ASSERT_FALSE(sub_unallocated(a));
  ASSERT_TRUE(allocated(a(1)));
  ASSERT_TRUE(allocated(a(2)));
  ASSERT_TRUE(allocated(a(3)));
}
TEST_F(test_dvar_matrix, allocatecolsmax)
{
  gradient_structure gs;

  ivector colsmax(1, 3);
  colsmax(1) = 4;
  colsmax(2) = 5;
  colsmax(3) = 6;
  dvar_matrix a;
  a.allocate(1, 3, 2, colsmax);
  ASSERT_EQ(1, a.rowmin());
  ASSERT_EQ(3, a.rowmax());
  ASSERT_EQ(2, a(1).indexmin());
  ASSERT_EQ(colsmax(1), a(1).indexmax());
  ASSERT_EQ(2, a(2).indexmin());
  ASSERT_EQ(colsmax(2), a(2).indexmax());
  ASSERT_EQ(2, a(3).indexmin());
  ASSERT_EQ(colsmax(3), a(3).indexmax());
}
TEST_F(test_dvar_matrix, emptyequalempty)
{
  dvar_matrix a;
  dmatrix b;

  a = b;
  ASSERT_EQ(1, a.rowmin());
  ASSERT_EQ(0, a.rowmax());
  ASSERT_FALSE(allocated(a));
}
TEST_F(test_dvar_matrix, deallocatecopies)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;

  dvar_matrix a(1, 2, 1, 2);
  ASSERT_EQ(0, a.get_ncopies());
  dvar_matrix firstcopy(a);
  ASSERT_EQ(1, a.get_ncopies());
  ASSERT_EQ(1, firstcopy.get_ncopies());
  dvar_matrix secondcopy(a);
  ASSERT_EQ(2, a.get_ncopies());
  ASSERT_EQ(2, firstcopy.get_ncopies());
  ASSERT_EQ(2, secondcopy.get_ncopies());

  firstcopy.deallocate();
  ASSERT_EQ(1, a.get_ncopies());
  ASSERT_EQ(0, firstcopy.get_ncopies());
  ASSERT_EQ(1, secondcopy.get_ncopies());

  secondcopy.deallocate();
  ASSERT_EQ(0, a.get_ncopies());
  ASSERT_EQ(0, firstcopy.get_ncopies());
  ASSERT_EQ(0, secondcopy.get_ncopies());
}
