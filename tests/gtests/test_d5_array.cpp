#include <gtest/gtest.h>
#include <cmath>
#include "fvar.hpp"

class test_d5_array: public ::testing::Test {};

TEST_F(test_d5_array, allocate_copy_full)
{
  d5_array a;
  a.allocate(3, 6,
             1, 2,
             1, 2,
             1, 2,
             1, 2
            );
  ASSERT_EQ(a.size(), 4);
  ASSERT_EQ(a.indexmin(), 3);
  ASSERT_EQ(a.indexmax(), 6);

  d5_array b;
  b.allocate(a);

  ASSERT_EQ(b.size(), 4);
  ASSERT_EQ(b.indexmin(), 3);
  ASSERT_EQ(b.indexmax(), 6);
}
TEST_F(test_d5_array, allocate_vector)
{
  d5_array a;
  a.allocate(3, 6);

  ASSERT_EQ(a.size(), 4);
  ASSERT_EQ(a.indexmin(), 3);
  ASSERT_EQ(a.indexmax(), 6);
}
