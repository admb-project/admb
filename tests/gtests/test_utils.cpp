#include <gtest/gtest.h>
#include <fvar.hpp>

class test_utils: public ::testing::Test {};

TEST_F(test_utils, ranfill)
{
  double auto_rand(long int& idum, int reset);

  long idum = 5;

  double value = auto_rand(idum, -1);
  ASSERT_DOUBLE_EQ(value, 0.5);

  double value2 = auto_rand(idum, 1);
  ASSERT_DOUBLE_EQ(value2, 0.6659108996391296);
}
