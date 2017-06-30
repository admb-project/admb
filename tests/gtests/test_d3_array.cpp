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
