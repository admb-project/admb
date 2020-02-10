#include <gtest/gtest.h>
#include <fvar.hpp>

class test_dvar6_array: public ::testing::Test {};

TEST_F(test_dvar6_array, empty)
{
  gradient_structure gs;
  dvar6_array a;
  ASSERT_EQ(0, a.size());
  ASSERT_EQ(1, a.indexmin());
  ASSERT_EQ(0, a.indexmax());
}
TEST_F(test_dvar6_array, deallocatecopies)
{
  gradient_structure gs;

  dvar6_array a(1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2);
  ASSERT_EQ(0, a.get_ncopies());
  dvar6_array firstcopy(a);
  ASSERT_EQ(1, a.get_ncopies());
  ASSERT_EQ(1, firstcopy.get_ncopies());
  dvar6_array secondcopy(a);
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
