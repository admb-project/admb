#include <gtest/gtest.h>
#include <cmath>
#include "fvar.hpp"

class test_d6_array: public ::testing::Test {};

TEST_F(test_d6_array, allocate_copy_full)
{
  d6_array a;
  a.allocate(3, 6,
             1, 2,
             1, 2,
             1, 2,
             1, 2,
             1, 2
            );
  ASSERT_EQ(a.size(), 4);
  ASSERT_EQ(a.indexmin(), 3);
  ASSERT_EQ(a.indexmax(), 6);

  d6_array b;
  b.allocate(a);

  ASSERT_EQ(b.size(), 4);
  ASSERT_EQ(b.indexmin(), 3);
  ASSERT_EQ(b.indexmax(), 6);
}
TEST_F(test_d6_array, inputoutput)
{
  d6_array a(1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2);

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
              a(i, j, k, l, m, n) = d;
              d += 2.0;
            }
          }
        }
      }
    }
  }

  ofstream ofs("d6_array.txt");
  ofs << a;
  ofs.close();

  d6_array b(1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2);

  ifstream ifs("d6_array.txt");
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
            for (int n = 1; n <= 2; ++n)
            {
              ASSERT_DOUBLE_EQ(a(i, j, k, l, m, n), b(i, j, k, l, m, n));
            }
          }
        }
      }
    }
  }
}
