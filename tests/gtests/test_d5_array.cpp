#include <gtest/gtest.h>
#include <cmath>
#include "fvar.hpp"

class test_d5_array: public ::testing::Test {};

TEST_F(test_d5_array, allocate_copy_full)
{
  d5_array a;
  a.allocate(3, 6,
             1, 2,
             1, 2,
             1, 2,
             1, 2
            );
  ASSERT_EQ(a.size(), 4);
  ASSERT_EQ(a.indexmin(), 3);
  ASSERT_EQ(a.indexmax(), 6);

  d5_array b;
  b.allocate(a);

  ASSERT_EQ(b.size(), 4);
  ASSERT_EQ(b.indexmin(), 3);
  ASSERT_EQ(b.indexmax(), 6);
}
TEST_F(test_d5_array, allocate_vector)
{
  d5_array a;
  a.allocate(3, 6);

  ASSERT_EQ(a.size(), 4);
  ASSERT_EQ(a.indexmin(), 3);
  ASSERT_EQ(a.indexmax(), 6);
}
TEST_F(test_d5_array, division_equal_operator)
{
  d5_array a(1, 2, 1, 2, 1, 2, 1, 2, 1, 2);

  double d = 2.0;
  for (int i = 1; i <= 2; ++i)
  {
    for (int j = 1; j <= 2; ++j)
    {
      for (int k = 1; k <= 2; ++k)
      {
        for (int l = 1; l <= 2; ++l)
        {
          for (int m = 1; m <= 2; ++m)
          {
            a(i, j, k, l, m) = d;
            d += 2.0;
          }
        }
      }
    }
  }

  d5_array result = a / 0.5;

  d = 2.0;
  for (int i = 1; i <= 2; ++i)
  {
    for (int j = 1; j <= 2; ++j)
    {
      for (int k = 1; k <= 2; ++k)
      {
        for (int l = 1; l <= 2; ++l)
        {
          for (int m = 1; m <= 2; ++m)
          {
            ASSERT_DOUBLE_EQ(d / 0.5 , result(i, j, k, l, m));
            d += 2.0;
          }
        }
      }
    }
  }
}
TEST_F(test_d5_array, division_equal_operator2)
{
  d5_array a(1, 2, 1, 2, 1, 2, 1, 2, 1, 2);

  double d = 2.0;
  for (int i = 1; i <= 2; ++i)
  {
    for (int j = 1; j <= 2; ++j)
    {
      for (int k = 1; k <= 2; ++k)
      {
        for (int l = 1; l <= 2; ++l)
        {
          for (int m = 1; m <= 2; ++m)
          {
            a(i, j, k, l, m) = d;
            d += 2.0;
          }
        }
      }
    }
  }

  a /= 0.5;

  d = 2.0;
  for (int i = 1; i <= 2; ++i)
  {
    for (int j = 1; j <= 2; ++j)
    {
      for (int k = 1; k <= 2; ++k)
      {
        for (int l = 1; l <= 2; ++l)
        {
          for (int m = 1; m <= 2; ++m)
          {
            ASSERT_DOUBLE_EQ(d / 0.5 , a(i, j, k, l, m));
            d += 2.0;
          }
        }
      }
    }
  }
}
TEST_F(test_d5_array, inputoutput)
{
  d5_array a(1, 2, 1, 2, 1, 2, 1, 2, 1, 2);

  double d = 2.0;
  for (int i = 1; i <= 2; ++i)
  {
    for (int j = 1; j <= 2; ++j)
    {
      for (int k = 1; k <= 2; ++k)
      {
        for (int l = 1; l <= 2; ++l)
        {
          for (int m = 1; m <= 2; ++m)
          {
            a(i, j, k, l, m) = d;
            d += 2.0;
          }
        }
      }
    }
  }

  ofstream ofs("d5_array.txt");
  ofs << a;
  ofs.close();

  d5_array b(1, 2, 1, 2, 1, 2, 1, 2, 1, 2);

  ifstream ifs("d5_array.txt");
  ifs >> b;
  ifs.close();

  for (int i = 1; i <= 2; ++i)
  {
    for (int j = 1; j <= 2; ++j)
    {
      for (int k = 1; k <= 2; ++k)
      {
        for (int l = 1; l <= 2; ++l)
        {
          for (int m = 1; m <= 2; ++m)
          {
            ASSERT_DOUBLE_EQ(a(i, j, k, l, m), b(i, j, k, l, m));
          }
        }
      }
    }
  }
}
