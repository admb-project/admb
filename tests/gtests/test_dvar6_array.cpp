#include <gtest/gtest.h>
#include <fvar.hpp>

extern "C"
{
  void test_ad_exit(const int exit_code);
}

class test_dvar6_array: public ::testing::Test {};

TEST_F(test_dvar6_array, empty)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;
  dvar6_array a;
  ASSERT_EQ(0, a.size());
  ASSERT_EQ(1, a.indexmin());
  ASSERT_EQ(0, a.indexmax());
}
