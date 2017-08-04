#include <gtest/gtest.h>
#include <cmath>
#include "fvar.hpp"

extern "C"
{
  void test_ad_exit(const int exit_code);
}

class test_i3_array: public ::testing::Test {};

TEST_F(test_i3_array, inputoutput)
{
  i3_array a(1, 2, 1, 2, 1, 2);

  int d = 2;
  for (int i = 1; i <= 2; ++i)
  {
    for (int j = 1; j <= 2; ++j)
    {
      for (int k = 1; k <= 2; ++k)
      {
        a(i, j, k) = d;
        d += 2;
      }
    }
  }

  ofstream ofs("testi3array.txt");
  ofs << a;
  ofs.close();

  i3_array ret(1, 2, 1, 2, 1, 2);

  ifstream ifs("testi3array.txt");
  ifs >> ret;
  ifs.close();

  d = 2;
  for (int i = 1; i <= 2; ++i)
  {
    for (int j = 1; j <= 2; ++j)
    {
      for (int k = 1; k <= 2; ++k)
      {
        ASSERT_EQ(a(i, j, k), ret(i, j, k));
        d += 2;
      }
    }
  }
}
TEST_F(test_i3_array, deallocate)
{
  i3_array a(2, 5);

  ASSERT_EQ(2, a.slicemin());
  ASSERT_EQ(5, a.slicemax());
  ASSERT_EQ(4, a.slicesize());

  a.deallocate();

  ASSERT_EQ(1, a.slicemin());
  ASSERT_EQ(0, a.slicemax());
  ASSERT_EQ(0, a.slicesize());
  ASSERT_FALSE(allocated(a));
}
TEST_F(test_i3_array, allocate2xintcolsvec)
{
  ivector colsmin(2, 5);
  colsmin(2) = 4;
  colsmin(3) = 5;
  colsmin(4) = 6;
  colsmin(5) = 7;
  ivector colsmax(2, 5);
  colsmax(2) = 14;
  colsmax(3) = 15;
  colsmax(4) = 16;
  colsmax(5) = 17;

  i3_array a;
  a.allocate(2, 5, 1, 4, colsmin, colsmax);
  ASSERT_EQ(2, a.slicemin());
  ASSERT_EQ(5, a.slicemax());
  ASSERT_EQ(4, a.slicesize());
  ASSERT_EQ(1, a(2).rowmin());
  ASSERT_EQ(4, a(2).rowmax());
  ASSERT_EQ(1, a(3).rowmin());
  ASSERT_EQ(4, a(3).rowmax());
  ASSERT_EQ(1, a(4).rowmin());
  ASSERT_EQ(4, a(4).rowmax());
  ASSERT_EQ(1, a(5).rowmin());
  ASSERT_EQ(4, a(5).rowmax());
  ASSERT_EQ(colsmin(2), a(2).colmin());
  ASSERT_EQ(colsmax(2), a(2).colmax());
  ASSERT_EQ(colsmin(3), a(3).colmin());
  ASSERT_EQ(colsmax(3), a(3).colmax());
  ASSERT_EQ(colsmin(4), a(4).colmin());
  ASSERT_EQ(colsmax(4), a(4).colmax());
  ASSERT_EQ(colsmin(5), a(5).colmin());
  ASSERT_EQ(colsmax(5), a(5).colmax());
}
TEST_F(test_i3_array, construct2xintcolsvec)
{
  ivector colsmin(2, 5);
  colsmin(2) = 4;
  colsmin(3) = 5;
  colsmin(4) = 6;
  colsmin(5) = 7;
  ivector colsmax(2, 5);
  colsmax(2) = 14;
  colsmax(3) = 15;
  colsmax(4) = 16;
  colsmax(5) = 17;

  i3_array a(2, 5, 1, 4, colsmin, colsmax);
  ASSERT_EQ(2, a.slicemin());
  ASSERT_EQ(5, a.slicemax());
  ASSERT_EQ(4, a.slicesize());
  ASSERT_EQ(1, a(2).rowmin());
  ASSERT_EQ(4, a(2).rowmax());
  ASSERT_EQ(1, a(3).rowmin());
  ASSERT_EQ(4, a(3).rowmax());
  ASSERT_EQ(1, a(4).rowmin());
  ASSERT_EQ(4, a(4).rowmax());
  ASSERT_EQ(1, a(5).rowmin());
  ASSERT_EQ(4, a(5).rowmax());
  ASSERT_EQ(colsmin(2), a(2).colmin());
  ASSERT_EQ(colsmax(2), a(2).colmax());
  ASSERT_EQ(colsmin(3), a(3).colmin());
  ASSERT_EQ(colsmax(3), a(3).colmax());
  ASSERT_EQ(colsmin(4), a(4).colmin());
  ASSERT_EQ(colsmax(4), a(4).colmax());
  ASSERT_EQ(colsmin(5), a(5).colmin());
  ASSERT_EQ(colsmax(5), a(5).colmax());
}
TEST_F(test_i3_array, allocatei3_array)
{
  ivector colsmin(2, 5);
  colsmin(2) = 4;
  colsmin(3) = 5;
  colsmin(4) = 6;
  colsmin(5) = 7;
  ivector colsmax(2, 5);
  colsmax(2) = 14;
  colsmax(3) = 15;
  colsmax(4) = 16;
  colsmax(5) = 17;

  i3_array a;
  a.allocate(2, 5, 1, 4, colsmin, colsmax);
  i3_array b;
  b.allocate(a);

  ASSERT_EQ(2, b.slicemin());
  ASSERT_EQ(5, b.slicemax());
  ASSERT_EQ(4, b.slicesize());
  ASSERT_EQ(1, b(2).rowmin());
  ASSERT_EQ(4, b(2).rowmax());
  ASSERT_EQ(1, b(3).rowmin());
  ASSERT_EQ(4, b(3).rowmax());
  ASSERT_EQ(1, b(4).rowmin());
  ASSERT_EQ(4, b(4).rowmax());
  ASSERT_EQ(1, b(5).rowmin());
  ASSERT_EQ(4, b(5).rowmax());
  ASSERT_EQ(colsmin(2), b(2).colmin());
  ASSERT_EQ(colsmax(2), b(2).colmax());
  ASSERT_EQ(colsmin(3), b(3).colmin());
  ASSERT_EQ(colsmax(3), b(3).colmax());
  ASSERT_EQ(colsmin(4), b(4).colmin());
  ASSERT_EQ(colsmax(4), b(4).colmax());
  ASSERT_EQ(colsmin(5), b(5).colmin());
  ASSERT_EQ(colsmax(5), b(5).colmax());
}
TEST_F(test_i3_array, initialize)
{
  ivector colsmin(2, 5);
  colsmin(2) = 4;
  colsmin(3) = 5;
  colsmin(4) = 6;
  colsmin(5) = 7;
  ivector colsmax(2, 5);
  colsmax(2) = 14;
  colsmax(3) = 15;
  colsmax(4) = 16;
  colsmax(5) = 17;

  i3_array a;
  a.allocate(2, 5, 1, 4, colsmin, colsmax);
  a.initialize();

  for (int i = 2; i <= 5; ++i)
  {
    for (int j = 1; j <= 4; ++j)
    {
      for (int k = colsmin(i); k <= colsmax(i); ++k)
      {
        ASSERT_EQ(0, a(i, j, k));
      }
    }
  }
}
TEST_F(test_i3_array, initializeempty)
{
  i3_array a;
  try
  {
    a.initialize();
  }
  catch (const int exit_code)
  {
    FAIL();
  }
}
TEST_F(test_i3_array, allocaterowsmax)
{
  ivector rowsmax(2, 5);
  rowsmax(2) = 14;
  rowsmax(3) = 15;
  rowsmax(4) = 16;
  rowsmax(5) = 17;

  i3_array a;
  a.allocate(2, 5, 1, rowsmax, 10, 20);
  i3_array b;
  b.allocate(a);

  ASSERT_EQ(2, b.slicemin());
  ASSERT_EQ(5, b.slicemax());
  ASSERT_EQ(4, b.slicesize());
  ASSERT_EQ(1, b(2).rowmin());
  ASSERT_EQ(14, b(2).rowmax());
  ASSERT_EQ(1, b(3).rowmin());
  ASSERT_EQ(15, b(3).rowmax());
  ASSERT_EQ(1, b(4).rowmin());
  ASSERT_EQ(16, b(4).rowmax());
  ASSERT_EQ(1, b(5).rowmin());
  ASSERT_EQ(17, b(5).rowmax());
  ASSERT_EQ(10, b(2).colmin());
  ASSERT_EQ(20, b(2).colmax());
  ASSERT_EQ(10, b(3).colmin());
  ASSERT_EQ(20, b(3).colmax());
  ASSERT_EQ(10, b(4).colmin());
  ASSERT_EQ(20, b(4).colmax());
  ASSERT_EQ(10, b(5).colmin());
  ASSERT_EQ(20, b(5).colmax());
}
TEST_F(test_i3_array, constructrowsmax)
{
  ivector rowsmax(2, 5);
  rowsmax(2) = 14;
  rowsmax(3) = 15;
  rowsmax(4) = 16;
  rowsmax(5) = 17;

  i3_array a(2, 5, 1, rowsmax, 10, 20);

  ASSERT_EQ(2, a.slicemin());
  ASSERT_EQ(5, a.slicemax());
  ASSERT_EQ(4, a.slicesize());
  ASSERT_EQ(1, a(2).rowmin());
  ASSERT_EQ(14, a(2).rowmax());
  ASSERT_EQ(1, a(3).rowmin());
  ASSERT_EQ(15, a(3).rowmax());
  ASSERT_EQ(1, a(4).rowmin());
  ASSERT_EQ(16, a(4).rowmax());
  ASSERT_EQ(1, a(5).rowmin());
  ASSERT_EQ(17, a(5).rowmax());
  ASSERT_EQ(10, a(2).colmin());
  ASSERT_EQ(20, a(2).colmax());
  ASSERT_EQ(10, a(3).colmin());
  ASSERT_EQ(20, a(3).colmax());
  ASSERT_EQ(10, a(4).colmin());
  ASSERT_EQ(20, a(4).colmax());
  ASSERT_EQ(10, a(5).colmin());
  ASSERT_EQ(20, a(5).colmax());
}
TEST_F(test_i3_array, allocateinvalidindex)
{
  i3_array empty(5, 2);
  ASSERT_EQ(1, empty.slicemin());
  ASSERT_EQ(0, empty.slicemax());
  ASSERT_EQ(0, empty.slicesize());
}
TEST_F(test_i3_array, elemerror)
{
  ad_exit=&test_ad_exit;

  i3_array a(2, 5);

  ASSERT_ANY_THROW({
    a.elem(1);
  });
  ASSERT_ANY_THROW({
    a.elem(6);
  });
}
TEST_F(test_i3_array, constelemerror)
{
  ad_exit=&test_ad_exit;

  const i3_array a(2, 5);

  ASSERT_ANY_THROW({
    a.elem(1);
  });
  ASSERT_ANY_THROW({
    a.elem(6);
  });
}
TEST_F(test_i3_array, copyconst)
{
  i3_array a(1, 3, 1, 2, 1, 1);

  int d = 2;
  for (int i = 1; i <= 3; ++i)
  {
    for (int j = 1; j <= 2; ++j)
    {
      for (int k = 1; k <= 1; ++k)
      {
        a(i, j, k) = d;
        d += 2;
      }
    }
  }

  const i3_array copy(a);
  d = 2;
  for (int i = 1; i <= 3; ++i)
  {
    for (int j = 1; j <= 2; ++j)
    {
      for (int k = 1; k <= 1; ++k)
      {
        ASSERT_EQ(copy(i, j, k), d);
        d += 2;
      }
    }
  }
}
TEST_F(test_i3_array, empty)
{
  i3_array empty;

  ASSERT_EQ(1, empty.slicemin());
  ASSERT_EQ(0, empty.slicemax());
  ASSERT_EQ(0, empty.slicesize());
}
TEST_F(test_i3_array, assignerror)
{
  ad_exit=&test_ad_exit;

  i3_array a(2, 5);

  ASSERT_ANY_THROW({
    i3_array b(1, 5);
    a = b;
  });
  ASSERT_ANY_THROW({
    i3_array b(2, 6);
    a = b;
  });
}
TEST_F(test_i3_array, assign)
{
  i3_array a(1, 3, 1, 2, 1, 1);

  int d = 2;
  for (int i = 1; i <= 3; ++i)
  {
    for (int j = 1; j <= 2; ++j)
    {
      for (int k = 1; k <= 1; ++k)
      {
        a(i, j, k) = d;
        d += 2;
      }
    }
  }

  i3_array b(1, 3, 1, 2, 1, 1);
  b = a;

  for (int i = 1; i <= 3; ++i)
  {
    for (int j = 1; j <= 2; ++j)
    {
      for (int k = 1; k <= 1; ++k)
      {
        ASSERT_EQ(b(i, j, k), a(i, j, k));
      }
    }
  }
}
TEST_F(test_i3_array, assignsinglevalue)
{
  i3_array a(1, 3, 1, 2, 1, 1);

  a = 5;

  for (int i = 1; i <= 3; ++i)
  {
    for (int j = 1; j <= 2; ++j)
    {
      for (int k = 1; k <= 1; ++k)
      {
        ASSERT_EQ(a(i, j, k), 5);
      }
    }
  }
}
TEST_F(test_i3_array, constructintintintivectorintimatrix)
{
  ivector rows(1, 3);
  rows(1) = 3;
  rows(2) = 4;
  rows(3) = 5;
  imatrix columns(1, 3);
  columns(1).allocate(2, rows(1));
  columns(2).allocate(2, rows(2));
  columns(3).allocate(2, rows(3));
  i3_array a(1, 3, 2, rows, 3, columns);

  ASSERT_EQ(1, a.slicemin());
  ASSERT_EQ(3, a.slicemax());
  ASSERT_EQ(3, a.slicesize());

  ASSERT_EQ(2, a(1).rowmin());
  ASSERT_EQ(rows(1), a(1).rowmax());
  ASSERT_EQ(rows(1) - 2 + 1, a(1).rowsize());
  ASSERT_EQ(2, a(2).rowmin());
  ASSERT_EQ(rows(2), a(2).rowmax());
  ASSERT_EQ(rows(2) - 2 + 1, a(2).rowsize());
  ASSERT_EQ(2, a(3).rowmin());
  ASSERT_EQ(rows(3), a(3).rowmax());
  ASSERT_EQ(rows(3) - 2 + 1, a(3).rowsize());
}
TEST_F(test_i3_array, invalidintintintivectorintimatrix)
{
  ivector rows;
  imatrix columns;
  i3_array a(3, 1, 2, rows, 3, columns);

  ASSERT_EQ(1, a.slicemin());
  ASSERT_EQ(0, a.slicemax());
  ASSERT_EQ(0, a.slicesize());
}
TEST_F(test_i3_array, intintimatrix)
{
  imatrix indexes(1, 2, 1, 4);
  i3_array a(1, 2, indexes);

  ASSERT_EQ(1, a.slicemin());
  ASSERT_EQ(2, a.slicemax());
  ASSERT_EQ(2, a.slicesize());
  ASSERT_EQ(&indexes(1), &a.elem(1).elem(1));
  ASSERT_EQ(&indexes(2), &a.elem(1).elem(2));
  ASSERT_EQ(&indexes(1), &a.elem(2).elem(1));
  ASSERT_EQ(&indexes(2), &a.elem(2).elem(2));
}
TEST_F(test_i3_array, invalidintintimatrix)
{
  imatrix indexes;
  i3_array a(2, 1, indexes);

  ASSERT_EQ(1, a.slicemin());
  ASSERT_EQ(0, a.slicemax());
  ASSERT_EQ(0, a.slicesize());
}
TEST_F(test_i3_array, intintimatrixnull)
{
  imatrix indexes;
  i3_array a(1, 2, indexes);

  ASSERT_EQ(1, a.slicemin());
  ASSERT_EQ(2, a.slicemax());
  ASSERT_EQ(2, a.slicesize());
  ASSERT_FALSE(allocated(a(1)));
  ASSERT_FALSE(allocated(a(2)));
}
