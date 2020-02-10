#include <gtest/gtest.h>
#include <fvar.hpp>

class test_dvar5_array: public ::testing::Test {};

TEST_F(test_dvar5_array, allocate_empty_vector)
{
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
  gradient_structure gs;
  dvar5_array arr(2, 4);
  ASSERT_EQ(3, arr.size());
  ASSERT_EQ(2, arr.indexmin());
  ASSERT_EQ(4, arr.indexmax());
  ASSERT_FALSE(allocated(arr[2]));
  ASSERT_FALSE(allocated(arr[3]));
  ASSERT_FALSE(allocated(arr[4]));
}
TEST_F(test_dvar5_array, empty)
{
  gradient_structure gs;
  dvar5_array a;
  ASSERT_EQ(0, a.size());
  ASSERT_EQ(1, a.indexmin());
  ASSERT_EQ(0, a.indexmax());
}
TEST_F(test_dvar5_array, deallocatecopies)
{
  gradient_structure gs;

  dvar5_array a(1, 2, 1, 2, 1, 2, 1, 2, 1, 2);
  ASSERT_EQ(0, a.get_ncopies());
  dvar5_array firstcopy(a);
  ASSERT_EQ(1, a.get_ncopies());
  ASSERT_EQ(1, firstcopy.get_ncopies());
  dvar5_array secondcopy(a);
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
