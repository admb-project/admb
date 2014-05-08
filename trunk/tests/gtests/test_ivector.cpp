#include <gtest/gtest.h>
#include <fvar.hpp>

class test_ivector: public ::testing::Test {};

TEST_F(test_ivector, constructor)
{
  ivector v;
  EXPECT_EQ(0, v.size());
}
TEST_F(test_ivector, initialize)
{
  ivector v(1, 10);
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
