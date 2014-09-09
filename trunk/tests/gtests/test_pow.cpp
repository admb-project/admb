#include <gtest/gtest.h>
#include <fvar.hpp>

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
