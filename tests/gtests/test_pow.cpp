#include <gtest/gtest.h>
#include <fvar.hpp>
#include <climits>

class test_pow: public ::testing::Test {};

TEST_F(test_pow, base_ivector)
{
  const int exponent = 3;
  ivector base(1, 3);
  base(1) = 1;
  base(2) = 2;
  base(3) = 3;
  ivector ret = pow(base, exponent);
  ASSERT_EQ(1, ret(1));
  ASSERT_EQ(8, ret(2));
  ASSERT_EQ(27, ret(3));
}
TEST_F(test_pow, exponent_ivector)
{
  const int base = 2;
  ivector exponent(1, 3);
  exponent(1) = 0;
  exponent(2) = 1;
  exponent(3) = 2;
  ivector ret = pow(base, exponent);
  ASSERT_EQ(1, ret(1));
  ASSERT_EQ(2, ret(2));
  ASSERT_EQ(4, ret(3));
}
#ifndef _WIN32
TEST_F(test_pow, base_is_int_max)
{
  const int base = INT_MAX;
  ivector exponent(1, 3);
  exponent(1) = 0;
  exponent(2) = 1;
  exponent(3) = 2;
  EXPECT_DEATH(pow(base, exponent), "Assertion");
}
TEST_F(test_pow, exponent_is_int_max)
{
  const int base = 2;
  ivector exponent(1, 3);
  exponent(1) = INT_MAX;
  exponent(2) = INT_MAX;
  exponent(3) = INT_MAX;
  EXPECT_DEATH(pow(base, exponent), "Assertion");
}
#endif
