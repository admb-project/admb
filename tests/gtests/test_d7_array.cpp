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
  ASSERT_EQ(a.indexmin(), 1);
  ASSERT_EQ(a.indexmax(), 0);
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
TEST_F(test_d7_array, empty)
{
  d7_array a;

  ASSERT_EQ(a.size(), 0);
  ASSERT_EQ(a.indexmin(), 1);
  ASSERT_EQ(a.indexmax(), 0);
}
TEST_F(test_d7_array, allocate4xint)
{
  d7_array a;
  a.allocate(1, 1, 1, 2, 1, 3, 1, 4, 1, 5, 1, 6, 1, 7);

  ASSERT_EQ(1, a.indexmin());
  ASSERT_EQ(1, a.indexmax());
  ASSERT_EQ(1, a(1).indexmin());
  ASSERT_EQ(2, a(1).indexmax());
  ASSERT_EQ(1, a(1, 1).indexmin());
  ASSERT_EQ(3, a(1, 1).indexmax());
  ASSERT_EQ(1, a(1, 2).indexmin());
  ASSERT_EQ(3, a(1, 2).indexmax());
  ASSERT_EQ(1, a(1, 1, 1).indexmin());
  ASSERT_EQ(4, a(1, 1, 1).indexmax());
  ASSERT_EQ(1, a(1, 2, 1).indexmin());
  ASSERT_EQ(4, a(1, 2, 1).indexmax());
  ASSERT_EQ(1, a(1, 1, 2).indexmin());
  ASSERT_EQ(4, a(1, 1, 2).indexmax());
  ASSERT_EQ(1, a(1, 2, 2).indexmin());
  ASSERT_EQ(4, a(1, 2, 2).indexmax());
  ASSERT_EQ(1, a(1, 1, 3).indexmin());
  ASSERT_EQ(4, a(1, 1, 3).indexmax());
  ASSERT_EQ(1, a(1, 2, 3).indexmin());
  ASSERT_EQ(4, a(1, 2, 3).indexmax());
  ASSERT_EQ(1, a(1, 1, 1, 1).indexmin());
  ASSERT_EQ(5, a(1, 1, 1, 1).indexmax());
  ASSERT_EQ(1, a(1, 1, 1, 4).indexmin());
  ASSERT_EQ(5, a(1, 1, 1, 4).indexmax());
  ASSERT_EQ(1, a(1, 1, 1, 1, 1).indexmin());
  ASSERT_EQ(6, a(1, 1, 1, 1, 1).indexmax());
  ASSERT_EQ(1, a(1, 1, 1, 1, 5).indexmin());
  ASSERT_EQ(6, a(1, 1, 1, 1, 5).indexmax());
  ASSERT_EQ(1, a(1, 1, 1, 1, 1, 1).indexmin());
  ASSERT_EQ(7, a(1, 1, 1, 1, 1, 1).indexmax());
  ASSERT_EQ(1, a(1, 1, 1, 1, 1, 6).indexmin());
  ASSERT_EQ(7, a(1, 1, 1, 1, 1, 6).indexmax());
}
