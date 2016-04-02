#include <gtest/gtest.h>
#include "fvar.hpp"

class test_d3_array: public ::testing::Test {};

TEST_F(test_d3_array, pow)
{
  d3_array a(1, 2, 1, 2, 1, 2);
  a(1) = 1;
  a(2) = 2;

  d3_array ret = pow(a, 3);
  ASSERT_EQ(1, ret(1, 1, 1));
  ASSERT_EQ(1, ret(1, 1, 2));
  ASSERT_EQ(1, ret(1, 2, 1));
  ASSERT_EQ(1, ret(1, 2, 2));
  ASSERT_EQ(8, ret(2, 1, 1));
  ASSERT_EQ(8, ret(2, 1, 2));
  ASSERT_EQ(8, ret(2, 2, 1));
  ASSERT_EQ(8, ret(2, 2, 2));
}
TEST_F(test_d3_array, cube)
{
  d3_array a(1, 2, 1, 2, 1, 2);
  a(1) = 1;
  a(2) = 2;

  d3_array ret = cube(a);
  ASSERT_EQ(1, ret(1, 1, 1));
  ASSERT_EQ(1, ret(1, 1, 2));
  ASSERT_EQ(1, ret(1, 2, 1));
  ASSERT_EQ(1, ret(1, 2, 2));
  ASSERT_EQ(8, ret(2, 1, 1));
  ASSERT_EQ(8, ret(2, 1, 2));
  ASSERT_EQ(8, ret(2, 2, 1));
  ASSERT_EQ(8, ret(2, 2, 2));
}
