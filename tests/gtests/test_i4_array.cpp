#include <gtest/gtest.h>
#include <cmath>
#include "fvar.hpp"

class test_i4_array: public ::testing::Test {};

TEST_F(test_i4_array, default)
{
  i4_array a;
  ASSERT_EQ(0, a.hslicesize());
  ASSERT_EQ(1, a.indexmin());
  ASSERT_EQ(0, a.indexmax());
}
