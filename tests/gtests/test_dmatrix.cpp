#include <gtest/gtest.h>
#include <fvar.hpp>
#include <climits>

extern "C"
{
  void test_ad_exit(const int exit_code);
}

class test_dmatrix: public ::testing::Test {};

TEST_F(test_dmatrix, fill)
{
  dmatrix m(1, 2, 1, 3);

  char array[] = "{0, 1, 2} {3, 4, 5}";

  m.fill(array);

  ASSERT_DOUBLE_EQ(0, m(1, 1));
  ASSERT_DOUBLE_EQ(1, m(1, 2));
  ASSERT_DOUBLE_EQ(2, m(1, 3));
  ASSERT_DOUBLE_EQ(3, m(2, 1));
  ASSERT_DOUBLE_EQ(4, m(2, 2));
  ASSERT_DOUBLE_EQ(5, m(2, 3));
}
TEST_F(test_dmatrix, fill_extrabraces)
{
  ad_exit=&test_ad_exit;

  dmatrix m(1, 2, 1, 3);

  char array[] = "{{0, 1, 2} {3, 4, 5}}";

  try
  {
    m.fill(array);
  }
  catch (const int exit_code)
  {
    const int expected_exit_code = 1;
    if (exit_code == expected_exit_code)
    {
      return;
    }
  }
  FAIL();
}
TEST_F(test_dmatrix, fill_unallocated)
{
  ad_exit=&test_ad_exit;

  dmatrix m;

  char array[] = "{0, 1, 2} {3, 4, 5}";

  try
  {
    m.fill(array);
  }
  catch (const int exit_code)
  {
    const int expected_exit_code = 22;
    if (exit_code == expected_exit_code)
    {
      return;
    }
  }
  FAIL();
}
