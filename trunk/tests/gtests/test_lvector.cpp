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
