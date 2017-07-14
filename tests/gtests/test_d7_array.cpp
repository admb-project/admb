#include <gtest/gtest.h>
#include <cmath>
#include "fvar.hpp"

class test_d7_array: public ::testing::Test {};

TEST_F(test_d7_array, allocate)
{
  d7_array a;
  a.allocate(3, 6);

  ASSERT_EQ(a.size(), 4);
  ASSERT_EQ(a.indexmin(), 3);
  ASSERT_EQ(a.indexmax(), 6);

  for (int i = 3; i <= 6; ++i)
  {
    ASSERT_TRUE(!a(i));
  }
}
TEST_F(test_d7_array, allocate_invalid)
{
  d7_array a;
  a.allocate(6, 3);

  ASSERT_EQ(a.size(), 0);
  ASSERT_EQ(a.indexmin(), 6);
  ASSERT_EQ(a.indexmax(), 3);
}
TEST_F(test_d7_array, allocate_copy)
{
  d7_array a;
  a.allocate(3, 6);

  //segmentation error
  d7_array b;
  b.allocate(a);

  ASSERT_EQ(b.size(), 4);
  ASSERT_EQ(b.indexmin(), 3);
  ASSERT_EQ(b.indexmax(), 6);
  ASSERT_FALSE(allocated(b(3)));
  ASSERT_FALSE(allocated(b(4)));
  ASSERT_FALSE(allocated(b(5)));
  ASSERT_FALSE(allocated(b(6)));
}
TEST_F(test_d7_array, allocate_copy_full)
{
  d7_array a;
  a.allocate(3, 6,
             1, 2,
             1, 2,
             1, 2,
             1, 2,
             1, 2,
             1, 2
            );

  d7_array b;
  b.allocate(a);

  ASSERT_EQ(b.size(), 4);
  ASSERT_EQ(b.indexmin(), 3);
  ASSERT_EQ(b.indexmax(), 6);
}
