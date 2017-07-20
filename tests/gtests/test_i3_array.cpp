#include <gtest/gtest.h>
#include <cmath>
#include "fvar.hpp"

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
