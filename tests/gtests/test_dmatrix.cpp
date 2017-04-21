#include <gtest/gtest.h>
#include <fvar.hpp>
#include <climits>

extern "C"
{
  void test_ad_exit(const int exit_code);
}

class test_dmatrix: public ::testing::Test {};

TEST_F(test_dmatrix, fill)
{
  dmatrix m(1, 2, 1, 3);

  char array[] = "{0, 1, 2} {3, 4, 5}";

  m.fill(array);

  ASSERT_DOUBLE_EQ(0, m(1, 1));
  ASSERT_DOUBLE_EQ(1, m(1, 2));
  ASSERT_DOUBLE_EQ(2, m(1, 3));
  ASSERT_DOUBLE_EQ(3, m(2, 1));
  ASSERT_DOUBLE_EQ(4, m(2, 2));
  ASSERT_DOUBLE_EQ(5, m(2, 3));
}
TEST_F(test_dmatrix, rowshift)
{
  char array[] = "{1, 2, 3, 4} {5, 6, 7, 8} {9, 10, 11, 12} {13, 14, 15, 16}";
  dmatrix m(1, 4, 1, 4);
  m.fill(array);
  ASSERT_DOUBLE_EQ(1, m(1, 1));
  ASSERT_DOUBLE_EQ(2, m(1, 2));
  ASSERT_DOUBLE_EQ(3, m(1, 3));
  ASSERT_DOUBLE_EQ(4, m(1, 4));
  ASSERT_DOUBLE_EQ(5, m(2, 1));
  ASSERT_DOUBLE_EQ(6, m(2, 2));
  ASSERT_DOUBLE_EQ(7, m(2, 3));
  ASSERT_DOUBLE_EQ(8, m(2, 4));
  ASSERT_DOUBLE_EQ(9, m(3, 1));
  ASSERT_DOUBLE_EQ(10, m(3, 2));
  ASSERT_DOUBLE_EQ(11, m(3, 3));
  ASSERT_DOUBLE_EQ(12, m(3, 4));
  ASSERT_DOUBLE_EQ(13, m(4, 1));
  ASSERT_DOUBLE_EQ(14, m(4, 2));
  ASSERT_DOUBLE_EQ(15, m(4, 3));
  ASSERT_DOUBLE_EQ(16, m(4, 4));
  ASSERT_EQ(1, m.indexmin());
  ASSERT_EQ(4, m.indexmax());
  m.rowshift(2);
  ASSERT_EQ(2, m.indexmin());
  ASSERT_EQ(5, m.indexmax());
  ASSERT_DOUBLE_EQ(1, m(2, 1));
  ASSERT_DOUBLE_EQ(2, m(2, 2));
  ASSERT_DOUBLE_EQ(3, m(2, 3));
  ASSERT_DOUBLE_EQ(4, m(2, 4));
  ASSERT_DOUBLE_EQ(5, m(3, 1));
  ASSERT_DOUBLE_EQ(6, m(3, 2));
  ASSERT_DOUBLE_EQ(7, m(3, 3));
  ASSERT_DOUBLE_EQ(8, m(3, 4));
  ASSERT_DOUBLE_EQ(9, m(4, 1));
  ASSERT_DOUBLE_EQ(10, m(4, 2));
  ASSERT_DOUBLE_EQ(11, m(4, 3));
  ASSERT_DOUBLE_EQ(12, m(4, 4));
  ASSERT_DOUBLE_EQ(13, m(5, 1));
  ASSERT_DOUBLE_EQ(14, m(5, 2));
  ASSERT_DOUBLE_EQ(15, m(5, 3));
  ASSERT_DOUBLE_EQ(16, m(5, 4));
}
TEST_F(test_dmatrix, fill_constructor)
{
  char array[] = "{0, 1, 2} {3, 4, 5}";
  dmatrix m(array);

  ASSERT_DOUBLE_EQ(0, m(1, 1));
  ASSERT_DOUBLE_EQ(1, m(1, 2));
  ASSERT_DOUBLE_EQ(2, m(1, 3));
  ASSERT_DOUBLE_EQ(3, m(2, 1));
  ASSERT_DOUBLE_EQ(4, m(2, 2));
  ASSERT_DOUBLE_EQ(5, m(2, 3));
}
TEST_F(test_dmatrix, fill_extrabraces)
{
  ad_exit=&test_ad_exit;

  dmatrix m(1, 2, 1, 3);

  char array[] = "{{0, 1, 2} {3, 4, 5}}";

  try
  {
    m.fill(array);
  }
  catch (const int exit_code)
  {
    const int expected_exit_code = 1;
    if (exit_code == expected_exit_code)
    {
      return;
    }
  }
  FAIL();
}
#ifndef OPT_LIB
TEST_F(test_dmatrix, fill_unallocated)
{
  ad_exit=&test_ad_exit;

  dmatrix m;

  char array[] = "{0, 1, 2} {3, 4, 5}";

  try
  {
    m.fill(array);
  }
  catch (const int exit_code)
  {
    const int expected_exit_code = 22;
    if (exit_code == expected_exit_code)
    {
      return;
    }
  }
  FAIL();
}
#endif
TEST_F(test_dmatrix, multiply)
{
  dmatrix m(1, 2, 1, 3);
  m(1, 1) = 0;
  m(1, 2) = 1;
  m(1, 3) = 2;
  m(2, 1) = 3;
  m(2, 2) = 4;
  m(2, 3) = 5;
  dmatrix n(1, 3, 1, 2);
  n(1, 1) = 5;
  n(2, 1) = 4;
  n(3, 1) = 3;
  n(1, 2) = 2;
  n(2, 2) = 1;
  n(3, 2) = 0;

  dmatrix mn = m * n;
  ASSERT_DOUBLE_EQ(10, mn(1, 1));
  ASSERT_DOUBLE_EQ(1, mn(1, 2));
  ASSERT_DOUBLE_EQ(46, mn(2, 1));
  ASSERT_DOUBLE_EQ(10, mn(2, 2));
}
TEST_F(test_dmatrix, mystrlen)
{
  int mystrlen(const char* line);
  char s[] = "12345678901234567\0";
  int actual = mystrlen(s);
  ASSERT_EQ(17, actual);
}
TEST_F(test_dmatrix, is_valid_row)
{
  dmatrix m(1, 4, 1, 3);
  m.initialize();
  ASSERT_EQ(false, m.is_valid_row(-1));
  ASSERT_EQ(false, m.is_valid_row(0));
  ASSERT_EQ(true, m.is_valid_row(1));
  ASSERT_EQ(true, m.is_valid_row(2));
  ASSERT_EQ(true, m.is_valid_row(3));
  ASSERT_EQ(true, m.is_valid_row(4));
  ASSERT_EQ(false, m.is_valid_row(5));
  ASSERT_DOUBLE_EQ(0, m(1, 1));
  ASSERT_DOUBLE_EQ(0, m(1, 3));
  ASSERT_DEATH(m(0), "Assertion");
  ASSERT_DEATH(m(5), "Assertion");
  ASSERT_DEATH(m(1, 0), "Assertion");
  ASSERT_DEATH(m(1, 4), "Assertion");
}
TEST_F(test_dmatrix, multiply_d3a_array_dvector)
{
  dvector v(1, 2);
  v = 3;
  d3_array t(1, 2, 1, 2, 1, 2);
  t(1) = 1;
  t(2) = 2;
  dmatrix m = t * v;
  ASSERT_EQ(6, m(1, 1));
  ASSERT_EQ(6, m(1, 2));
  ASSERT_EQ(12, m(2, 1));
  ASSERT_EQ(12, m(2, 2));
}
TEST_F(test_dmatrix, extract_diagonal)
{
  dmatrix m(1, 3, 1, 3);
  for (int i = 1; i <= 3; ++i)
  {
    for (int j = 1; j <= 3; ++j)
    {
      m(i, j) = i + j;
    }
  }
  dvector v(1, 3);
  v.initialize();
  dvector extract_diagonal(const dmatrix& m);
  v = extract_diagonal(m);
  ASSERT_DOUBLE_EQ(2, v(1));
  ASSERT_DOUBLE_EQ(4, v(2));
  ASSERT_DOUBLE_EQ(6, v(3));
}
TEST_F(test_dmatrix, extract_diagonal_error)
{
  ad_exit=&test_ad_exit;
  dmatrix m(2, 3, 1, 3);
  try
  {
    dvector extract_diagonal(const dmatrix& m);
    extract_diagonal(m);
  }
  catch (const int exit_code)
  {
    const int expected_exit_code = 1;
    if (exit_code == expected_exit_code)
    {
      return;
    }
  }
  FAIL();
}
TEST_F(test_dmatrix, extract_diagonal_error2)
{
  ad_exit=&test_ad_exit;
  dmatrix m(1, 3, 1, 4);
  try
  {
    dvector extract_diagonal(const dmatrix& m);
    extract_diagonal(m);
  }
  catch (const int exit_code)
  {
    const int expected_exit_code = 1;
    if (exit_code == expected_exit_code)
    {
      return;
    }
  }
  FAIL();
}
TEST_F(test_dmatrix, mean)
{
  dmatrix m(1, 2, 1, 2);
  m(1, 1) = 4;
  m(1, 2) = 8;
  m(2, 1) = 12;
  m(2, 2) = 16;

  double mean(const dmatrix& m);
  ASSERT_DOUBLE_EQ(10, mean(m));
}
TEST_F(test_dmatrix, colsum)
{
  dmatrix m(1, 3, 1, 3);
  m(1, 1) = 1;
  m(1, 2) = 2;
  m(1, 3) = 3;
  m(2, 1) = 4;
  m(2, 2) = 5;
  m(2, 3) = 6;
  m(3, 1) = 7;
  m(3, 2) = 8;
  m(3, 3) = 9;

  double colsum(const dmatrix& m, int col);
  ASSERT_DOUBLE_EQ(12, colsum(m, 1));
  ASSERT_DOUBLE_EQ(15, colsum(m, 2));
  ASSERT_DOUBLE_EQ(18, colsum(m, 3));

  ASSERT_ANY_THROW({
    colsum(m, 0);
  });
  ASSERT_ANY_THROW({
    colsum(m, 4);
  });
}
TEST_F(test_dmatrix, column_vector)
{
  dvector v(1, 4);
  v(1) = 4;
  v(2) = 3;
  v(3) = 2;
  v(4) = 1;
  dmatrix ret = column_vector(v);
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
  ASSERT_DOUBLE_EQ(4, ret(1, 1));
  ASSERT_DOUBLE_EQ(3, ret(2, 1));
  ASSERT_DOUBLE_EQ(2, ret(3, 1));
  ASSERT_DOUBLE_EQ(1, ret(4, 1));
}
TEST_F(test_dmatrix, row_vector)
{
  dvector v(1, 4);
  v(1) = 4;
  v(2) = 3;
  v(3) = 2;
  v(4) = 1;
  dmatrix ret = row_vector(v);
  ASSERT_EQ(1, ret.rowmin());
  ASSERT_EQ(1, ret.rowmax());
  ASSERT_EQ(1, ret(1).indexmin());
  ASSERT_EQ(4, ret(1).indexmax());
  ASSERT_DOUBLE_EQ(4, ret(1, 1));
  ASSERT_DOUBLE_EQ(3, ret(1, 2));
  ASSERT_DOUBLE_EQ(2, ret(1, 3));
  ASSERT_DOUBLE_EQ(1, ret(1, 4));
}
TEST_F(test_dmatrix, default)
{
  dmatrix ret;

/*
  ASSERT_EQ(1, ret.rowmin());
  ASSERT_EQ(0, ret.rowmax());
  ASSERT_EQ(0, ret.rowsize());
*/

  //ASSERT_EQ(1, ret.colmin());
  //ASSERT_EQ(0, ret.colmax());
  ASSERT_EQ(0, ret.colsize());
}
