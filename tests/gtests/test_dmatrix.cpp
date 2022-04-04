#include <gtest/gtest.h>
#include <fvar.hpp>
#include <climits>

class test_dmatrix: public ::testing::Test {};

TEST_F(test_dmatrix, norm)
{
  dmatrix m(1, 2, 1, 3);

  char array[] = "{0, -1, 2} {-3, 4, 5}";

  m.fill(array);

  double ret = norm2(m);
  ASSERT_DOUBLE_EQ(55, ret);

  double ret2 = norm(m);
  ASSERT_DOUBLE_EQ(std::pow(55, 0.5), ret2);
}
TEST_F(test_dmatrix, unbalancedbraces)
{
  dmatrix m(1, 2, 1, 3);

  char array[] = "{0, -1, 2} {-3, 4, 5";

  ASSERT_ANY_THROW({
    m.fill(array);
  });
}
TEST_F(test_dmatrix, unbalancedbraces2)
{
  dmatrix m(1, 2, 1, 3);

  char array[] = "{0, -1, 2} {-3, 4, 5} }";

  ASSERT_ANY_THROW({
    m.fill(array);
  });
}
TEST_F(test_dmatrix, notenoughrows)
{
  dmatrix m(1, 2, 1, 3);

  char array[] = "{0, -1, 2}";

  ASSERT_ANY_THROW({
    m.fill(array);
  });
}
TEST_F(test_dmatrix, toomanyrows)
{
  dmatrix m(1, 2, 1, 3);

  char array[] = "{0, -1, 2} {1, 1, 1} {1, 1, 1}";

  ASSERT_ANY_THROW({
    m.fill(array);
  });
}
TEST_F(test_dmatrix, notenoughcolumns)
{
  dmatrix m(1, 2, 1, 3);

  char array[] = "{0, -1} {-3, 4}";

  ASSERT_ANY_THROW({
    m.fill(array);
  });
}
TEST_F(test_dmatrix, toomanycolumns)
{
  dmatrix m(1, 2, 1, 3);

  char array[] = "{0, -1, 1, 1} {-3, 4, 1, 1}";

  ASSERT_ANY_THROW({
    m.fill(array);
  });
}
TEST_F(test_dmatrix, select)
{
  dmatrix m(1, 3, 1, 3);
  m.initialize();

  ASSERT_DOUBLE_EQ(0, m(1, 1));
  ASSERT_DOUBLE_EQ(0, m(1, 2));
  ASSERT_DOUBLE_EQ(0, m(1, 3));
  ASSERT_DOUBLE_EQ(0, m(2, 1));
  ASSERT_DOUBLE_EQ(0, m(2, 2));
  ASSERT_DOUBLE_EQ(0, m(2, 3));
  ASSERT_DOUBLE_EQ(0, m(3, 1));
  ASSERT_DOUBLE_EQ(0, m(3, 2));
  ASSERT_DOUBLE_EQ(0, m(3, 3));

  dvector fill(1, 3);
  fill(1) = 1;
  fill(2) = 2;
  fill(3) = 3;

  m.colfill(1, fill);

  ASSERT_DOUBLE_EQ(1, m(1, 1));
  ASSERT_DOUBLE_EQ(0, m(1, 2));
  ASSERT_DOUBLE_EQ(0, m(1, 3));
  ASSERT_DOUBLE_EQ(2, m(2, 1));
  ASSERT_DOUBLE_EQ(0, m(2, 2));
  ASSERT_DOUBLE_EQ(0, m(2, 3));
  ASSERT_DOUBLE_EQ(3, m(3, 1));
  ASSERT_DOUBLE_EQ(0, m(3, 2));
  ASSERT_DOUBLE_EQ(0, m(3, 3));

  m.colfill(2, fill);

  ASSERT_DOUBLE_EQ(1, m(1, 1));
  ASSERT_DOUBLE_EQ(1, m(1, 2));
  ASSERT_DOUBLE_EQ(0, m(1, 3));
  ASSERT_DOUBLE_EQ(2, m(2, 1));
  ASSERT_DOUBLE_EQ(2, m(2, 2));
  ASSERT_DOUBLE_EQ(0, m(2, 3));
  ASSERT_DOUBLE_EQ(3, m(3, 1));
  ASSERT_DOUBLE_EQ(3, m(3, 2));
  ASSERT_DOUBLE_EQ(0, m(3, 3));

  m.colfill(3, fill);

  ASSERT_DOUBLE_EQ(1, m(1, 1));
  ASSERT_DOUBLE_EQ(1, m(1, 2));
  ASSERT_DOUBLE_EQ(1, m(1, 3));
  ASSERT_DOUBLE_EQ(2, m(2, 1));
  ASSERT_DOUBLE_EQ(2, m(2, 2));
  ASSERT_DOUBLE_EQ(2, m(2, 3));
  ASSERT_DOUBLE_EQ(3, m(3, 1));
  ASSERT_DOUBLE_EQ(3, m(3, 2));
  ASSERT_DOUBLE_EQ(3, m(3, 3));
}
TEST_F(test_dmatrix, colfill)
{
  dmatrix m(1, 3, 1, 3);

  char array[] = "{0, -1, 2} {-3, 4, 5} {1, -2, 1}";

  m.fill(array);

  ivector indexes(1, 2);
  indexes(1) = 2;
  indexes(2) = 3;

  dmatrix ret = m(indexes);
  ASSERT_EQ(1, ret.rowmin());
  ASSERT_EQ(2, ret.rowmax());
  ASSERT_EQ(1, ret.colmin());
  ASSERT_EQ(2, ret.colmax());

  ASSERT_DOUBLE_EQ(4, ret(1, 1));
  ASSERT_DOUBLE_EQ(5, ret(1, 2));
  ASSERT_DOUBLE_EQ(-2, ret(2, 1));
  ASSERT_DOUBLE_EQ(1, ret(2, 2));
}
TEST_F(test_dmatrix, trace_or_sum)
{
  double trace(const dmatrix& M);
  dmatrix m(1, 3, 1, 3);

  char array[] = "{0, -1, 2} {-3, 4, 5} {1, -2, 1}";

  m.fill(array);

  double ret = trace(m);
  ASSERT_DOUBLE_EQ(5, ret);
}
TEST_F(test_dmatrix, trace_or_sum_exit)
{
  double trace(const dmatrix& M);
  dmatrix m(1, 2, 1, 3);

  ASSERT_ANY_THROW({
    trace(m);
  });
}
TEST_F(test_dmatrix, trace_or_sum_exit2)
{
  double trace(const dmatrix& M);
  dmatrix m(1, 2, 2, 3);

  ASSERT_ANY_THROW({
    trace(m);
  });
}
TEST_F(test_dmatrix, min)
{
  dmatrix m(1, 2, 1, 3);

  char array[] = "{0, -10, 2} {-3, 4, 5}";

  m.fill(array);

  double ret = min(m);

  ASSERT_DOUBLE_EQ(-10, ret);
}
TEST_F(test_dmatrix, min2)
{
  dmatrix m(1, 2, 1, 3);

  char array[] = "{0, -10, 2} {-3, 4, -55}";

  m.fill(array);

  double ret = min(m);

  ASSERT_DOUBLE_EQ(-55, ret);
}
TEST_F(test_dmatrix, max)
{
  dmatrix m(1, 2, 1, 3);

  char array[] = "{0, -1, 2} {-3, 4, 5}";

  m.fill(array);

  double ret = max(m);

  ASSERT_DOUBLE_EQ(5, ret);
}
TEST_F(test_dmatrix, max2)
{
  dmatrix m(1, 2, 1, 3);

  char array[] = "{0, -1, 20} {-3, 4, 5}";

  m.fill(array);

  double ret = max(m);

  ASSERT_DOUBLE_EQ(20, ret);
}
TEST_F(test_dmatrix, cube)
{
  dmatrix m(1, 2, 1, 3);

  char array[] = "{0, -1, 20} {-3, 4, 5}";

  m.fill(array);

  dmatrix ret = cube(m);

  ASSERT_DOUBLE_EQ(std::pow(m(1, 1), 3), ret(1, 1));
  ASSERT_DOUBLE_EQ(std::pow(m(1, 2), 3), ret(1, 2));
  ASSERT_DOUBLE_EQ(std::pow(m(1, 3), 3), ret(1, 3));
  ASSERT_DOUBLE_EQ(std::pow(m(2, 1), 3), ret(2, 1));
  ASSERT_DOUBLE_EQ(std::pow(m(2, 2), 3), ret(2, 2));
  ASSERT_DOUBLE_EQ(std::pow(m(2, 3), 3), ret(2, 3));
}
TEST_F(test_dmatrix, powinteger)
{
  dmatrix m(1, 2, 1, 3);

  char array[] = "{0, -1, 2} {-3, 4, 5}";

  m.fill(array);

  int e = 2;
  dmatrix ret = pow(m, e);
  ASSERT_DOUBLE_EQ(0, ret(1, 1));
  ASSERT_DOUBLE_EQ(1, ret(1, 2));
  ASSERT_DOUBLE_EQ(4, ret(1, 3));
  ASSERT_DOUBLE_EQ(9, ret(2, 1));
  ASSERT_DOUBLE_EQ(16, ret(2, 2));
  ASSERT_DOUBLE_EQ(25, ret(2, 3));
}
TEST_F(test_dmatrix, powdouble)
{
  dmatrix m(1, 2, 1, 3);

  char array[] = "{0, 1, 4} {9, 16, 25}";

  m.fill(array);

  double e = 0.5;
  dmatrix ret = pow(m, e);
  ASSERT_DOUBLE_EQ(std::pow(0.0, 0.5), ret(1, 1));
  ASSERT_DOUBLE_EQ(std::pow(1.0, 0.5), ret(1, 2));
  ASSERT_DOUBLE_EQ(std::pow(4.0, 0.5), ret(1, 3));
  ASSERT_DOUBLE_EQ(std::pow(9.0, 0.5), ret(2, 1));
  ASSERT_DOUBLE_EQ(std::pow(16.0, 0.5), ret(2, 2));
  ASSERT_DOUBLE_EQ(std::pow(25.0, 0.5), ret(2, 3));
}
TEST_F(test_dmatrix, sqr)
{
  dmatrix m(1, 2, 1, 3);

  char array[] = "{0, 1, 4} {9, 16, 25}";

  m.fill(array);

  dmatrix ret = sqr(m);
  ASSERT_DOUBLE_EQ(0, ret(1, 1));
  ASSERT_DOUBLE_EQ(1, ret(1, 2));
  ASSERT_DOUBLE_EQ(16, ret(1, 3));
  ASSERT_DOUBLE_EQ(81, ret(2, 1));
  ASSERT_DOUBLE_EQ(16 * 16, ret(2, 2));
  ASSERT_DOUBLE_EQ(25 * 25, ret(2, 3));
}
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
  dmatrix m(2, 3, 1, 3);
  ASSERT_ANY_THROW({
    dvector extract_diagonal(const dmatrix& m);
    extract_diagonal(m);
  });
}
TEST_F(test_dmatrix, extract_diagonal_error2)
{
  dmatrix m(1, 3, 1, 4);
  ASSERT_ANY_THROW({
    dvector extract_diagonal(const dmatrix& m);
    extract_diagonal(m);
  });
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
  ad_exit=&test_ad_exit;
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
TEST_F(test_dmatrix, identity)
{
  dmatrix ret = identity_matrix(2, 5);

  ASSERT_EQ(2, ret.rowmin());
  ASSERT_EQ(5, ret.rowmax());
  ASSERT_EQ(2, ret.colmin());
  ASSERT_EQ(5, ret.colmax());

  ASSERT_DOUBLE_EQ(1, ret(2, 2));
  ASSERT_DOUBLE_EQ(0, ret(2, 3));
  ASSERT_DOUBLE_EQ(0, ret(2, 4));
  ASSERT_DOUBLE_EQ(0, ret(2, 5));
  ASSERT_DOUBLE_EQ(0, ret(3, 2));
  ASSERT_DOUBLE_EQ(1, ret(3, 3));
  ASSERT_DOUBLE_EQ(0, ret(3, 4));
  ASSERT_DOUBLE_EQ(0, ret(3, 5));
  ASSERT_DOUBLE_EQ(0, ret(4, 2));
  ASSERT_DOUBLE_EQ(0, ret(4, 3));
  ASSERT_DOUBLE_EQ(1, ret(4, 4));
  ASSERT_DOUBLE_EQ(0, ret(4, 5));
  ASSERT_DOUBLE_EQ(0, ret(5, 2));
  ASSERT_DOUBLE_EQ(0, ret(5, 3));
  ASSERT_DOUBLE_EQ(0, ret(5, 4));
  ASSERT_DOUBLE_EQ(1, ret(5, 5));
}
TEST_F(test_dmatrix, operatortimesvalue)
{
  dmatrix m(1, 2, 1, 3);

  char array[] = "{0, -1, 20} {-3, 4, 5}";

  m.fill(array);

  double value = -2.0;

  m *= value;

  ASSERT_DOUBLE_EQ(0, m(1, 1));
  ASSERT_DOUBLE_EQ(2, m(1, 2));
  ASSERT_DOUBLE_EQ(-40, m(1, 3));
  ASSERT_DOUBLE_EQ(6, m(2, 1));
  ASSERT_DOUBLE_EQ(-8, m(2, 2));
  ASSERT_DOUBLE_EQ(-10, m(2, 3));
}
TEST_F(test_dmatrix, sum)
{
  dmatrix m(1, 2, 1, 3);

  char array[] = "{0, -1, 2} {-3, 4, 5}";

  m.fill(array);

  double ret = sum(m);

  ASSERT_DOUBLE_EQ(7, ret);
}
TEST_F(test_dmatrix, rowsum)
{
  dmatrix m(1, 2, 1, 3);

  char array[] = "{0, -1, 2} {-3, 4, 5}";

  m.fill(array);

  dvector ret = rowsum(m);

  ASSERT_EQ(1, ret.indexmin());
  ASSERT_EQ(2, ret.indexmax());
  ASSERT_DOUBLE_EQ(1, ret(1));
  ASSERT_DOUBLE_EQ(6, ret(2));
}
TEST_F(test_dmatrix, fullcolsum)
{
  dmatrix m(1, 2, 1, 3);

  char array[] = "{0, -1, 2} {-3, 4, 5}";

  m.fill(array);

  dvector ret = colsum(m);

  ASSERT_EQ(1, ret.indexmin());
  ASSERT_EQ(3, ret.indexmax());
  ASSERT_DOUBLE_EQ(-3, ret(1));
  ASSERT_DOUBLE_EQ(3, ret(2));
  ASSERT_DOUBLE_EQ(7, ret(3));
}
TEST_F(test_dmatrix, uoistream)
{
  ad_exit=&test_ad_exit;
  dmatrix m(1, 2, 1, 3);

  char array[] = "{0, -1, 2} {-3, 4, 5}";

  m.fill(array);

  uostream& operator<<(const uostream&, const dmatrix&);

  uostream output("test_damtrixio.txt");
  output << m;
  output.close();

  dmatrix b(1, 2, 1, 3);
  b.initialize();

  uistream& operator>>(const uistream&, const dmatrix&);
  uistream input("test_damtrixio.txt");
  input >> b;
  input.close();

  ASSERT_DOUBLE_EQ(m(1, 1), b(1, 1));
  ASSERT_DOUBLE_EQ(m(1, 2), b(1, 2));
  ASSERT_DOUBLE_EQ(m(1, 3), b(1, 3));
  ASSERT_DOUBLE_EQ(m(2, 1), b(2, 1));
  ASSERT_DOUBLE_EQ(m(2, 2), b(2, 2));
  ASSERT_DOUBLE_EQ(m(2, 3), b(2, 3));

  dmatrix c(1, 3, 1, 3);
  c.initialize();

  ASSERT_ANY_THROW({
    uistream input2("test_damtrixio.txt");
    input2 >> c;
    input2.close();
  });
}
TEST_F(test_dmatrix, assigmenterror)
{
  ad_exit=&test_ad_exit;
  dmatrix a(1, 2, 1, 3);
  ASSERT_ANY_THROW({
    dmatrix b(2, 2, 1, 3);
    a = b;
  });
  ASSERT_ANY_THROW({
    dmatrix b(1, 2, 2, 3);
    a = b;
  });
  ASSERT_ANY_THROW({
    dmatrix b(1, 3, 1, 3);
    a = b;
  });
  ASSERT_ANY_THROW({
    dmatrix b(1, 2, 1, 4);
    a = b;
  });
}
TEST_F(test_dmatrix, plusassigmenterror)
{
  ad_exit=&test_ad_exit;
  dmatrix a(1, 2, 1, 3);
  ASSERT_ANY_THROW({
    dmatrix b(2, 2, 1, 3);
    a += b;
  });
  ASSERT_ANY_THROW({
    dmatrix b(1, 3, 1, 3);
    a += b;
  });
}
TEST_F(test_dmatrix, minusassigmenterror)
{
  ad_exit=&test_ad_exit;
  dmatrix a(1, 2, 1, 3);
  ASSERT_ANY_THROW({
    dmatrix b(2, 2, 1, 3);
    a -= b;
  });
  ASSERT_ANY_THROW({
    dmatrix b(1, 3, 1, 3);
    a -= b;
  });
}
TEST_F(test_dmatrix, minusassigment)
{
  dmatrix a(1, 2, 1, 2);
  char array[] = "{0, -1} {-3, 4}";
  a.fill(array);
  dmatrix b(1, 2, 1, 2);
  char array2[] = "{0, 1} {3, 4}";
  b.fill(array2);

  a -= b;

  ASSERT_DOUBLE_EQ(a(1, 1), 0);
  ASSERT_DOUBLE_EQ(a(1, 2), -2);
  ASSERT_DOUBLE_EQ(a(2, 1), -6);
  ASSERT_DOUBLE_EQ(a(2, 2), 0);
}
TEST_F(test_dmatrix, plusassigment)
{
  dmatrix a(1, 2, 1, 2);
  char array[] = "{0, -1} {-3, 4}";
  a.fill(array);
  dmatrix b(1, 2, 1, 2);
  char array2[] = "{0, 1} {3, 4}";
  b.fill(array2);

  a += b;

  ASSERT_DOUBLE_EQ(a(1, 1), 0);
  ASSERT_DOUBLE_EQ(a(1, 2), 0);
  ASSERT_DOUBLE_EQ(a(2, 1), 0);
  ASSERT_DOUBLE_EQ(a(2, 2), 8);
}
TEST_F(test_dmatrix, assigment)
{
  dmatrix a(1, 2, 1, 2);
  char array[] = "{0, -1} {-3, 4}";
  a.fill(array);

  dmatrix b(1, 2, 1, 2);
  b = a;

  ASSERT_DOUBLE_EQ(b(1, 1), 0);
  ASSERT_DOUBLE_EQ(b(1, 2), -1);
  ASSERT_DOUBLE_EQ(b(2, 1), -3);
  ASSERT_DOUBLE_EQ(b(2, 2), 4);
}
TEST_F(test_dmatrix, initialize)
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
  ASSERT_DOUBLE_EQ(1, m(1, 1));
  ASSERT_DOUBLE_EQ(2, m(1, 2));
  ASSERT_DOUBLE_EQ(3, m(1, 3));
  ASSERT_DOUBLE_EQ(4, m(2, 1));
  ASSERT_DOUBLE_EQ(5, m(2, 2));
  ASSERT_DOUBLE_EQ(6, m(2, 3));
  ASSERT_DOUBLE_EQ(7, m(3, 1));
  ASSERT_DOUBLE_EQ(8, m(3, 2));
  ASSERT_DOUBLE_EQ(9, m(3, 3));
  m.initialize();

  ASSERT_DOUBLE_EQ(0, m(1, 1));
  ASSERT_DOUBLE_EQ(0, m(1, 2));
  ASSERT_DOUBLE_EQ(0, m(1, 3));
  ASSERT_DOUBLE_EQ(0, m(2, 1));
  ASSERT_DOUBLE_EQ(0, m(2, 2));
  ASSERT_DOUBLE_EQ(0, m(2, 3));
  ASSERT_DOUBLE_EQ(0, m(3, 1));
  ASSERT_DOUBLE_EQ(0, m(3, 2));
  ASSERT_DOUBLE_EQ(0, m(3, 3));
}
TEST_F(test_dmatrix, emptyinitialize)
{
  ad_exit=&test_ad_exit;
  dmatrix m;
  ASSERT_NO_THROW({
    m.initialize();
  });
}
TEST_F(test_dmatrix, empty)
{
  ad_exit=&test_ad_exit;
  dmatrix empty;
  ASSERT_EQ(1, empty.rowmin());
  ASSERT_EQ(0, empty.rowmax());
  ASSERT_EQ(0, empty.rowsize());
  ASSERT_EQ(0, empty.colsize());

  ASSERT_ANY_THROW({
    empty.colmin();
  });
  ASSERT_ANY_THROW({
    empty.colmax();
  });
}
TEST_F(test_dmatrix, symmetrize)
{
  dmatrix m(1, 3, 1, 3);
  char array[] = "{0, 1, 2} {3, 4, 5} {6, 7, 8}";
  m.fill(array);

  dmatrix results = symmetrize(m);

  ASSERT_DOUBLE_EQ(0, results(1, 1));
  ASSERT_DOUBLE_EQ(2, results(1, 2));
  ASSERT_DOUBLE_EQ(4, results(1, 3));
  ASSERT_DOUBLE_EQ(2, results(2, 1));
  ASSERT_DOUBLE_EQ(4, results(2, 2));
  ASSERT_DOUBLE_EQ(6, results(2, 3));
  ASSERT_DOUBLE_EQ(4, results(3, 1));
  ASSERT_DOUBLE_EQ(6, results(3, 2));
  ASSERT_DOUBLE_EQ(8, results(3, 3));
}
TEST_F(test_dmatrix, symmetrizeerror)
{
  ad_exit=&test_ad_exit;
  ASSERT_ANY_THROW({
    dmatrix m(1, 2, 1, 3);
    symmetrize(m);
  });
  ASSERT_ANY_THROW({
    dmatrix m(1, 3, 2, 3);
    symmetrize(m);
  });
}
TEST_F(test_dmatrix, extract_row)
{
  dmatrix m(1, 3, 1, 3);
  char array[] = "{0, 1, 2} {3, 4, 5} {6, 7, 8}";
  m.fill(array);

  dvector m1 = extract_row(m, 1);
  ASSERT_EQ(1, m1.indexmin());
  ASSERT_EQ(3, m1.indexmax());
  ASSERT_DOUBLE_EQ(0, m1(1));
  ASSERT_DOUBLE_EQ(1, m1(2));
  ASSERT_DOUBLE_EQ(2, m1(3));
  dvector m2 = extract_row(m, 2);
  ASSERT_EQ(1, m2.indexmin());
  ASSERT_EQ(3, m2.indexmax());
  ASSERT_DOUBLE_EQ(3, m2(1));
  ASSERT_DOUBLE_EQ(4, m2(2));
  ASSERT_DOUBLE_EQ(5, m2(3));
  dvector m3 = extract_row(m, 3);
  ASSERT_EQ(1, m3.indexmin());
  ASSERT_EQ(3, m3.indexmax());
  ASSERT_DOUBLE_EQ(6, m3(1));
  ASSERT_DOUBLE_EQ(7, m3(2));
  ASSERT_DOUBLE_EQ(8, m3(3));
}
TEST_F(test_dmatrix, extract_rowerror)
{
  ad_exit=&test_ad_exit;
  dmatrix m(1, 3);
  ASSERT_ANY_THROW({
    row(m, 0);
  });
  ASSERT_ANY_THROW({
    row(m, 4);
  });
}
TEST_F(test_dmatrix, extract_column)
{
  dmatrix m(1, 3, 1, 3);
  char array[] = "{0, 1, 2} {3, 4, 5} {6, 7, 8}";
  m.fill(array);

  dvector m1 = extract_column(m, 1);
  ASSERT_EQ(1, m1.indexmin());
  ASSERT_EQ(3, m1.indexmax());
  ASSERT_DOUBLE_EQ(0, m1(1));
  ASSERT_DOUBLE_EQ(3, m1(2));
  ASSERT_DOUBLE_EQ(6, m1(3));
  dvector m2 = extract_column(m, 2);
  ASSERT_EQ(1, m2.indexmin());
  ASSERT_EQ(3, m2.indexmax());
  ASSERT_DOUBLE_EQ(1, m2(1));
  ASSERT_DOUBLE_EQ(4, m2(2));
  ASSERT_DOUBLE_EQ(7, m2(3));
  dvector m3 = extract_column(m, 3);
  ASSERT_EQ(1, m3.indexmin());
  ASSERT_EQ(3, m3.indexmax());
  ASSERT_DOUBLE_EQ(2, m3(1));
  ASSERT_DOUBLE_EQ(5, m3(2));
  ASSERT_DOUBLE_EQ(8, m3(3));
}
TEST_F(test_dmatrix, extract_columnerror)
{
  ad_exit=&test_ad_exit;
  dmatrix m(1, 3, 1, 3);
  ASSERT_ANY_THROW({
    row(m, 0);
  });
  ASSERT_ANY_THROW({
    row(m, 4);
  });
}
TEST_F(test_dmatrix, copy_empty)
{
  dmatrix empty;

  ASSERT_TRUE(empty.begin() == nullptr);
  ASSERT_TRUE(empty.end() == nullptr);
  ASSERT_TRUE(empty.operator!());
  ASSERT_TRUE(empty.indexmin() == 1);
  ASSERT_TRUE(empty.indexmax() == 0);

  dmatrix copy(empty);

  ASSERT_TRUE(copy.begin() == nullptr);
  ASSERT_TRUE(copy.end() == nullptr);
  ASSERT_TRUE(copy.operator!());
  ASSERT_TRUE(copy.indexmin() == 1);
  ASSERT_TRUE(copy.indexmax() == 0);
}
TEST_F(test_dmatrix, mean_empty)
{
  dmatrix empty;
  double mean(const dmatrix&);
  ASSERT_ANY_THROW({
    mean(empty);
  });
}
TEST_F(test_dmatrix, mean_negative)
{
  dmatrix m(1, 2, 1, 2);
  m(1, 1) = 4.5;
  m(1, 2) = 8.1;
  m(2, 1) = -12.8;
  m(2, 2) = 16.3;

  double mean(const dmatrix& m);
  ASSERT_DOUBLE_EQ(4.025, mean(m));
}
TEST_F(test_dmatrix, file)
{
  std::ofstream ofs("dmatrix.txt");
  ofs << "    1,     2   ,   3\n";
  ofs << "    -4,5.25,6\n";
  ofs.close();
  
  dmatrix m((char*)"dmatrix.txt");
  cout << m << endl;
  ASSERT_DOUBLE_EQ(m.rowmin(), 1);
  ASSERT_DOUBLE_EQ(m.rowmax(), 2);
  ASSERT_DOUBLE_EQ(m(1).indexmin(), 1);
  ASSERT_DOUBLE_EQ(m(1).indexmax(), 3);
  ASSERT_DOUBLE_EQ(m(2).indexmin(), 1);
  ASSERT_DOUBLE_EQ(m(2).indexmax(), 3);
  ASSERT_DOUBLE_EQ(m(1, 1), 1);
  ASSERT_DOUBLE_EQ(m(1, 2), 2);
  ASSERT_DOUBLE_EQ(m(1, 3), 3);
  ASSERT_DOUBLE_EQ(m(2, 1), -4);
  ASSERT_DOUBLE_EQ(m(2, 2), 5.25);
  ASSERT_DOUBLE_EQ(m(2, 3), 6);
}
TEST_F(test_dmatrix, file_spaces)
{
  std::ofstream ofs("dmatrix.txt");
  ofs << "    1      2       3\n";
  ofs << "    -4 5.25 6\n";
  ofs.close();
  
  dmatrix m((char*)"dmatrix.txt");
  cout << m << endl;
  ASSERT_DOUBLE_EQ(m.rowmin(), 1);
  ASSERT_DOUBLE_EQ(m.rowmax(), 2);
  ASSERT_DOUBLE_EQ(m(1).indexmin(), 1);
  ASSERT_DOUBLE_EQ(m(1).indexmax(), 3);
  ASSERT_DOUBLE_EQ(m(2).indexmin(), 1);
  ASSERT_DOUBLE_EQ(m(2).indexmax(), 3);
  ASSERT_DOUBLE_EQ(m(1, 1), 1);
  ASSERT_DOUBLE_EQ(m(1, 2), 2);
  ASSERT_DOUBLE_EQ(m(1, 3), 3);
  ASSERT_DOUBLE_EQ(m(2, 1), -4);
  ASSERT_DOUBLE_EQ(m(2, 2), 5.25);
  ASSERT_DOUBLE_EQ(m(2, 3), 6);
}
