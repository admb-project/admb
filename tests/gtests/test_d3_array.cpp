#include <gtest/gtest.h>
#include <cmath>
#include "fvar.hpp"

class test_d3_array: public ::testing::Test {};

TEST_F(test_d3_array, pow)
{
  d3_array a(1, 2, 1, 2, 1, 2);
  a(1) = 1;
  a(2) = 2;

  d3_array ret = pow(a, 3);
  ASSERT_EQ(1, ret(1, 1, 1));
  ASSERT_EQ(1, ret(1, 1, 2));
  ASSERT_EQ(1, ret(1, 2, 1));
  ASSERT_EQ(1, ret(1, 2, 2));
  ASSERT_EQ(8, ret(2, 1, 1));
  ASSERT_EQ(8, ret(2, 1, 2));
  ASSERT_EQ(8, ret(2, 2, 1));
  ASSERT_EQ(8, ret(2, 2, 2));
}
TEST_F(test_d3_array, cube)
{
  d3_array a(1, 2, 1, 2, 1, 2);
  a(1) = 1;
  a(2) = 2;

  d3_array ret = cube(a);
  ASSERT_EQ(1, ret(1, 1, 1));
  ASSERT_EQ(1, ret(1, 1, 2));
  ASSERT_EQ(1, ret(1, 2, 1));
  ASSERT_EQ(1, ret(1, 2, 2));
  ASSERT_EQ(8, ret(2, 1, 1));
  ASSERT_EQ(8, ret(2, 1, 2));
  ASSERT_EQ(8, ret(2, 2, 1));
  ASSERT_EQ(8, ret(2, 2, 2));
}
TEST_F(test_d3_array, division)
{
  d3_array a(1, 2, 1, 2, 1, 2);

  double d = 2.0;
  for (int i = 1; i <= 2; ++i)
  {
    for (int j = 1; j <= 2; ++j)
    {
      for (int k = 1; k <= 2; ++k)
      {
        a(i, j, k) = d;
        d += 2.0;
      }
    }
  }

  d3_array ret = a / 2.0;

  d = 2.0;
  for (int i = 1; i <= 2; ++i)
  {
    for (int j = 1; j <= 2; ++j)
    {
      for (int k = 1; k <= 2; ++k)
      {
        ASSERT_DOUBLE_EQ(d / 2.0, ret(i, j, k));
        d += 2.0;
      }
    }
  }
}
TEST_F(test_d3_array, uiostream)
{
  d3_array a(1, 2, 1, 2, 1, 2);

  double d = 2.0;
  for (int i = 1; i <= 2; ++i)
  {
    for (int j = 1; j <= 2; ++j)
    {
      for (int k = 1; k <= 2; ++k)
      {
        a(i, j, k) = d;
        d += 2.0;
      }
    }
  }

  uostream uos("uos.txt");
  uos << a;
  uos.close();

  d3_array ret(1, 2, 1, 2, 1, 2);

  uistream uis("uos.txt");
  uis >> ret;
  uis.close();

  d = 2.0;
  for (int i = 1; i <= 2; ++i)
  {
    for (int j = 1; j <= 2; ++j)
    {
      for (int k = 1; k <= 2; ++k)
      {
        ASSERT_DOUBLE_EQ(a(i, j, k), ret(i, j, k));
        d += 2.0;
      }
    }
  }
}
TEST_F(test_d3_array, division_member)
{
  d3_array a(1, 2, 1, 2, 1, 2);

  double d = 2.0;
  for (int i = 1; i <= 2; ++i)
  {
    for (int j = 1; j <= 2; ++j)
    {
      for (int k = 1; k <= 2; ++k)
      {
        a(i, j, k) = d;
        d += 2.0;
      }
    }
  }

  a /= 2.0;

  d = 2.0;
  for (int i = 1; i <= 2; ++i)
  {
    for (int j = 1; j <= 2; ++j)
    {
      for (int k = 1; k <= 2; ++k)
      {
        ASSERT_DOUBLE_EQ(d / 2.0, a(i, j, k));
        d += 2.0;
      }
    }
  }
}
TEST_F(test_d3_array, mfexp)
{
  d3_array a(1, 2, 1, 2, 1, 2);

  double d = 2.0;
  for (int i = 1; i <= 2; ++i)
  {
    for (int j = 1; j <= 2; ++j)
    {
      for (int k = 1; k <= 2; ++k)
      {
        a(i, j, k) = d;
        d += 2.0;
      }
    }
  }

  d3_array ret = mfexp(a);

  d = 2.0;
  for (int i = 1; i <= 2; ++i)
  {
    for (int j = 1; j <= 2; ++j)
    {
      for (int k = 1; k <= 2; ++k)
      {
        ASSERT_DOUBLE_EQ(mfexp(d), ret(i, j, k));
        d += 2.0;
      }
    }
  }
}
TEST_F(test_d3_array, mfexp_with_bounds)
{
  d3_array a(1, 2, 1, 2, 1, 2);

  double d = 2.0;
  for (int i = 1; i <= 2; ++i)
  {
    for (int j = 1; j <= 2; ++j)
    {
      for (int k = 1; k <= 2; ++k)
      {
        a(i, j, k) = d;
        d += 2.0;
      }
    }
  }

  d3_array ret = mfexp(a, 5);

  d = 2.0;
  for (int i = 1; i <= 2; ++i)
  {
    for (int j = 1; j <= 2; ++j)
    {
      for (int k = 1; k <= 2; ++k)
      {
        ASSERT_DOUBLE_EQ(mfexp(d, 5), ret(i, j, k));
        d += 2.0;
      }
    }
  }
}
TEST_F(test_d3_array, log)
{
  d3_array a(1, 2, 1, 2, 1, 2);

  double d = 2.0;
  for (int i = 1; i <= 2; ++i)
  {
    for (int j = 1; j <= 2; ++j)
    {
      for (int k = 1; k <= 2; ++k)
      {
        a(i, j, k) = d;
        d += 2.0;
      }
    }
  }

  d3_array ret = log(a);

  d = 2.0;
  for (int i = 1; i <= 2; ++i)
  {
    for (int j = 1; j <= 2; ++j)
    {
      for (int k = 1; k <= 2; ++k)
      {
        ASSERT_DOUBLE_EQ(std::log(d), ret(i, j, k));
        d += 2.0;
      }
    }
  }
}
TEST_F(test_d3_array, exp)
{
  d3_array a(1, 2, 1, 2, 1, 2);

  double d = 2.0;
  for (int i = 1; i <= 2; ++i)
  {
    for (int j = 1; j <= 2; ++j)
    {
      for (int k = 1; k <= 2; ++k)
      {
        a(i, j, k) = d;
        d += 2.0;
      }
    }
  }

  d3_array ret = exp(a);

  d = 2.0;
  for (int i = 1; i <= 2; ++i)
  {
    for (int j = 1; j <= 2; ++j)
    {
      for (int k = 1; k <= 2; ++k)
      {
        ASSERT_DOUBLE_EQ(std::exp(d), ret(i, j, k));
        d += 2.0;
      }
    }
  }
}
TEST_F(test_d3_array, mean)
{
  d3_array a(1, 2, 1, 2, 1, 2);
  a(1, 1, 1) = 5;
  a(1, 1, 2) = 2;
  a(1, 2, 1) = 3;
  a(1, 2, 2) = 4;
  a(2, 1, 1) = 5;
  a(2, 1, 2) = 6;
  a(2, 2, 1) = 7;
  a(2, 2, 2) = 8;

  ASSERT_DOUBLE_EQ(5, mean(a));
}
TEST_F(test_d3_array, size_count)
{
  d3_array a(1, 4, 1, 3, 1, 2);

  ASSERT_EQ(24, size_count(a));
}
TEST_F(test_d3_array, io)
{
  d3_array a(1, 2, 1, 2, 1, 2);
  a(1, 1, 1) = 5;
  a(1, 1, 2) = 2;
  a(1, 2, 1) = 3;
  a(1, 2, 2) = 4;
  a(2, 1, 1) = 5;
  a(2, 1, 2) = 6;
  a(2, 2, 1) = 7;
  a(2, 2, 2) = 8;

  ofstream ofs("d3io.txt");
  ofs << a;
  ofs.close();

  d3_array b(1, 2, 1, 2, 1, 2);
  b.initialize();

  ifstream ifs("d3io.txt");
  ifs >> b;
  ifs.close();

  ASSERT_DOUBLE_EQ(a(1, 1, 1), b(1, 1, 1));
  ASSERT_DOUBLE_EQ(a(1, 1, 2), b(1, 1, 2));
  ASSERT_DOUBLE_EQ(a(1, 2, 1), b(1, 2, 1));
  ASSERT_DOUBLE_EQ(a(1, 2, 2), b(1, 2, 2));
  ASSERT_DOUBLE_EQ(a(2, 1, 1), b(2, 1, 1));
  ASSERT_DOUBLE_EQ(a(2, 1, 2), b(2, 1, 2));
  ASSERT_DOUBLE_EQ(a(2, 2, 1), b(2, 2, 1));
  ASSERT_DOUBLE_EQ(a(2, 2, 2), b(2, 2, 2));
}
