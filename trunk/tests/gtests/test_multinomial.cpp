#include <gtest/gtest.h>
#include <fvar.hpp>
#include <climits>

class test_multinomial: public ::testing::Test {};

TEST_F(test_multinomial, fill_multinomial)
{
  const int seed = 2;

  dvector p(1, 3);
  p(1) = 1;
  p(2) = 2;
  p(3) = 3;

  dvector d(1, 3);
  d.fill_multinomial(seed, p);

  lvector l(1, 3);
  l.fill_multinomial(seed, p);

  ivector i(1, 3);
  i.fill_multinomial(seed, p);

  ASSERT_DOUBLE_EQ(d(1), l(1));
  ASSERT_DOUBLE_EQ(d(2), l(2));
  ASSERT_DOUBLE_EQ(d(3), l(3));
  ASSERT_DOUBLE_EQ(d(1), i(1));
  ASSERT_DOUBLE_EQ(d(2), i(2));
  ASSERT_DOUBLE_EQ(d(3), i(3));
}
