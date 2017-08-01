#include <gtest/gtest.h>
#include <cmath>
#include "fvar.hpp"

class test_i5_array: public ::testing::Test {};

TEST_F(test_i5_array, default)
{
  i5_array a;
  ASSERT_EQ(0, a.hslicesize());
  ASSERT_EQ(1, a.indexmin());
  ASSERT_EQ(0, a.indexmax());
}
TEST_F(test_i5_array, 1xint)
{
  i5_array a(2, 5);
  ASSERT_EQ(4, a.hslicesize());
  ASSERT_EQ(2, a.indexmin());
  ASSERT_EQ(5, a.indexmax());
  ASSERT_EQ(1, a(2).indexmin());
  ASSERT_EQ(0, a(2).indexmax());
  ASSERT_EQ(1, a(3).indexmin());
  ASSERT_EQ(0, a(3).indexmax());
  ASSERT_EQ(1, a(4).indexmin());
  ASSERT_EQ(0, a(4).indexmax());
  ASSERT_EQ(1, a(5).indexmin());
  ASSERT_EQ(0, a(5).indexmax());
}
TEST_F(test_i5_array, 1xintinvalid)
{
  i5_array a(5, 2);
  ASSERT_EQ(0, a.hslicesize());
  ASSERT_EQ(1, a.indexmin());
  ASSERT_EQ(0, a.indexmax());
}
TEST_F(test_i5_array, 5xint)
{
  i5_array a;
  a.allocate(1, 5, 1, 4, 1, 3, 1, 2, 1, 1);
  ASSERT_EQ(5, a.hslicesize());
  ASSERT_EQ(1, a.indexmin());
  ASSERT_EQ(5, a.indexmax());
  for (int i = 1; i <= 5; ++i)
  {
    ASSERT_EQ(1, a(i).indexmin());
    ASSERT_EQ(4, a(i).indexmax());
    for (int j = 1; j <= 4; ++j)
    {
      ASSERT_EQ(1, a(i, j).indexmin());
      ASSERT_EQ(3, a(i, j).indexmax());
      for (int k = 1; k <= 3; ++k)
      {
        ASSERT_EQ(1, a(i, j, k).indexmin());
        ASSERT_EQ(2, a(i, j, k).indexmax());
        for (int w = 1; w <= 2; ++w)
        {
          ASSERT_EQ(1, a(i, j, k, w).indexmin());
          ASSERT_EQ(1, a(i, j, k, w).indexmax());
        }
      }
    }
  }
}
TEST_F(test_i5_array, allocate1xint)
{
  i5_array a;
  a.allocate(2, 5);
  ASSERT_EQ(4, a.hslicesize());
  ASSERT_EQ(2, a.indexmin());
  ASSERT_EQ(5, a.indexmax());
  ASSERT_EQ(1, a(2).indexmin());
  ASSERT_EQ(0, a(2).indexmax());
  ASSERT_EQ(1, a(3).indexmin());
  ASSERT_EQ(0, a(3).indexmax());
  ASSERT_EQ(1, a(4).indexmin());
  ASSERT_EQ(0, a(4).indexmax());
  ASSERT_EQ(1, a(5).indexmin());
  ASSERT_EQ(0, a(5).indexmax());
}
TEST_F(test_i5_array, deallocate)
{
  i5_array a;
  a.allocate(1, 5, 1, 4, 1, 3, 1, 2, 1, 1);
  a.deallocate();
  ASSERT_EQ(0, a.hslicesize());
  ASSERT_EQ(1, a.indexmin());
  ASSERT_EQ(0, a.indexmax());
}
TEST_F(test_i5_array, equals)
{
  i5_array a;
  a.allocate(1, 5, 1, 4, 1, 3, 1, 2, 1, 1);

  int count = 0;
  for (int i = 1; i <= 5; ++i)
  {
    for (int j = 1; j <= 4; ++j)
    {
      for (int k = 1; k <= 3; ++k)
      {
        for (int w = 1; w <= 2; ++w)
        {
          a(i, j, k, w, 1) = count;
          ++count;
        }
      }
    }
  }
  count = 0;
  for (int i = 1; i <= 5; ++i)
  {
    for (int j = 1; j <= 4; ++j)
    {
      for (int k = 1; k <= 3; ++k)
      {
        for (int w = 1; w <= 2; ++w)
        {
          ASSERT_EQ(a(i, j, k, w, 1), count);
          ++count;
        }
      }
    }
  }
}
TEST_F(test_i5_array, elemerror)
{
  i5_array a(2, 5);
  ASSERT_ANY_THROW({
    a.elem(1);
  });
  ASSERT_ANY_THROW({
    a.elem(6);
  });
}
TEST_F(test_i5_array, elembracketerror)
{
  i5_array a(2, 5);
  ASSERT_ANY_THROW({
    a[1];
  });
  ASSERT_ANY_THROW({
    a[6];
  });
}
TEST_F(test_i5_array, constelemerror)
{
  const i5_array a(2, 5);
  ASSERT_ANY_THROW({
    a.elem(1);
  });
  ASSERT_ANY_THROW({
    a.elem(6);
  });
}
