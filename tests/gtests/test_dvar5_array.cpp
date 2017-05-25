#include <gtest/gtest.h>
#include <fvar.hpp>

extern "C"
{
  void test_ad_exit(const int exit_code);
}

class test_dvar5_array: public ::testing::Test {};

TEST_F(test_dvar5_array, allocate_empty_vector)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;
  dvar5_array arr;
  arr.allocate(2, 4);
  ASSERT_EQ(3, arr.size());
  ASSERT_EQ(2, arr.indexmin());
  ASSERT_EQ(4, arr.indexmax());
  ASSERT_FALSE(allocated(arr[2]));
  ASSERT_FALSE(allocated(arr[3]));
  ASSERT_FALSE(allocated(arr[4]));
}
TEST_F(test_dvar5_array, construct_empty_vector)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;
  dvar5_array arr(2, 4);
  ASSERT_EQ(3, arr.size());
  ASSERT_EQ(2, arr.indexmin());
  ASSERT_EQ(4, arr.indexmax());
  ASSERT_FALSE(allocated(arr[2]));
  ASSERT_FALSE(allocated(arr[3]));
  ASSERT_FALSE(allocated(arr[4]));
}
