#include <gtest/gtest.h>
#include <fvar.hpp>

extern "C"
{
  void test_ad_exit(const int exit_code);
}

class test_dvar7_array: public ::testing::Test {};

TEST_F(test_dvar7_array, allocate_vector)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;
  dvar7_array a;
  a.allocate(2, 4);
  ASSERT_EQ(3, a.size());
  ASSERT_EQ(2, a.indexmin());
  ASSERT_EQ(4, a.indexmax());
}
TEST_F(test_dvar7_array, allocate_m1)
{
  ad_exit=&test_ad_exit;

  d7_array m1(2, 4, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2);

  gradient_structure gs;
  dvar7_array a;
  a.allocate(m1);
  ASSERT_EQ(3, a.size());
  ASSERT_EQ(2, a.indexmin());
  ASSERT_EQ(4, a.indexmax());
}
TEST_F(test_dvar7_array, allocate_all_dimensions)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;
  dvar7_array a;
  a.allocate(2, 4, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2);
  ASSERT_EQ(3, a.size());
  ASSERT_EQ(2, a.indexmin());
  ASSERT_EQ(4, a.indexmax());
}
