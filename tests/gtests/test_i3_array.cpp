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
