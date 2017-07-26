#include <gtest/gtest.h>
#include <cmath>
#include "fvar.hpp"

class test_d7_array: public ::testing::Test {};

TEST_F(test_d7_array, allocate)
{
  d7_array a;
  a.allocate(3, 6);

  ASSERT_EQ(a.size(), 4);
  ASSERT_EQ(a.indexmin(), 3);
  ASSERT_EQ(a.indexmax(), 6);

  for (int i = 3; i <= 6; ++i)
  {
    ASSERT_TRUE(!a(i));
  }
}
TEST_F(test_d7_array, allocate_invalid)
{
  d7_array a;
  a.allocate(6, 3);

  ASSERT_EQ(a.size(), 0);
  ASSERT_EQ(a.indexmin(), 1);
  ASSERT_EQ(a.indexmax(), 0);
}
TEST_F(test_d7_array, allocate_copy)
{
  d7_array a;
  a.allocate(3, 6);
  ASSERT_EQ(a.size(), 4);
  ASSERT_EQ(a.indexmin(), 3);
  ASSERT_EQ(a.indexmax(), 6);
  ASSERT_EQ(a(3).indexmin(), 1);
  ASSERT_EQ(a(3).indexmax(), 0);
  ASSERT_EQ(a(4).indexmin(), 1);
  ASSERT_EQ(a(4).indexmax(), 0);
  ASSERT_EQ(a(5).indexmin(), 1);
  ASSERT_EQ(a(5).indexmax(), 0);
  ASSERT_EQ(a(6).indexmin(), 1);
  ASSERT_EQ(a(6).indexmax(), 0);
  ASSERT_FALSE(allocated(a(3)));
  ASSERT_FALSE(allocated(a(4)));
  ASSERT_FALSE(allocated(a(5)));
  ASSERT_FALSE(allocated(a(6)));

  //segmentation error
  d7_array b;
  b.allocate(a);

  ASSERT_EQ(b.size(), 4);
  ASSERT_EQ(b.indexmin(), 3);
  ASSERT_EQ(b.indexmax(), 6);
  ASSERT_EQ(b(3).indexmin(), 1);
  ASSERT_EQ(b(3).indexmax(), 0);
  ASSERT_EQ(b(4).indexmin(), 1);
  ASSERT_EQ(b(4).indexmax(), 0);
  ASSERT_EQ(b(5).indexmin(), 1);
  ASSERT_EQ(b(5).indexmax(), 0);
  ASSERT_EQ(b(6).indexmin(), 1);
  ASSERT_EQ(b(6).indexmax(), 0);
  ASSERT_TRUE(!b(3));
  ASSERT_FALSE(!(!b(3)));
  ASSERT_FALSE(allocated(b(3)));
  ASSERT_FALSE(allocated(b(4)));
  ASSERT_FALSE(allocated(b(5)));
  ASSERT_FALSE(allocated(b(6)));
}
TEST_F(test_d7_array, allocate_copy_full)
{
  d7_array a;
  a.allocate(3, 6,
             1, 2,
             1, 2,
             1, 2,
             1, 2,
             1, 2,
             1, 2
            );

  d7_array b;
  b.allocate(a);

  ASSERT_EQ(b.size(), 4);
  ASSERT_EQ(b.indexmin(), 3);
  ASSERT_EQ(b.indexmax(), 6);
}
TEST_F(test_d7_array, empty)
{
  d7_array a;

  ASSERT_EQ(a.size(), 0);
  ASSERT_EQ(a.indexmin(), 1);
  ASSERT_EQ(a.indexmax(), 0);
}
TEST_F(test_d7_array, allocate4xint)
{
  d7_array a;
  a.allocate(1, 1, 1, 2, 1, 3, 1, 4, 1, 5, 1, 6, 1, 7);

  ASSERT_EQ(1, a.indexmin());
  ASSERT_EQ(1, a.indexmax());
  ASSERT_EQ(1, a(1).indexmin());
  ASSERT_EQ(2, a(1).indexmax());
  ASSERT_EQ(1, a(1, 1).indexmin());
  ASSERT_EQ(3, a(1, 1).indexmax());
  ASSERT_EQ(1, a(1, 2).indexmin());
  ASSERT_EQ(3, a(1, 2).indexmax());
  ASSERT_EQ(1, a(1, 1, 1).indexmin());
  ASSERT_EQ(4, a(1, 1, 1).indexmax());
  ASSERT_EQ(1, a(1, 2, 1).indexmin());
  ASSERT_EQ(4, a(1, 2, 1).indexmax());
  ASSERT_EQ(1, a(1, 1, 2).indexmin());
  ASSERT_EQ(4, a(1, 1, 2).indexmax());
  ASSERT_EQ(1, a(1, 2, 2).indexmin());
  ASSERT_EQ(4, a(1, 2, 2).indexmax());
  ASSERT_EQ(1, a(1, 1, 3).indexmin());
  ASSERT_EQ(4, a(1, 1, 3).indexmax());
  ASSERT_EQ(1, a(1, 2, 3).indexmin());
  ASSERT_EQ(4, a(1, 2, 3).indexmax());
  ASSERT_EQ(1, a(1, 1, 1, 1).indexmin());
  ASSERT_EQ(5, a(1, 1, 1, 1).indexmax());
  ASSERT_EQ(1, a(1, 1, 1, 4).indexmin());
  ASSERT_EQ(5, a(1, 1, 1, 4).indexmax());
  ASSERT_EQ(1, a(1, 1, 1, 1, 1).indexmin());
  ASSERT_EQ(6, a(1, 1, 1, 1, 1).indexmax());
  ASSERT_EQ(1, a(1, 1, 1, 1, 5).indexmin());
  ASSERT_EQ(6, a(1, 1, 1, 1, 5).indexmax());
  ASSERT_EQ(1, a(1, 1, 1, 1, 1, 1).indexmin());
  ASSERT_EQ(7, a(1, 1, 1, 1, 1, 1).indexmax());
  ASSERT_EQ(1, a(1, 1, 1, 1, 1, 6).indexmin());
  ASSERT_EQ(7, a(1, 1, 1, 1, 1, 6).indexmax());
}
TEST_F(test_d7_array, sum)
{
  d7_array a(1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2);

  double total = 0;
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
            for (int n = 1; n <= 2; ++n)
            {
              for (int p = 1; p <= 2; ++p)
              {
                a(i, j, k, l, m, n, p) = d;
                total += d;
                d += 2.0;
              }
            }
          }
        }
      }
    }
  }
  ASSERT_DOUBLE_EQ(total, sum(a));
}
TEST_F(test_d7_array, divisor)
{
  d7_array a(1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2);

  double total = 0;
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
            for (int n = 1; n <= 2; ++n)
            {
              for (int p = 1; p <= 2; ++p)
              {
                a(i, j, k, l, m, n, p) = d;
                total += d;
                d += 2.0;
              }
            }
          }
        }
      }
    }
  }
  d7_array b;
  b.allocate(a);
  b = a; 
  b /= 2.0;
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
            for (int n = 1; n <= 2; ++n)
            {
              for (int p = 1; p <= 2; ++p)
              {
                ASSERT_DOUBLE_EQ(a(i, j, k, l, m, n, p) / 2.0, b(i, j, k, l, m, n, p));
              }
            }
          }
        }
      }
    }
  }
  d7_array c;
  c.allocate(a);
  c = a / 2.0;
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
            for (int n = 1; n <= 2; ++n)
            {
              for (int p = 1; p <= 2; ++p)
              {
                ASSERT_DOUBLE_EQ(c(i, j, k, l, m, n, p), b(i, j, k, l, m, n, p));
              }
            }
          }
        }
      }
    }
  }
}
TEST_F(test_d7_array, constsum)
{
  d7_array a(1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2);

  double total = 0;
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
            for (int n = 1; n <= 2; ++n)
            {
              for (int p = 1; p <= 2; ++p)
              {
                a(i, j, k, l, m, n, p) = d;
                total += d;
                d += 2.0;
              }
            }
          }
        }
      }
    }
  }

  const d7_array b(a);
  ASSERT_DOUBLE_EQ(total, sum(b));
}
TEST_F(test_d7_array, initialize)
{
  d7_array a(1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2);

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
            for (int n = 1; n <= 2; ++n)
            {
              for (int p = 1; p <= 2; ++p)
              {
                a(i, j, k, l, m, n, p) = d;
                d += 2.0;
              }
            }
          }
        }
      }
    }
  }
  a.initialize();
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
            for (int n = 1; n <= 2; ++n)
            {
              for (int p = 1; p <= 2; ++p)
              {
                ASSERT_DOUBLE_EQ(0.0, a(i, j, k, l, m, n, p));
              }
            }
          }
        }
      }
    }
  }
}
TEST_F(test_d7_array, equal)
{
  d7_array a(1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2);

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
            for (int n = 1; n <= 2; ++n)
            {
              for (int p = 1; p <= 2; ++p)
              {
                a(i, j, k, l, m, n, p) = d;
                d += 2.0;
              }
            }
          }
        }
      }
    }
  }
  d7_array b(1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2);
  b = a;
  a.initialize();
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
            for (int n = 1; n <= 2; ++n)
            {
              for (int p = 1; p <= 2; ++p)
              {
                ASSERT_DOUBLE_EQ(0.0, a(i, j, k, l, m, n, p));
              }
            }
          }
        }
      }
    }
  }
  a = b;
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
            for (int n = 1; n <= 2; ++n)
            {
              for (int p = 1; p <= 2; ++p)
              {
                ASSERT_DOUBLE_EQ(a(i, j, k, l, m, n, p), b(i, j, k, l, m, n, p));
              }
            }
          }
        }
      }
    }
  }
}
TEST_F(test_d7_array, elem)
{
  d7_array a;
  a.allocate(2, 5);
  ASSERT_ANY_THROW({
    a.elem(1);
  });
  ASSERT_ANY_THROW({
    a.elem(6);
  });
}
TEST_F(test_d7_array, assigment2error)
{
  d7_array a;
  a.allocate(1, 4);
  ASSERT_ANY_THROW({
    d7_array b;
    b.allocate(2, 4);
    a = b;
  });
  ASSERT_ANY_THROW({
    d7_array b;
    b.allocate(1, 5);
    a = b;
  });
}
TEST_F(test_d7_array, copyempty)
{
  d7_array empty;
  ASSERT_FALSE(allocated(empty));
  ASSERT_EQ(1, empty.indexmin());
  ASSERT_EQ(0, empty.indexmax());
  ASSERT_EQ(0, empty.size());
  d7_array a(empty);
  ASSERT_FALSE(allocated(a));
  ASSERT_EQ(1, a.indexmin());
  ASSERT_EQ(0, a.indexmax());
  ASSERT_EQ(0, a.size());
}
