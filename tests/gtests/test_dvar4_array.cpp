#include <gtest/gtest.h>
#include <fvar.hpp>

extern "C"
{
  void test_ad_exit(const int exit_code);
}

class test_dvar4_array: public ::testing::Test {};

TEST_F(test_dvar4_array, assignment)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;
  dvar4_array a(1, 2, 1, 2, 1, 2, 1, 2);
  a.initialize();

  d4_array b(1, 2, 1, 2, 1, 2, 1, 2);

  int count = 1;
  for (int i = 1; i <= 2; ++i)
  {
    for (int j = 1; j <= 2; ++j)
    {
      for (int k = 1; k <= 2; ++k)
      {
        for (int l = 1; l <= 2; ++l)
        {
          b(i, j, k, l) = count;
          ++count;
        }
      }
    }
  }

  a = b;

  count = 1;
  for (int i = 1; i <= 2; ++i)
  {
    for (int j = 1; j <= 2; ++j)
    {
      for (int k = 1; k <= 2; ++k)
      {
        for (int l = 1; l <= 2; ++l)
        {
          ASSERT_DOUBLE_EQ(b(i, j, k, l), static_cast<double>(count));
          ++count;
        }
      }
    }
  }
}
