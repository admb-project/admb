#include <gtest/gtest.h>
#include <fvar.hpp>

void test_ad_exit(const int exit_code);

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
TEST_F(test_dvar7_array, empty)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;
  dvar7_array a;
  ASSERT_EQ(0, a.size());
  ASSERT_EQ(1, a.indexmin());
  ASSERT_EQ(0, a.indexmax());
}
TEST_F(test_dvar7_array, deallocatecopies)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;

  dvar7_array a(1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2);
  ASSERT_EQ(0, a.get_ncopies());
  dvar7_array firstcopy(a);
  ASSERT_EQ(1, a.get_ncopies());
  ASSERT_EQ(1, firstcopy.get_ncopies());
  dvar7_array secondcopy(a);
  ASSERT_EQ(2, a.get_ncopies());
  ASSERT_EQ(2, firstcopy.get_ncopies());
  ASSERT_EQ(2, secondcopy.get_ncopies());

  firstcopy.deallocate();
  ASSERT_EQ(1, a.get_ncopies());
  ASSERT_EQ(0, firstcopy.get_ncopies());
  ASSERT_EQ(1, secondcopy.get_ncopies());

  secondcopy.deallocate();
  ASSERT_EQ(0, a.get_ncopies());
  ASSERT_EQ(0, firstcopy.get_ncopies());
  ASSERT_EQ(0, secondcopy.get_ncopies());
}
