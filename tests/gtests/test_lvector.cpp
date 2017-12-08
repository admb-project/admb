#include <gtest/gtest.h>
#include <fvar.hpp>

class test_lvector: public ::testing::Test {};

TEST_F(test_lvector, constructor)
{
  lvector v;
  EXPECT_EQ(0, v.size());
}
TEST_F(test_lvector, initialize)
{
  lvector v(1, 10);
  EXPECT_EQ(10, v.size());
  for (int i = 1; i <= 10; i++)
  {
    v(i) = i;
  }
  for (int i = 1; i <= 10; i++)
  {
    EXPECT_EQ(i, v(i));
  }
  v.initialize();
  for (int i = 1; i <= 10; i++)
  {
    EXPECT_EQ(0, v(i));
  }
}
TEST_F(test_lvector, select)
{
  lvector v(1, 10);
  for (int i = 1; i <= 10; i++)
  {
    v(i) = i;
  }

  ivector indexes(1, 3);
  indexes(1) = 2;
  indexes(2) = 5;
  indexes(3) = 8;

  lvector selected = v(indexes);

  EXPECT_EQ(2, selected(1));
  EXPECT_EQ(5, selected(2));
  EXPECT_EQ(8, selected(3));
}
TEST_F(test_lvector, shift)
{
  lvector v(1, 4);
  v(1) = 0;
  v(2) = 1;
  v(3) = 2;
  v(4) = -4;

  EXPECT_EQ(1, v.indexmin());
  EXPECT_EQ(4, v.indexmax());

  v.shift(2);
  EXPECT_EQ(2, v.indexmin());
  EXPECT_EQ(5, v.indexmax());

  EXPECT_EQ(0, v(2));
  EXPECT_EQ(1, v(3));
  EXPECT_EQ(2, v(4));
  EXPECT_EQ(-4, v(5));
}
