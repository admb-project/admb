#include <gtest/gtest.h>
#include <cmath>
#include "fvar.hpp"

class test_i5_array: public ::testing::Test {};

TEST_F(test_i5_array, default)
{
  i5_array a;
  ASSERT_EQ(0, a.hslicesize());
  ASSERT_EQ(1, a.indexmin());
  ASSERT_EQ(0, a.indexmax());
}
TEST_F(test_i5_array, 1xint)
{
  i5_array a(2, 5);
  ASSERT_EQ(4, a.hslicesize());
  ASSERT_EQ(2, a.indexmin());
  ASSERT_EQ(5, a.indexmax());
  ASSERT_EQ(1, a(2).indexmin());
  ASSERT_EQ(0, a(2).indexmax());
}
TEST_F(test_i5_array, 1xintinvalid)
{
  i5_array a(5, 2);
  ASSERT_EQ(0, a.hslicesize());
  ASSERT_EQ(1, a.indexmin());
  ASSERT_EQ(0, a.indexmax());
}
/*
TEST_F(test_i5_array, 5xint)
{
  i5_array a(1, 5, 1, 4, 1, 3, 1, 2, 1, 1);
}
*/
