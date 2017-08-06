#include <gtest/gtest.h>
#include <cmath>
#include "fvar.hpp"

extern "C"
{
  void test_ad_exit(const int exit_code);
}

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
  a(1, 1, 1) = 1;
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
TEST_F(test_d3_array, sliceexit)
{
  ad_exit=&test_ad_exit;

  d3_array a(1, 2, 1, 2, 1, 2);

  ASSERT_ANY_THROW({
    a(3, 1, 1);
  });
  ASSERT_ANY_THROW({
    a(0, 1, 1);
  });
  ASSERT_ANY_THROW({
    a(3, 1);
  });
  ASSERT_ANY_THROW({
    a(0, 1);
  });
  ASSERT_ANY_THROW({
    a(3);
  });
  ASSERT_ANY_THROW({
    a(0);
  });
  ASSERT_ANY_THROW({
    a[3];
  });
  ASSERT_ANY_THROW({
    a[0];
  });
}
TEST_F(test_d3_array, sqr)
{
  d3_array a(1, 2, 1, 2, 1, 2);
  a(1, 1, 1) = 5;
  a(1, 1, 2) = 2;
  a(1, 2, 1) = -3;
  a(1, 2, 2) = 4;
  a(2, 1, 1) = -5;
  a(2, 1, 2) = -6;
  a(2, 2, 1) = 7;
  a(2, 2, 2) = 8;

  d3_array ret = sqr(a);

  ASSERT_DOUBLE_EQ(25 ,ret(1, 1, 1));
  ASSERT_DOUBLE_EQ(4, ret(1, 1, 2));
  ASSERT_DOUBLE_EQ(9, ret(1, 2, 1));
  ASSERT_DOUBLE_EQ(16, ret(1, 2, 2));
  ASSERT_DOUBLE_EQ(25 ,ret(2, 1, 1));
  ASSERT_DOUBLE_EQ(36 ,ret(2, 1, 2));
  ASSERT_DOUBLE_EQ(49 ,ret(2, 2, 1));
  ASSERT_DOUBLE_EQ(64 ,ret(2, 2, 2));
}
TEST_F(test_d3_array, sin)
{
  d3_array a(1, 2, 1, 2, 1, 2);
  a(1, 1, 1) = 1;
  a(1, 1, 2) = 2;
  a(1, 2, 1) = 3;
  a(1, 2, 2) = 4;
  a(2, 1, 1) = 5;
  a(2, 1, 2) = 6;
  a(2, 2, 1) = 7;
  a(2, 2, 2) = 8;

  d3_array ret = sin(a);

  ASSERT_DOUBLE_EQ(std::sin(1), ret(1, 1, 1));
  ASSERT_DOUBLE_EQ(std::sin(2), ret(1, 1, 2));
  ASSERT_DOUBLE_EQ(std::sin(3), ret(1, 2, 1));
  ASSERT_DOUBLE_EQ(std::sin(4), ret(1, 2, 2));
  ASSERT_DOUBLE_EQ(std::sin(5), ret(2, 1, 1));
  ASSERT_DOUBLE_EQ(std::sin(6), ret(2, 1, 2));
  ASSERT_DOUBLE_EQ(std::sin(7), ret(2, 2, 1));
  ASSERT_DOUBLE_EQ(std::sin(8), ret(2, 2, 2));
}
TEST_F(test_d3_array, cos)
{
  d3_array a(1, 2, 1, 2, 1, 2);
  a(1, 1, 1) = 1;
  a(1, 1, 2) = 2;
  a(1, 2, 1) = 3;
  a(1, 2, 2) = 4;
  a(2, 1, 1) = 5;
  a(2, 1, 2) = 6;
  a(2, 2, 1) = 7;
  a(2, 2, 2) = 8;

  d3_array ret = cos(a);

  ASSERT_DOUBLE_EQ(std::cos(1), ret(1, 1, 1));
  ASSERT_DOUBLE_EQ(std::cos(2), ret(1, 1, 2));
  ASSERT_DOUBLE_EQ(std::cos(3), ret(1, 2, 1));
  ASSERT_DOUBLE_EQ(std::cos(4), ret(1, 2, 2));
  ASSERT_DOUBLE_EQ(std::cos(5), ret(2, 1, 1));
  ASSERT_DOUBLE_EQ(std::cos(6), ret(2, 1, 2));
  ASSERT_DOUBLE_EQ(std::cos(7), ret(2, 2, 1));
  ASSERT_DOUBLE_EQ(std::cos(8), ret(2, 2, 2));
}
TEST_F(test_d3_array, tan)
{
  d3_array a(1, 2, 1, 2, 1, 2);
  a(1, 1, 1) = 1;
  a(1, 1, 2) = 2;
  a(1, 2, 1) = 3;
  a(1, 2, 2) = 4;
  a(2, 1, 1) = 5;
  a(2, 1, 2) = 6;
  a(2, 2, 1) = 7;
  a(2, 2, 2) = 8;

  d3_array ret = tan(a);

  ASSERT_DOUBLE_EQ(std::tan(1), ret(1, 1, 1));
  ASSERT_DOUBLE_EQ(std::tan(2), ret(1, 1, 2));
  ASSERT_DOUBLE_EQ(std::tan(3), ret(1, 2, 1));
  ASSERT_DOUBLE_EQ(std::tan(4), ret(1, 2, 2));
  ASSERT_DOUBLE_EQ(std::tan(5), ret(2, 1, 1));
  ASSERT_DOUBLE_EQ(std::tan(6), ret(2, 1, 2));
  ASSERT_DOUBLE_EQ(std::tan(7), ret(2, 2, 1));
  ASSERT_DOUBLE_EQ(std::tan(8), ret(2, 2, 2));
}
TEST_F(test_d3_array, elem_prod)
{
  d3_array a(1, 2, 1, 2, 1, 2);
  a(1, 1, 1) = 1;
  a(1, 1, 2) = 2;
  a(1, 2, 1) = 3;
  a(1, 2, 2) = 4;
  a(2, 1, 1) = 5;
  a(2, 1, 2) = 6;
  a(2, 2, 1) = 7;
  a(2, 2, 2) = 8;

  d3_array b(1, 2, 1, 2, 1, 2);
  b(1, 1, 1) = 8;
  b(1, 1, 2) = 7;
  b(1, 2, 1) = 6;
  b(1, 2, 2) = 5;
  b(2, 1, 1) = 4;
  b(2, 1, 2) = 3;
  b(2, 2, 1) = 2;
  b(2, 2, 2) = 1;

  d3_array ret = elem_prod(a, b);

  ASSERT_DOUBLE_EQ(a(1, 1, 1) * b(1, 1, 1), ret(1, 1, 1));
  ASSERT_DOUBLE_EQ(a(1, 1, 2) * b(1, 1, 2), ret(1, 1, 2));
  ASSERT_DOUBLE_EQ(a(1, 2, 1) * b(1, 2, 1), ret(1, 2, 1));
  ASSERT_DOUBLE_EQ(a(1, 2, 2) * b(1, 2, 2), ret(1, 2, 2));
  ASSERT_DOUBLE_EQ(a(2, 1, 1) * b(2, 1, 1), ret(2, 1, 1));
  ASSERT_DOUBLE_EQ(a(2, 1, 2) * b(2, 1, 2), ret(2, 1, 2));
  ASSERT_DOUBLE_EQ(a(2, 2, 1) * b(2, 2, 1), ret(2, 2, 1));
  ASSERT_DOUBLE_EQ(a(2, 2, 2) * b(2, 2, 2), ret(2, 2, 2));
}
TEST_F(test_d3_array, elem_div)
{
  d3_array a(1, 2, 1, 2, 1, 2);
  a(1, 1, 1) = 1;
  a(1, 1, 2) = 2;
  a(1, 2, 1) = 3;
  a(1, 2, 2) = 4;
  a(2, 1, 1) = 5;
  a(2, 1, 2) = 6;
  a(2, 2, 1) = 7;
  a(2, 2, 2) = 8;

  d3_array b(1, 2, 1, 2, 1, 2);
  b(1, 1, 1) = 8;
  b(1, 1, 2) = 7;
  b(1, 2, 1) = 6;
  b(1, 2, 2) = 5;
  b(2, 1, 1) = 4;
  b(2, 1, 2) = 3;
  b(2, 2, 1) = 2;
  b(2, 2, 2) = 1;

  d3_array ret = elem_div(a, b);

  ASSERT_DOUBLE_EQ(a(1, 1, 1) / b(1, 1, 1), ret(1, 1, 1));
  ASSERT_DOUBLE_EQ(a(1, 1, 2) / b(1, 1, 2), ret(1, 1, 2));
  ASSERT_DOUBLE_EQ(a(1, 2, 1) / b(1, 2, 1), ret(1, 2, 1));
  ASSERT_DOUBLE_EQ(a(1, 2, 2) / b(1, 2, 2), ret(1, 2, 2));
  ASSERT_DOUBLE_EQ(a(2, 1, 1) / b(2, 1, 1), ret(2, 1, 1));
  ASSERT_DOUBLE_EQ(a(2, 1, 2) / b(2, 1, 2), ret(2, 1, 2));
  ASSERT_DOUBLE_EQ(a(2, 2, 1) / b(2, 2, 1), ret(2, 2, 1));
  ASSERT_DOUBLE_EQ(a(2, 2, 2) / b(2, 2, 2), ret(2, 2, 2));
}
TEST_F(test_d3_array, addition)
{
  d3_array a(1, 2, 1, 2, 1, 2);
  a(1, 1, 1) = 1;
  a(1, 1, 2) = 2;
  a(1, 2, 1) = 3;
  a(1, 2, 2) = 4;
  a(2, 1, 1) = 5;
  a(2, 1, 2) = 6;
  a(2, 2, 1) = 7;
  a(2, 2, 2) = 8;

  d3_array b(1, 2, 1, 2, 1, 2);
  b(1, 1, 1) = 8;
  b(1, 1, 2) = 7;
  b(1, 2, 1) = 6;
  b(1, 2, 2) = 5;
  b(2, 1, 1) = 4;
  b(2, 1, 2) = 3;
  b(2, 2, 1) = 2;
  b(2, 2, 2) = 1;

  d3_array ret = a + b;

  ASSERT_DOUBLE_EQ(a(1, 1, 1) + b(1, 1, 1), ret(1, 1, 1));
  ASSERT_DOUBLE_EQ(a(1, 1, 2) + b(1, 1, 2), ret(1, 1, 2));
  ASSERT_DOUBLE_EQ(a(1, 2, 1) + b(1, 2, 1), ret(1, 2, 1));
  ASSERT_DOUBLE_EQ(a(1, 2, 2) + b(1, 2, 2), ret(1, 2, 2));
  ASSERT_DOUBLE_EQ(a(2, 1, 1) + b(2, 1, 1), ret(2, 1, 1));
  ASSERT_DOUBLE_EQ(a(2, 1, 2) + b(2, 1, 2), ret(2, 1, 2));
  ASSERT_DOUBLE_EQ(a(2, 2, 1) + b(2, 2, 1), ret(2, 2, 1));
  ASSERT_DOUBLE_EQ(a(2, 2, 2) + b(2, 2, 2), ret(2, 2, 2));
}
TEST_F(test_d3_array, substraction)
{
  d3_array a(1, 2, 1, 2, 1, 2);
  a(1, 1, 1) = 1;
  a(1, 1, 2) = 2;
  a(1, 2, 1) = 3;
  a(1, 2, 2) = 4;
  a(2, 1, 1) = 5;
  a(2, 1, 2) = 6;
  a(2, 2, 1) = 7;
  a(2, 2, 2) = 8;

  d3_array b(1, 2, 1, 2, 1, 2);
  b(1, 1, 1) = 8;
  b(1, 1, 2) = 7;
  b(1, 2, 1) = 6;
  b(1, 2, 2) = 5;
  b(2, 1, 1) = 4;
  b(2, 1, 2) = 3;
  b(2, 2, 1) = 2;
  b(2, 2, 2) = 1;

  d3_array ret = a - b;

  ASSERT_DOUBLE_EQ(a(1, 1, 1) - b(1, 1, 1), ret(1, 1, 1));
  ASSERT_DOUBLE_EQ(a(1, 1, 2) - b(1, 1, 2), ret(1, 1, 2));
  ASSERT_DOUBLE_EQ(a(1, 2, 1) - b(1, 2, 1), ret(1, 2, 1));
  ASSERT_DOUBLE_EQ(a(1, 2, 2) - b(1, 2, 2), ret(1, 2, 2));
  ASSERT_DOUBLE_EQ(a(2, 1, 1) - b(2, 1, 1), ret(2, 1, 1));
  ASSERT_DOUBLE_EQ(a(2, 1, 2) - b(2, 1, 2), ret(2, 1, 2));
  ASSERT_DOUBLE_EQ(a(2, 2, 1) - b(2, 2, 1), ret(2, 2, 1));
  ASSERT_DOUBLE_EQ(a(2, 2, 2) - b(2, 2, 2), ret(2, 2, 2));
}
TEST_F(test_d3_array, value_addition)
{
  d3_array a(1, 2, 1, 2, 1, 2);
  a(1, 1, 1) = 1;
  a(1, 1, 2) = 2;
  a(1, 2, 1) = 3;
  a(1, 2, 2) = 4;
  a(2, 1, 1) = 5;
  a(2, 1, 2) = 6;
  a(2, 2, 1) = 7;
  a(2, 2, 2) = 8;

  double value = -4.5;

  d3_array ret = value + a;

  ASSERT_DOUBLE_EQ(value + a(1, 1, 1), ret(1, 1, 1));
  ASSERT_DOUBLE_EQ(value + a(1, 1, 2), ret(1, 1, 2));
  ASSERT_DOUBLE_EQ(value + a(1, 2, 1), ret(1, 2, 1));
  ASSERT_DOUBLE_EQ(value + a(1, 2, 2), ret(1, 2, 2));
  ASSERT_DOUBLE_EQ(value + a(2, 1, 1), ret(2, 1, 1));
  ASSERT_DOUBLE_EQ(value + a(2, 1, 2), ret(2, 1, 2));
  ASSERT_DOUBLE_EQ(value + a(2, 2, 1), ret(2, 2, 1));
  ASSERT_DOUBLE_EQ(value + a(2, 2, 2), ret(2, 2, 2));
}
TEST_F(test_d3_array, value_subtraction)
{
  d3_array a(1, 2, 1, 2, 1, 2);
  a(1, 1, 1) = 1;
  a(1, 1, 2) = 2;
  a(1, 2, 1) = 3;
  a(1, 2, 2) = 4;
  a(2, 1, 1) = 5;
  a(2, 1, 2) = 6;
  a(2, 2, 1) = 7;
  a(2, 2, 2) = 8;

  double value = -4.5;

  d3_array ret = value - a;

  ASSERT_DOUBLE_EQ(value - a(1, 1, 1), ret(1, 1, 1));
  ASSERT_DOUBLE_EQ(value - a(1, 1, 2), ret(1, 1, 2));
  ASSERT_DOUBLE_EQ(value - a(1, 2, 1), ret(1, 2, 1));
  ASSERT_DOUBLE_EQ(value - a(1, 2, 2), ret(1, 2, 2));
  ASSERT_DOUBLE_EQ(value - a(2, 1, 1), ret(2, 1, 1));
  ASSERT_DOUBLE_EQ(value - a(2, 1, 2), ret(2, 1, 2));
  ASSERT_DOUBLE_EQ(value - a(2, 2, 1), ret(2, 2, 1));
  ASSERT_DOUBLE_EQ(value - a(2, 2, 2), ret(2, 2, 2));
}
TEST_F(test_d3_array, value_addition2)
{
  d3_array a(1, 2, 1, 2, 1, 2);
  a(1, 1, 1) = 1;
  a(1, 1, 2) = 2;
  a(1, 2, 1) = 3;
  a(1, 2, 2) = 4;
  a(2, 1, 1) = 5;
  a(2, 1, 2) = 6;
  a(2, 2, 1) = 7;
  a(2, 2, 2) = 8;

  double value = -4.5;

  d3_array ret = a + value;

  ASSERT_DOUBLE_EQ(a(1, 1, 1) + value, ret(1, 1, 1));
  ASSERT_DOUBLE_EQ(a(1, 1, 2) + value, ret(1, 1, 2));
  ASSERT_DOUBLE_EQ(a(1, 2, 1) + value, ret(1, 2, 1));
  ASSERT_DOUBLE_EQ(a(1, 2, 2) + value, ret(1, 2, 2));
  ASSERT_DOUBLE_EQ(a(2, 1, 1) + value, ret(2, 1, 1));
  ASSERT_DOUBLE_EQ(a(2, 1, 2) + value, ret(2, 1, 2));
  ASSERT_DOUBLE_EQ(a(2, 2, 1) + value, ret(2, 2, 1));
  ASSERT_DOUBLE_EQ(a(2, 2, 2) + value, ret(2, 2, 2));
}
TEST_F(test_d3_array, value_subtraction2)
{
  d3_array a(1, 2, 1, 2, 1, 2);
  a(1, 1, 1) = 1;
  a(1, 1, 2) = 2;
  a(1, 2, 1) = 3;
  a(1, 2, 2) = 4;
  a(2, 1, 1) = 5;
  a(2, 1, 2) = 6;
  a(2, 2, 1) = 7;
  a(2, 2, 2) = 8;

  double value = -4.5;

  d3_array ret = a - value;

  ASSERT_DOUBLE_EQ(a(1, 1, 1) - value, ret(1, 1, 1));
  ASSERT_DOUBLE_EQ(a(1, 1, 2) - value, ret(1, 1, 2));
  ASSERT_DOUBLE_EQ(a(1, 2, 1) - value, ret(1, 2, 1));
  ASSERT_DOUBLE_EQ(a(1, 2, 2) - value, ret(1, 2, 2));
  ASSERT_DOUBLE_EQ(a(2, 1, 1) - value, ret(2, 1, 1));
  ASSERT_DOUBLE_EQ(a(2, 1, 2) - value, ret(2, 1, 2));
  ASSERT_DOUBLE_EQ(a(2, 2, 1) - value, ret(2, 2, 1));
  ASSERT_DOUBLE_EQ(a(2, 2, 2) - value, ret(2, 2, 2));
}
TEST_F(test_d3_array, mulitply_value)
{
  d3_array a(1, 2, 1, 2, 1, 2);
  a(1, 1, 1) = 1;
  a(1, 1, 2) = 2;
  a(1, 2, 1) = 3;
  a(1, 2, 2) = 4;
  a(2, 1, 1) = 5;
  a(2, 1, 2) = 6;
  a(2, 2, 1) = 7;
  a(2, 2, 2) = 8;

  double value = -4.5;

  d3_array ret = a * value;

  ASSERT_DOUBLE_EQ(a(1, 1, 1) * value, ret(1, 1, 1));
  ASSERT_DOUBLE_EQ(a(1, 1, 2) * value, ret(1, 1, 2));
  ASSERT_DOUBLE_EQ(a(1, 2, 1) * value, ret(1, 2, 1));
  ASSERT_DOUBLE_EQ(a(1, 2, 2) * value, ret(1, 2, 2));
  ASSERT_DOUBLE_EQ(a(2, 1, 1) * value, ret(2, 1, 1));
  ASSERT_DOUBLE_EQ(a(2, 1, 2) * value, ret(2, 1, 2));
  ASSERT_DOUBLE_EQ(a(2, 2, 1) * value, ret(2, 2, 1));
  ASSERT_DOUBLE_EQ(a(2, 2, 2) * value, ret(2, 2, 2));
}
TEST_F(test_d3_array, mulitply_value2)
{
  d3_array a(1, 2, 1, 2, 1, 2);
  a(1, 1, 1) = 1;
  a(1, 1, 2) = 2;
  a(1, 2, 1) = 3;
  a(1, 2, 2) = 4;
  a(2, 1, 1) = 5;
  a(2, 1, 2) = 6;
  a(2, 2, 1) = 7;
  a(2, 2, 2) = 8;

  double value = -4.5;

  d3_array ret = value * a;

  ASSERT_DOUBLE_EQ(value * a(1, 1, 1), ret(1, 1, 1));
  ASSERT_DOUBLE_EQ(value * a(1, 1, 2), ret(1, 1, 2));
  ASSERT_DOUBLE_EQ(value * a(1, 2, 1), ret(1, 2, 1));
  ASSERT_DOUBLE_EQ(value * a(1, 2, 2), ret(1, 2, 2));
  ASSERT_DOUBLE_EQ(value * a(2, 1, 1), ret(2, 1, 1));
  ASSERT_DOUBLE_EQ(value * a(2, 1, 2), ret(2, 1, 2));
  ASSERT_DOUBLE_EQ(value * a(2, 2, 1), ret(2, 2, 1));
  ASSERT_DOUBLE_EQ(value * a(2, 2, 2), ret(2, 2, 2));
}
TEST_F(test_d3_array, norm2)
{
  d3_array a(1, 2, 1, 2, 1, 2);
  a(1, 1, 1) = 1;
  a(1, 1, 2) = -2;
  a(1, 2, 1) = 3;
  a(1, 2, 2) = -4;
  a(2, 1, 1) = 5;
  a(2, 1, 2) = -6;
  a(2, 2, 1) = -7;
  a(2, 2, 2) = 8;

  double ret = norm2(a);

  ASSERT_DOUBLE_EQ(204, ret);
  ASSERT_DOUBLE_EQ(204, sumsq(a));
}
TEST_F(test_d3_array, norm)
{
  d3_array a(1, 2, 1, 2, 1, 2);
  a(1, 1, 1) = 1;
  a(1, 1, 2) = -2;
  a(1, 2, 1) = 3;
  a(1, 2, 2) = -4;
  a(2, 1, 1) = 5;
  a(2, 1, 2) = -6;
  a(2, 2, 1) = -7;
  a(2, 2, 2) = 8;

  double ret = norm(a);

  ASSERT_DOUBLE_EQ(std::sqrt(204.0), ret);
}
TEST_F(test_d3_array, square)
{
  d3_array a(1, 2, 1, 2, 1, 2);
  a(1, 1, 1) = 1;
  a(1, 1, 2) = 2;
  a(1, 2, 1) = 3;
  a(1, 2, 2) = 4;
  a(2, 1, 1) = 5;
  a(2, 1, 2) = 6;
  a(2, 2, 1) = 7;
  a(2, 2, 2) = 8;

  d3_array ret = square(a);

  ASSERT_DOUBLE_EQ(std::pow(a(1, 1, 1), 2.0), ret(1, 1, 1));
  ASSERT_DOUBLE_EQ(std::pow(a(1, 1, 2), 2.0), ret(1, 1, 2));
  ASSERT_DOUBLE_EQ(std::pow(a(1, 2, 1), 2.0), ret(1, 2, 1));
  ASSERT_DOUBLE_EQ(std::pow(a(1, 2, 2), 2.0), ret(1, 2, 2));
  ASSERT_DOUBLE_EQ(std::pow(a(2, 1, 1), 2.0), ret(2, 1, 1));
  ASSERT_DOUBLE_EQ(std::pow(a(2, 1, 2), 2.0), ret(2, 1, 2));
  ASSERT_DOUBLE_EQ(std::pow(a(2, 2, 1), 2.0), ret(2, 2, 1));
  ASSERT_DOUBLE_EQ(std::pow(a(2, 2, 2), 2.0), ret(2, 2, 2));
}
TEST_F(test_d3_array, indexerror)
{
  ad_exit=&test_ad_exit;

  const d3_array a(1, 2, 1, 2, 1, 2);

  ASSERT_ANY_THROW({
    a[0];
  });
  ASSERT_ANY_THROW({
    a[3];
  });
  ASSERT_ANY_THROW({
    a(0);
  });
  ASSERT_ANY_THROW({
    a(3);
  });
  ASSERT_ANY_THROW({
    a(0, 1);
  });
  ASSERT_ANY_THROW({
    a(3, 1);
  });
  ASSERT_ANY_THROW({
    a(0, 1, 1);
  });
  ASSERT_ANY_THROW({
    a(3, 1, 1);
  });
}
TEST_F(test_d3_array, equalsss)
{
  d3_array a(1, 2, 1, 2, 1, 2);
  a.initialize();

  double value = -4.5;

  a = value;

  ASSERT_DOUBLE_EQ(value, a(1, 1, 1));
  ASSERT_DOUBLE_EQ(value, a(1, 1, 2));
  ASSERT_DOUBLE_EQ(value, a(1, 2, 1));
  ASSERT_DOUBLE_EQ(value, a(1, 2, 2));
  ASSERT_DOUBLE_EQ(value, a(2, 1, 1));
  ASSERT_DOUBLE_EQ(value, a(2, 1, 2));
  ASSERT_DOUBLE_EQ(value, a(2, 2, 1));
  ASSERT_DOUBLE_EQ(value, a(2, 2, 2));
}
TEST_F(test_d3_array, assignement)
{
  d3_array a(1, 2, 1, 2, 1, 2);
  a(1, 1, 1) = 1;
  a(1, 1, 2) = 2;
  a(1, 2, 1) = 3;
  a(1, 2, 2) = 4;
  a(2, 1, 1) = 5;
  a(2, 1, 2) = 6;
  a(2, 2, 1) = 7;
  a(2, 2, 2) = 8;

  d3_array b(1, 2, 1, 2, 1, 2);
  b.initialize();

  b = a;

  ASSERT_DOUBLE_EQ(a(1, 1, 1), b(1, 1, 1));
  ASSERT_DOUBLE_EQ(a(1, 1, 2), b(1, 1, 2));
  ASSERT_DOUBLE_EQ(a(1, 2, 1), b(1, 2, 1));
  ASSERT_DOUBLE_EQ(a(1, 2, 2), b(1, 2, 2));
  ASSERT_DOUBLE_EQ(a(2, 1, 1), b(2, 1, 1));
  ASSERT_DOUBLE_EQ(a(2, 1, 2), b(2, 1, 2));
  ASSERT_DOUBLE_EQ(a(2, 2, 1), b(2, 2, 1));
  ASSERT_DOUBLE_EQ(a(2, 2, 2), b(2, 2, 2));

  b = b;

  ASSERT_DOUBLE_EQ(a(1, 1, 1), b(1, 1, 1));
  ASSERT_DOUBLE_EQ(a(1, 1, 2), b(1, 1, 2));
  ASSERT_DOUBLE_EQ(a(1, 2, 1), b(1, 2, 1));
  ASSERT_DOUBLE_EQ(a(1, 2, 2), b(1, 2, 2));
  ASSERT_DOUBLE_EQ(a(2, 1, 1), b(2, 1, 1));
  ASSERT_DOUBLE_EQ(a(2, 1, 2), b(2, 1, 2));
  ASSERT_DOUBLE_EQ(a(2, 2, 1), b(2, 2, 1));
  ASSERT_DOUBLE_EQ(a(2, 2, 2), b(2, 2, 2));
}
TEST_F(test_d3_array, assignementfails)
{
  ad_exit=&test_ad_exit;

  d3_array a(1, 2, 1, 2, 1, 2);

  ASSERT_ANY_THROW({
    d3_array b(0, 2, 1, 2, 1, 2);
    a = b;
  });

  ASSERT_ANY_THROW({
    d3_array c(1, 3, 1, 2, 1, 2);
    a = c;
  });
}
TEST_F(test_d3_array, allocate_other)
{
  d3_array a(1, 2, 3, 4, 7, 12);
  d3_array b;

  b.allocate(a);

  ASSERT_EQ(b.slicemin(), 1);
  ASSERT_EQ(b.slicemax(), 2);
  ASSERT_EQ(b(1).rowmin(), 3);
  ASSERT_EQ(b(1).rowmax(), 4);
  ASSERT_EQ(b(2).rowmin(), 3);
  ASSERT_EQ(b(2).rowmax(), 4);
  ASSERT_EQ(b(1).colmin(), 7);
  ASSERT_EQ(b(1).colmax(), 12);
  ASSERT_EQ(b(2).colmin(), 7);
  ASSERT_EQ(b(2).colmax(), 12);
}
TEST_F(test_d3_array, allocate_6int)
{
  d3_array b;

  b.allocate(1, 2, 3, 4, 7, 12);

  ASSERT_EQ(b.slicemin(), 1);
  ASSERT_EQ(b.slicemax(), 2);
  ASSERT_EQ(b(1).rowmin(), 3);
  ASSERT_EQ(b(1).rowmax(), 4);
  ASSERT_EQ(b(2).rowmin(), 3);
  ASSERT_EQ(b(2).rowmax(), 4);
  ASSERT_EQ(b(1).colmin(), 7);
  ASSERT_EQ(b(1).colmax(), 12);
  ASSERT_EQ(b(2).colmin(), 7);
  ASSERT_EQ(b(2).colmax(), 12);
}
TEST_F(test_d3_array, allocate_5int)
{
  d3_array b;

  ivector colsmin(1, 2);
  colsmin(1) = 8;
  colsmin(2) = 9;
  b.allocate(1, 2, 3, 4, colsmin, 12);

  ASSERT_EQ(b.slicemin(), 1);
  ASSERT_EQ(b.slicemax(), 2);
  ASSERT_EQ(b(1).rowmin(), 3);
  ASSERT_EQ(b(1).rowmax(), 4);
  ASSERT_EQ(b(2).rowmin(), 3);
  ASSERT_EQ(b(2).rowmax(), 4);
  ASSERT_EQ(b(1).colmin(), colsmin(1));
  ASSERT_EQ(b(1).colmax(), 12);
  ASSERT_EQ(b(2).colmin(), colsmin(2));
  ASSERT_EQ(b(2).colmax(), 12);
}
TEST_F(test_d3_array, allocate_5int_error)
{
  d3_array b;

  ASSERT_ANY_THROW({
    ivector colsmin(1, 3);
    b.allocate(1, 2, 3, 4, colsmin, 12);
  });
  ASSERT_ANY_THROW({
    ivector colsmin(0, 2);
    b.allocate(1, 2, 3, 4, colsmin, 12);
  });
}
TEST_F(test_d3_array, allocate_5intb)
{
  d3_array b;

  ivector colsmax(1, 2);
  colsmax(1) = 8;
  colsmax(2) = 9;
  b.allocate(1, 2, 3, 4, 7, colsmax);

  ASSERT_EQ(b.slicemin(), 1);
  ASSERT_EQ(b.slicemax(), 2);
  ASSERT_EQ(b(1).rowmin(), 3);
  ASSERT_EQ(b(1).rowmax(), 4);
  ASSERT_EQ(b(2).rowmin(), 3);
  ASSERT_EQ(b(2).rowmax(), 4);
  ASSERT_EQ(b(1).colmin(), 7);
  ASSERT_EQ(b(1).colmax(), colsmax(1));
  ASSERT_EQ(b(2).colmin(), 7);
  ASSERT_EQ(b(2).colmax(), colsmax(2));
}
TEST_F(test_d3_array, allocate_5intb_error)
{
  d3_array b;

  ASSERT_ANY_THROW({
    ivector colsmax(0, 2);
    b.allocate(1, 2, 3, 4, 1, colsmax);
  });
  ASSERT_ANY_THROW({
    ivector colsmax(1, 3);
    b.allocate(1, 2, 3, 4, 1, colsmax);
  });
}
TEST_F(test_d3_array, allocate_4int)
{
  d3_array b;

  b.allocate(1, 2, 3, 4);

  ASSERT_EQ(b.slicemin(), 1);
  ASSERT_EQ(b.slicemax(), 2);
  ASSERT_EQ(b(1).rowmin(), 3);
  ASSERT_EQ(b(1).rowmax(), 4);
  ASSERT_EQ(b(2).rowmin(), 3);
  ASSERT_EQ(b(2).rowmax(), 4);
  ASSERT_EQ(b(1).colmin(), 1);
  ASSERT_EQ(b(1).colmax(), 0);
  ASSERT_EQ(b(2).colmin(), 1);
  ASSERT_EQ(b(2).colmax(), 0);
}
TEST_F(test_d3_array, indexed)
{
  d3_array a(1, 2, 1, 2, 1, 2);
  a(1, 1, 1) = 1;
  a(1, 1, 2) = 2;
  a(1, 2, 1) = 3;
  a(1, 2, 2) = 4;
  a(2, 1, 1) = 5;
  a(2, 1, 2) = 6;
  a(2, 2, 1) = 7;
  a(2, 2, 2) = 8;

  const d3_array b(a);

  ASSERT_DOUBLE_EQ(a(1, 1, 1), b(1, 1, 1));
  ASSERT_DOUBLE_EQ(a(1, 1, 2), b(1, 1, 2));
  ASSERT_DOUBLE_EQ(a(1, 2, 1), b(1, 2, 1));
  ASSERT_DOUBLE_EQ(a(1, 2, 2), b(1, 2, 2));
  ASSERT_DOUBLE_EQ(a(2, 1, 1), b(2, 1, 1));
  ASSERT_DOUBLE_EQ(a(2, 1, 2), b(2, 1, 2));
  ASSERT_DOUBLE_EQ(a(2, 2, 1), b(2, 2, 1));
  ASSERT_DOUBLE_EQ(a(2, 2, 2), b(2, 2, 2));

  const dvector c(b(1, 1));
  ASSERT_DOUBLE_EQ(a(1, 1, 1), c(1));
  ASSERT_DOUBLE_EQ(a(1, 1, 2), c(2));
}
TEST_F(test_d3_array, constructorintint)
{
  d3_array a(1, 2);
  ASSERT_FALSE(!a);
  ASSERT_TRUE(allocated(a));
  ASSERT_FALSE(allocated(a(1)));
  ASSERT_FALSE(allocated(a(2)));
  ASSERT_TRUE(!a(1));
  ASSERT_TRUE(!a(2));
  a(1).allocate(1, 2);
  ASSERT_FALSE(allocated(a(1, 1)));
  ASSERT_FALSE(allocated(a(1, 2)));
  ASSERT_TRUE(!a(1, 1));
  ASSERT_TRUE(!a(1, 2));
}
TEST_F(test_d3_array, allocateintint4xivector)
{
  d3_array a;
  ivector rowsmin(1, 3);
  rowsmin(1) = 2;
  rowsmin(2) = 3;
  rowsmin(3) = 4;
  ivector rowsmax(1, 3);
  rowsmax(1) = 5;
  rowsmax(2) = 6;
  rowsmax(3) = 7;
  ivector colsmin(1, 3);
  colsmin(1) = 2;
  colsmin(2) = 3;
  colsmin(3) = 4;
  ivector colsmax(1, 3);
  colsmax(1) = 5;
  colsmax(2) = 6;
  colsmax(3) = 7;
  a.allocate(1, 3, rowsmin, rowsmax, colsmin, colsmax);

  ASSERT_EQ(1, a.slicemin());
  ASSERT_EQ(3, a.slicemax());
  ASSERT_EQ(2, a(1).rowmin());
  ASSERT_EQ(5, a(1).rowmax());
  ASSERT_EQ(3, a(2).rowmin());
  ASSERT_EQ(6, a(2).rowmax());
  ASSERT_EQ(4, a(3).rowmin());
  ASSERT_EQ(7, a(3).rowmax());
  ASSERT_EQ(2, a(1).colmin());
  ASSERT_EQ(5, a(1).colmax());
  ASSERT_EQ(3, a(2).colmin());
  ASSERT_EQ(6, a(2).colmax());
  ASSERT_EQ(4, a(3).colmin());
  ASSERT_EQ(7, a(3).colmax());
}
TEST_F(test_d3_array, position)
{
  d3_array_position position(2, 5);
  d3_array a(position);
  ASSERT_EQ(2, a.slicemin());
  ASSERT_EQ(5, a.slicemax());
  ASSERT_EQ(4, a.slicesize());
  ASSERT_FALSE(allocated(a(2)));
  ASSERT_FALSE(allocated(a(3)));
  ASSERT_FALSE(allocated(a(4)));
  ASSERT_FALSE(allocated(a(5)));
}
TEST_F(test_d3_array, emptysum)
{
  d3_array a;
  ASSERT_DOUBLE_EQ(0.0, sum(a));
}
TEST_F(test_d3_array, allocate4int2vectors)
{
  d3_array a;

  ivector lowers(1, 3);
  lowers(1) = 5;
  lowers(2) = 6;
  lowers(3) = 7;
  ivector uppers(1, 3);
  uppers(1) = 8;
  uppers(2) = 9;
  uppers(3) = 10;
  a.allocate(1, 3, 1, 2, lowers, uppers);
  ASSERT_EQ(5, a(1, 1).indexmin());
  ASSERT_EQ(8, a(1, 1).indexmax());
  ASSERT_EQ(5, a(1, 2).indexmin());
  ASSERT_EQ(8, a(1, 2).indexmax());
  ASSERT_EQ(6, a(2, 1).indexmin());
  ASSERT_EQ(9, a(2, 1).indexmax());
  ASSERT_EQ(6, a(2, 2).indexmin());
  ASSERT_EQ(9, a(2, 2).indexmax());
  ASSERT_EQ(7, a(3, 1).indexmin());
  ASSERT_EQ(10, a(3, 1).indexmax());
  ASSERT_EQ(7, a(3, 2).indexmin());
  ASSERT_EQ(10, a(3, 2).indexmax());
}
TEST_F(test_d3_array, invalidindexesallocate4int2vectors)
{
  d3_array a;

  ivector lowers(1, 3);
  lowers(1) = 5;
  lowers(2) = 6;
  lowers(3) = 7;
  ivector uppers(1, 3);
  uppers(1) = 8;
  uppers(2) = 9;
  uppers(3) = 10;
  ASSERT_ANY_THROW({
    a.allocate(3, 1, 1, 2, lowers, uppers);
  });
}
TEST_F(test_d3_array, errorindexesallocate4int2vectors)
{
  ad_exit=&test_ad_exit;

  d3_array a;

  ASSERT_ANY_THROW({
    ivector lowers(0, 3);
    ivector uppers(1, 3);
    a.allocate(1, 3, 1, 2, lowers, uppers);
  });
  ASSERT_ANY_THROW({
    ivector lowers(1, 4);
    ivector uppers(1, 3);
    a.allocate(1, 3, 1, 2, lowers, uppers);
  });
  ASSERT_ANY_THROW({
    ivector lowers(1, 3);
    ivector uppers(0, 3);
    a.allocate(1, 3, 1, 2, lowers, uppers);
  });
  ASSERT_ANY_THROW({
    ivector lowers(1, 3);
    ivector uppers(1, 4);
    a.allocate(1, 3, 1, 2, lowers, uppers);
  });
}
TEST_F(test_d3_array, invalid_allocate_2int)
{
  d3_array b;

  b.allocate(2, 1);

  ASSERT_EQ(b.slicemin(), 1);
  ASSERT_EQ(b.slicemax(), 0);
  ASSERT_EQ(b.slicesize(), 0);
}
TEST_F(test_d3_array, allocate_rowsmax)
{
  d3_array b;

  ivector rowsmax(1, 3);
  rowsmax(1) = 2;
  rowsmax(2) = 3;
  rowsmax(3) = 4;
  b.allocate(1, 3, 2, rowsmax, 5, 6);

  ASSERT_EQ(b.slicemin(), 1);
  ASSERT_EQ(b.slicemax(), 3);
  ASSERT_EQ(b.slicesize(), 3);

  ASSERT_EQ(b(1).indexmin(), 2);
  ASSERT_EQ(b(1).indexmax(), 2);
  ASSERT_EQ(b(1, 2).indexmin(), 5);
  ASSERT_EQ(b(1, 2).indexmax(), 6);

  ASSERT_EQ(b(2).indexmin(), 2);
  ASSERT_EQ(b(2).indexmax(), 3);
  ASSERT_EQ(b(2, 2).indexmin(), 5);
  ASSERT_EQ(b(2, 2).indexmax(), 6);
  ASSERT_EQ(b(2, 3).indexmin(), 5);
  ASSERT_EQ(b(2, 3).indexmax(), 6);

  ASSERT_EQ(b(3).indexmin(), 2);
  ASSERT_EQ(b(3).indexmax(), 4);
  ASSERT_EQ(b(3, 2).indexmin(), 5);
  ASSERT_EQ(b(3, 2).indexmax(), 6);
  ASSERT_EQ(b(3, 3).indexmin(), 5);
  ASSERT_EQ(b(3, 3).indexmax(), 6);
  ASSERT_EQ(b(3, 4).indexmin(), 5);
  ASSERT_EQ(b(3, 4).indexmax(), 6);
}
TEST_F(test_d3_array, allocate_rowsmin)
{
  d3_array b;

  ivector rowsmin(1, 3);
  rowsmin(1) = 2;
  rowsmin(2) = 3;
  rowsmin(3) = 4;
  b.allocate(1, 3, rowsmin, 4, 5, 6);

  ASSERT_EQ(b.slicemin(), 1);
  ASSERT_EQ(b.slicemax(), 3);
  ASSERT_EQ(b.slicesize(), 3);

  ASSERT_EQ(b(1).indexmin(), 2);
  ASSERT_EQ(b(1).indexmax(), 4);
  ASSERT_EQ(b(1, 2).indexmin(), 5);
  ASSERT_EQ(b(1, 2).indexmax(), 6);
  ASSERT_EQ(b(1, 3).indexmin(), 5);
  ASSERT_EQ(b(1, 3).indexmax(), 6);
  ASSERT_EQ(b(1, 4).indexmin(), 5);
  ASSERT_EQ(b(1, 4).indexmax(), 6);

  ASSERT_EQ(b(2).indexmin(), 3);
  ASSERT_EQ(b(2).indexmax(), 4);
  ASSERT_EQ(b(2, 3).indexmin(), 5);
  ASSERT_EQ(b(2, 3).indexmax(), 6);
  ASSERT_EQ(b(2, 4).indexmin(), 5);
  ASSERT_EQ(b(2, 4).indexmax(), 6);

  ASSERT_EQ(b(3).indexmin(), 4);
  ASSERT_EQ(b(3).indexmax(), 4);
  ASSERT_EQ(b(3, 4).indexmin(), 5);
  ASSERT_EQ(b(3, 4).indexmax(), 6);
}
TEST_F(test_d3_array, allocate_rowsmax_colsmax)
{
  d3_array b;

  ivector rowsmax(1, 3);
  rowsmax(1) = 2;
  rowsmax(2) = 3;
  rowsmax(3) = 4;
  ivector colsmax(1, 3);
  colsmax(1) = 5;
  colsmax(2) = 6;
  colsmax(3) = 7;
  b.allocate(1, 3, 2, rowsmax, 5, colsmax);

  ASSERT_EQ(b.slicemin(), 1);
  ASSERT_EQ(b.slicemax(), 3);
  ASSERT_EQ(b.slicesize(), 3);

  ASSERT_EQ(b(1).indexmin(), 2);
  ASSERT_EQ(b(1).indexmax(), 2);
  ASSERT_EQ(b(1, 2).indexmin(), 5);
  ASSERT_EQ(b(1, 2).indexmax(), 5);

  ASSERT_EQ(b(2).indexmin(), 2);
  ASSERT_EQ(b(2).indexmax(), 3);
  ASSERT_EQ(b(2, 2).indexmin(), 5);
  ASSERT_EQ(b(2, 2).indexmax(), 6);
  ASSERT_EQ(b(2, 3).indexmin(), 5);
  ASSERT_EQ(b(2, 3).indexmax(), 6);

  ASSERT_EQ(b(3).indexmin(), 2);
  ASSERT_EQ(b(3).indexmax(), 4);
  ASSERT_EQ(b(3, 2).indexmin(), 5);
  ASSERT_EQ(b(3, 2).indexmax(), 7);
  ASSERT_EQ(b(3, 3).indexmin(), 5);
  ASSERT_EQ(b(3, 3).indexmax(), 7);
  ASSERT_EQ(b(3, 4).indexmin(), 5);
  ASSERT_EQ(b(3, 4).indexmax(), 7);
}
TEST_F(test_d3_array, error_rowsmax_colsmax)
{
  ad_exit=&test_ad_exit;

  ASSERT_ANY_THROW({
    d3_array b;
    ivector rowsmax(0, 3);
    ivector colsmax(1, 3);
    b.allocate(1, 3, 2, rowsmax, 5, colsmax);
  });
  ASSERT_ANY_THROW({
    d3_array b;
    ivector rowsmax(1, 4);
    ivector colsmax(1, 3);
    b.allocate(1, 3, 2, rowsmax, 5, colsmax);
  });
  ASSERT_ANY_THROW({
    d3_array b;
    ivector rowsmax(1, 3);
    ivector colsmax(0, 3);
    b.allocate(1, 3, 2, rowsmax, 5, colsmax);
  });
  ASSERT_ANY_THROW({
    d3_array b;
    ivector rowsmax(1, 3);
    ivector colsmax(1, 4);
    b.allocate(1, 3, 2, rowsmax, 5, colsmax);
  });
}
