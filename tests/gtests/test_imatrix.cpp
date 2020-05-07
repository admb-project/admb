#include <gtest/gtest.h>
#include <fvar.hpp>
#include <climits>

extern "C"
{
  void test_ad_exit(const int exit_code);
}

class test_imatrix: public ::testing::Test {};

TEST_F(test_imatrix, rowmax_plus_1)
{
  ad_exit=&test_ad_exit;

  imatrix m(1, 4, 1, 3);
  m.initialize();
  ASSERT_THROW(m[5],int);
}
TEST_F(test_imatrix, rowmax)
{
  imatrix m(1, 4, 1, 3);
  int expected = m.rowsize() + m.rowmin() - 1;
  ASSERT_EQ(expected,m.rowmax());
}
TEST_F(test_imatrix, is_valid_row)
{
  imatrix m(1, 4, 1, 3);
  ASSERT_EQ(false, m.is_valid_row(-1));
  ASSERT_EQ(false, m.is_valid_row(0));
  ASSERT_EQ(true, m.is_valid_row(1));
  ASSERT_EQ(true, m.is_valid_row(2));
  ASSERT_EQ(true, m.is_valid_row(3));
  ASSERT_EQ(true, m.is_valid_row(4));
  ASSERT_EQ(false, m.is_valid_row(5));
}
TEST_F(test_imatrix, assignment)
{
  imatrix m(1, 4, 1, 3);
  m.initialize();
  for (int i = 1; i <= 4; ++i)
  {
    for (int j = 1; j <= 3; ++j)
    {
      ASSERT_EQ(0, m(i, j));
    }
  }
  m = 5;
  for (int i = 1; i <= 4; ++i)
  {
    for (int j = 1; j <= 3; ++j)
    {
      ASSERT_EQ(5, m(i, j));
    }
  }
}
TEST_F(test_imatrix, assignment_imatrix)
{
  ad_exit=&test_ad_exit;
  imatrix m(1, 4, 1, 3);
  imatrix m2(1, 2, 1, 2);
  ASSERT_THROW(m = m2, int);
}
TEST_F(test_imatrix, diagonal)
{
  imatrix m(1, 3, 1, 3);
  m.initialize();
  m(1, 1) = 10;
  m(2, 2) = 20;
  m(3, 3) = 30;
  ivector ret = diagonal(m);
  ASSERT_EQ(10, ret(1));
  ASSERT_EQ(20, ret(2));
  ASSERT_EQ(30, ret(3));
}
TEST_F(test_imatrix, diagonalerror)
{
  ASSERT_ANY_THROW({
    imatrix m(1, 3, 2, 3);
    diagonal(m);
  });
  ASSERT_ANY_THROW({
    imatrix m(1, 3, 1, 4);
    diagonal(m);
  });
}
TEST_F(test_imatrix, min)
{
  int min(const imatrix& M);
  imatrix m(1, 3, 1, 3);
  m.initialize();
  m(2, 2) = -20;
  ASSERT_EQ(-20, min(m));
}
TEST_F(test_imatrix, max)
{
  int max(const imatrix& M);
  imatrix m(1, 3, 1, 3);
  m.initialize();
  m(2, 2) = 20;
  ASSERT_EQ(20, max(m));
}
TEST_F(test_imatrix, colsum)
{
  imatrix m(1, 3, 1, 3);
  m.initialize();

  int count = 0;
  for (int i = 1; i <= 3; ++i)
  {
    for (int j = 1; j <= 3; ++j)
    {
      m(i, j) = count;
      ++count;
    }
  }
  ivector ret(1, 3);
  ivector colsum(const imatrix& m);
  ret = colsum(m);
  ASSERT_EQ(9, ret(1));
  ASSERT_EQ(12, ret(2));
  ASSERT_EQ(15, ret(3));
}
TEST_F(test_imatrix, sum)
{
  imatrix m(1, 3, 1, 3);
  m.initialize();

  int count = 0;
  for (int i = 1; i <= 3; ++i)
  {
    for (int j = 1; j <= 3; ++j)
    {
      m(i, j) = count;
      ++count;
    }
  }
  int ret = sum(m);
  ASSERT_EQ(36, ret);
}
TEST_F(test_imatrix, rowsum)
{
  imatrix m(1, 3, 1, 3);
  m.initialize();

  int count = 0;
  for (int i = 1; i <= 3; ++i)
  {
    for (int j = 1; j <= 3; ++j)
    {
      m(i, j) = count;
      ++count;
    }
  }
  ivector ret(1, 3);
  ivector rowsum(const imatrix& m);
  ret = rowsum(m);
  ASSERT_EQ(3, ret(1));
  ASSERT_EQ(12, ret(2));
  ASSERT_EQ(21, ret(3));
}
TEST_F(test_imatrix, column)
{
  imatrix m(1, 3, 1, 3);
  m.initialize();

  int count = 0;
  for (int i = 1; i <= 3; ++i)
  {
    for (int j = 1; j <= 3; ++j)
    {
      m(i, j) = count;
      ++count;
    }
  }
  ivector ret(1, 3);
  ret = column(m, 2);
  ASSERT_EQ(1, ret(1));
  ASSERT_EQ(4, ret(2));
  ASSERT_EQ(7, ret(3));

  int sum = colsum(m, 2);
  ASSERT_EQ(12, sum);
}
TEST_F(test_imatrix, columnexit)
{
  imatrix m(1, 3, 2, 4);
  ASSERT_ANY_THROW({
    column(m, 1);
  });
  ASSERT_ANY_THROW({
    column(m, 5);
  });
  ASSERT_ANY_THROW({
    colsum(m, 1);
  });
  ASSERT_ANY_THROW({
    colsum(m, 5);
  });
}
TEST_F(test_imatrix, allocate_imatrix)
{
  imatrix m(1, 3, 1, 3);
  m.initialize();

  int count = 0;
  for (int i = 1; i <= 3; ++i)
  {
    for (int j = 1; j <= 3; ++j)
    {
      m(i, j) = count;
      ++count;
    }
  }

  imatrix matrix;
  matrix.allocate(m);

  count = 0;
  for (int i = 1; i <= 3; ++i)
  {
    for (int j = 1; j <= 3; ++j)
    {
      ASSERT_EQ(m(i, j), count);
      ++count;
    }
  }
}
TEST_F(test_imatrix, allocate_imatrix_emptycolumns)
{
  imatrix m(1, 3);
  m.initialize();

  imatrix matrix;
  matrix.allocate(m);

  ASSERT_EQ(1, matrix.rowmin());
  ASSERT_EQ(3, matrix.rowmax());
  ASSERT_FALSE(allocated(matrix(1)));
  ASSERT_FALSE(allocated(matrix(2)));
  ASSERT_FALSE(allocated(matrix(3)));
}
TEST_F(test_imatrix, allocate_imatrix_empty)
{
  imatrix m;
  m.initialize();
  ASSERT_EQ(1, m.rowmin());
  ASSERT_EQ(0, m.rowmax());
  ASSERT_EQ(0, m.rowsize());
  ASSERT_FALSE(allocated(m));
  ASSERT_TRUE(sub_unallocated(m));

  imatrix matrix;
  matrix.allocate(m);

  ASSERT_EQ(1, matrix.rowmin());
  ASSERT_EQ(0, matrix.rowmax());
  ASSERT_EQ(0, matrix.rowsize());
  ASSERT_FALSE(allocated(matrix));
  ASSERT_TRUE(sub_unallocated(matrix));
}
TEST_F(test_imatrix, raggedallocate)
{
  imatrix m;

  ivector colsmin(1, 3);
  colsmin(1) = 2;
  colsmin(2) = 4;
  colsmin(3) = 6;
  ivector colsmax(1, 3);
  colsmax(1) = 12;
  colsmax(2) = 14;
  colsmax(3) = 16;
  m.allocate(1, 3, colsmin, colsmax);

  ASSERT_EQ(m.rowmin(), 1);
  ASSERT_EQ(m.rowmax(), 3);
  ASSERT_EQ(m.rowmin(), m.indexmin());
  ASSERT_EQ(m.rowmax(), m.indexmax());
  ASSERT_EQ(colsmin(1), m(1).indexmin());
  ASSERT_EQ(colsmax(1), m(1).indexmax());
  ASSERT_EQ(colsmin(2), m(2).indexmin());
  ASSERT_EQ(colsmax(2), m(2).indexmax());
  ASSERT_EQ(colsmin(3), m(3).indexmin());
  ASSERT_EQ(colsmax(3), m(3).indexmax());
}
TEST_F(test_imatrix, raggedallocate2)
{
  imatrix m;

  ivector colsmax(1, 3);
  colsmax(1) = 12;
  colsmax(2) = 14;
  colsmax(3) = 16;
  m.allocate(1, 3, 5, colsmax);

  ASSERT_EQ(m.rowmin(), 1);
  ASSERT_EQ(m.rowmax(), 3);
  ASSERT_EQ(m.rowmin(), m.indexmin());
  ASSERT_EQ(m.rowmax(), m.indexmax());
  ASSERT_EQ(5, m(1).indexmin());
  ASSERT_EQ(colsmax(1), m(1).indexmax());
  ASSERT_EQ(5, m(2).indexmin());
  ASSERT_EQ(colsmax(2), m(2).indexmax());
  ASSERT_EQ(5, m(3).indexmin());
  ASSERT_EQ(colsmax(3), m(3).indexmax());
}
TEST_F(test_imatrix, fill_seqadd)
{
  imatrix m(1, 3, 1, 3);
  int start = 11;
  int increment = 5;
  m.fill_seqadd(11, 5);

  ASSERT_EQ(11, m(1, 1));
  ASSERT_EQ(16, m(1, 2));
  ASSERT_EQ(21, m(1, 3));
  ASSERT_EQ(26, m(2, 1));
  ASSERT_EQ(31, m(2, 2));
  ASSERT_EQ(36, m(2, 3));
  ASSERT_EQ(41, m(3, 1));
  ASSERT_EQ(46, m(3, 2));
  ASSERT_EQ(51, m(3, 3));
}
TEST_F(test_imatrix, imatrix_position)
{
  imatrix_position position(1, 3);
  ASSERT_EQ(position.lb(1), 0);
  ASSERT_EQ(position.lb(2), 0);
  ASSERT_EQ(position.lb(3), 0);
  ASSERT_EQ(position.ub(1), -1);
  ASSERT_EQ(position.ub(2), -1);
  ASSERT_EQ(position.ub(3), -1);
  ASSERT_TRUE(position.ptr(1) == 0);
  ASSERT_TRUE(position.ptr(2) == 0);
  ASSERT_TRUE(position.ptr(3) == 0);

  imatrix_position copy_position(position);
  ASSERT_EQ(copy_position.lb(1), 0);
  ASSERT_EQ(copy_position.lb(2), 0);
  ASSERT_EQ(copy_position.lb(3), 0);
  ASSERT_EQ(copy_position.ub(1), -1);
  ASSERT_EQ(copy_position.ub(2), -1);
  ASSERT_EQ(copy_position.ub(3), -1);
  ASSERT_TRUE(copy_position.ptr(1) == 0);
  ASSERT_TRUE(copy_position.ptr(2) == 0);
  ASSERT_TRUE(copy_position.ptr(3) == 0);

  position.lb.allocate(1, 3);
  position.lb(1) = 1;
  position.lb(2) = 2;
  position.lb(3) = 3;
  position.ub.allocate(1, 3);
  position.ub(1) = 4;
  position.ub(2) = 5;
  position.ub(3) = 6;

  imatrix_position copy_position2(position);
  ASSERT_EQ(copy_position2.lb(1), 1);
  ASSERT_EQ(copy_position2.lb(2), 2);
  ASSERT_EQ(copy_position2.lb(3), 3);
  ASSERT_EQ(copy_position2.ub(1), 4);
  ASSERT_EQ(copy_position2.ub(2), 5);
  ASSERT_EQ(copy_position2.ub(3), 6);
  ASSERT_TRUE(copy_position2.ptr(1) == 0);
  ASSERT_TRUE(copy_position2.ptr(2) == 0);
  ASSERT_TRUE(copy_position2.ptr(3) == 0);

  imatrix m;
  m.allocate(position);
  ASSERT_EQ(1, m.rowmin());
  ASSERT_EQ(3, m.rowmax());
  ASSERT_EQ(position.lb(1), m(1).indexmin());
  ASSERT_EQ(position.ub(1), m(1).indexmax());
  ASSERT_EQ(position.lb(2), m(2).indexmin());
  ASSERT_EQ(position.ub(2), m(2).indexmax());
  ASSERT_EQ(position.lb(3), m(3).indexmin());
  ASSERT_EQ(position.ub(3), m(3).indexmax());

  imatrix_position copy_position3(m);
  ASSERT_EQ(copy_position3.lb(1), 1);
  ASSERT_EQ(copy_position3.lb(2), 2);
  ASSERT_EQ(copy_position3.lb(3), 3);
  ASSERT_EQ(copy_position3.ub(1), 4);
  ASSERT_EQ(copy_position3.ub(2), 5);
  ASSERT_EQ(copy_position3.ub(3), 6);
  ASSERT_TRUE(copy_position3.ptr(1) == m(1).get_v());
  ASSERT_TRUE(copy_position3.ptr(2) == m(2).get_v());
  ASSERT_TRUE(copy_position3.ptr(3) == m(3).get_v());
}
TEST_F(test_imatrix, imatrix_position_error)
{
  ASSERT_ANY_THROW({
    imatrix m;
    imatrix_position position(1, 3);
    position.lb.allocate(2, 3);
    position.ub.allocate(1, 3);
    m.allocate(position);
  });
  ASSERT_ANY_THROW({
    imatrix m;
    imatrix_position position(1, 3);
    position.lb.allocate(1, 4);
    position.ub.allocate(1, 3);
    m.allocate(position);
  });
  ASSERT_ANY_THROW({
    imatrix m;
    imatrix_position position(1, 3);
    position.lb.allocate(1, 3);
    position.ub.allocate(2, 3);
    m.allocate(position);
  });
  ASSERT_ANY_THROW({
    imatrix m;
    imatrix_position position(1, 3);
    position.lb.allocate(1, 3);
    position.ub.allocate(1, 4);
    m.allocate(position);
  });
}
TEST_F(test_imatrix, imatrix_imatrix)
{
  imatrix a(1, 2, 1, 3);
  a(1, 1) = 1;
  a(1, 2) = 2;
  a(1, 3) = 3;
  a(2, 1) = 4;
  a(2, 2) = 5;
  a(2, 3) = 6;
  imatrix b(1, 3, 1, 2);
  b(1, 1) = 7;
  b(1, 2) = 8;
  b(2, 1) = 9;
  b(2, 2) = 10;
  b(3, 1) = 11;
  b(3, 2) = 12;
  imatrix results = a * b;

  ASSERT_EQ(1, results.rowmin());
  ASSERT_EQ(2, results.rowmax());
  ASSERT_EQ(1, results.colmin());
  ASSERT_EQ(2, results.colmax());
  ASSERT_EQ(58, results(1, 1));
  ASSERT_EQ(64, results(1, 2));
  ASSERT_EQ(139, results(2, 1));
  ASSERT_EQ(154, results(2, 2));
}
TEST_F(test_imatrix, error_imatrix_imatrix)
{
  ASSERT_ANY_THROW({
    imatrix a(1, 2, 1, 3);
    imatrix b(1, 3, 2, 2);
    a * b;
  });
  ASSERT_ANY_THROW({
    imatrix a(1, 2, 1, 3);
    imatrix b(1, 3, 1, 3);
    a * b;
  });
}
TEST_F(test_imatrix, operatorequalint)
{
  imatrix m(1, 3, 1, 3);
  int value = 11;
  m = value;

  ASSERT_EQ(11, m(1, 1));
  ASSERT_EQ(11, m(1, 2));
  ASSERT_EQ(11, m(1, 3));
  ASSERT_EQ(11, m(2, 1));
  ASSERT_EQ(11, m(2, 2));
  ASSERT_EQ(11, m(2, 3));
  ASSERT_EQ(11, m(3, 1));
  ASSERT_EQ(11, m(3, 2));
  ASSERT_EQ(11, m(3, 3));
}
TEST_F(test_imatrix, assigmentempty)
{
  imatrix m(1, 3, 1, 3);
  m(1, 1) = 1;
  m(1, 2) = 2;
  m(1, 3) = 3;
  m(2, 1) = 4;
  m(2, 2) = 5;
  m(2, 3) = 6;
  m(3, 1) = 7;
  m(3, 2) = 8;
  m(3, 3) = 9;

  imatrix a;
  a = m;

  ASSERT_EQ(&a(1, 1), &m(1, 1));
  ASSERT_EQ(&a(1, 2), &m(1, 2));
  ASSERT_EQ(&a(1, 3), &m(1, 3));
  ASSERT_EQ(&a(2, 1), &m(2, 1));
  ASSERT_EQ(&a(2, 2), &m(2, 2));
  ASSERT_EQ(&a(2, 3), &m(2, 3));
  ASSERT_EQ(&a(3, 1), &m(3, 1));
  ASSERT_EQ(&a(3, 2), &m(3, 2));
  ASSERT_EQ(&a(3, 3), &m(3, 3));
}
TEST_F(test_imatrix, assigmentallocated)
{
  imatrix m(1, 3, 1, 3);
  m(1, 1) = 1;
  m(1, 2) = 2;
  m(1, 3) = 3;
  m(2, 1) = 4;
  m(2, 2) = 5;
  m(2, 3) = 6;
  m(3, 1) = 7;
  m(3, 2) = 8;
  m(3, 3) = 9;

  imatrix a(1, 3, 1, 3);
  a = m;

  ASSERT_EQ(a(1, 1), m(1, 1));
  ASSERT_EQ(a(1, 2), m(1, 2));
  ASSERT_EQ(a(1, 3), m(1, 3));
  ASSERT_EQ(a(2, 1), m(2, 1));
  ASSERT_EQ(a(2, 2), m(2, 2));
  ASSERT_EQ(a(2, 3), m(2, 3));
  ASSERT_EQ(a(3, 1), m(3, 1));
  ASSERT_EQ(a(3, 2), m(3, 2));
  ASSERT_EQ(a(3, 3), m(3, 3));

  ASSERT_NE(&a(1, 1), &m(1, 1));
  ASSERT_NE(&a(1, 2), &m(1, 2));
  ASSERT_NE(&a(1, 3), &m(1, 3));
  ASSERT_NE(&a(2, 1), &m(2, 1));
  ASSERT_NE(&a(2, 2), &m(2, 2));
  ASSERT_NE(&a(2, 3), &m(2, 3));
  ASSERT_NE(&a(3, 1), &m(3, 1));
  ASSERT_NE(&a(3, 2), &m(3, 2));
  ASSERT_NE(&a(3, 3), &m(3, 3));
}
TEST_F(test_imatrix, assigmentsame)
{
  imatrix m(1, 3, 1, 3);
  ASSERT_NO_THROW({
    m = m;
  });
}
TEST_F(test_imatrix, rowshift)
{
  imatrix m(2, 3);
  m.rowshift(1);
  ASSERT_EQ(1, m.indexmin());
  ASSERT_EQ(2, m.indexmax());
  ASSERT_EQ(2, m.rowsize());
  m.rowshift(3);
  ASSERT_EQ(3, m.indexmin());
  ASSERT_EQ(4, m.indexmax());
  ASSERT_EQ(2, m.rowsize());
}
TEST_F(test_imatrix, rowshiftempty)
{
  imatrix m;
  m.rowshift(5);
  ASSERT_EQ(1, m.indexmin());
  ASSERT_EQ(0, m.indexmax());
  ASSERT_EQ(0, m.rowsize());
}
TEST_F(test_imatrix, indexederror)
{
  ad_exit=&test_ad_exit;

  imatrix m(2, 3);
  ASSERT_ANY_THROW({
    m(1);
  });
  ASSERT_ANY_THROW({
    m(4);
  });
  ASSERT_ANY_THROW({
    m[1];
  });
  ASSERT_ANY_THROW({
    m[4];
  });
}
TEST_F(test_imatrix, constindexederror)
{
  ad_exit=&test_ad_exit;

  const imatrix m(2, 3);
  ASSERT_ANY_THROW({
    m(1);
  });
  ASSERT_ANY_THROW({
    m(4);
  });
  ASSERT_ANY_THROW({
    m[1];
  });
  ASSERT_ANY_THROW({
    m[4];
  });
}
TEST_F(test_imatrix, ij_indexederror)
{
  ad_exit=&test_ad_exit;

  imatrix m(2, 3, 2, 3);
  ASSERT_ANY_THROW({
    m(1, 2);
  });
  ASSERT_ANY_THROW({
    m(4, 2);
  });
  ASSERT_ANY_THROW({
    m(2, 1);
  });
  ASSERT_ANY_THROW({
    m(2, 4);
  });
}
TEST_F(test_imatrix, const_ij_indexederror)
{
  ad_exit=&test_ad_exit;

  const imatrix m(2, 3, 2, 3);
  ASSERT_ANY_THROW({
    m(1, 2);
  });
  ASSERT_ANY_THROW({
    m(4, 2);
  });
  ASSERT_ANY_THROW({
    m(2, 1);
  });
  ASSERT_ANY_THROW({
    m(2, 4);
  });
}
TEST_F(test_imatrix, constcopy)
{
  imatrix m(1, 4, 1, 3);
  m.initialize();
  for (int i = 1; i <= 4; ++i)
  {
    for (int j = 1; j <= 3; ++j)
    {
      ASSERT_EQ(0, m(i, j));
    }
  }
  const imatrix copy(m);
  for (int i = 1; i <= 4; ++i)
  {
    for (int j = 1; j <= 3; ++j)
    {
      ASSERT_EQ(copy(i, j), m(i, j));
    }
  }
}
TEST_F(test_imatrix, invalidconstructintintivector)
{
  ivector columns(3, 5);
  columns(3) = 10;
  columns(4) = 20;
  columns(5) = 30;
  ASSERT_EQ(0, columns.get_ncopies());

  imatrix m(4, 1, columns);

  ASSERT_EQ(1, m.indexmin());
  ASSERT_EQ(0, m.indexmax());
  ASSERT_EQ(0, columns.get_ncopies());
}
TEST_F(test_imatrix, constructintintivector)
{
  ivector columns(3, 5);
  columns(3) = 10;
  columns(4) = 20;
  columns(5) = 30;
  ASSERT_EQ(0, columns.get_ncopies());

  imatrix m(1, 4, columns);

  ASSERT_EQ(3, m(1).indexmin());
  ASSERT_EQ(5, m(1).indexmax());
  ASSERT_EQ(3, m(2).indexmin());
  ASSERT_EQ(5, m(2).indexmax());
  ASSERT_EQ(3, m(3).indexmin());
  ASSERT_EQ(5, m(3).indexmax());
  ASSERT_EQ(3, m(4).indexmin());
  ASSERT_EQ(5, m(4).indexmax());
  ASSERT_EQ(4, columns.get_ncopies());
  ASSERT_EQ(&columns(3), &m(1, 3));
  ASSERT_EQ(&columns(3), &m(2, 3));
  ASSERT_EQ(&columns(3), &m(3, 3));
  ASSERT_EQ(&columns(3), &m(4, 3));
}
TEST_F(test_imatrix, deallocatecopies)
{
  imatrix a(1, 2, 1, 2);
  ASSERT_EQ(0, a.get_ncopies());
  imatrix firstcopy(a);
  ASSERT_EQ(1, a.get_ncopies());
  ASSERT_EQ(1, firstcopy.get_ncopies());
  imatrix secondcopy(a);
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
TEST_F(test_imatrix, constconstructintintivector)
{
  ivector columns(3, 5);
  columns(3) = 10;
  columns(4) = 20;
  columns(5) = 30;
  ASSERT_EQ(0, columns.get_ncopies());

  imatrix a(1, 4, columns);
  imatrix m(a);

  ASSERT_EQ(3, m(1).indexmin());
  ASSERT_EQ(5, m(1).indexmax());
  ASSERT_EQ(3, m(2).indexmin());
  ASSERT_EQ(5, m(2).indexmax());
  ASSERT_EQ(3, m(3).indexmin());
  ASSERT_EQ(5, m(3).indexmax());
  ASSERT_EQ(3, m(4).indexmin());
  ASSERT_EQ(5, m(4).indexmax());
  ASSERT_EQ(4, columns.get_ncopies());
  ASSERT_EQ(&columns(3), &m(1, 3));
  ASSERT_EQ(&columns(3), &m(2, 3));
  ASSERT_EQ(&columns(3), &m(3, 3));
  ASSERT_EQ(&columns(3), &m(4, 3));
}
