#include <gtest/gtest.h>
#include "admodel.h"

class test_param_init_bounded_dev_vector: public ::testing::Test {};

/**
Subtract mean from vector v so that the sum is near zero.
From AD Model Builder manual page 1-26.
*/
TEST_F(test_param_init_bounded_dev_vector, sum_zero)
{
  dvector v(1, 5);
  v(1) = -0.5;
  v(2) = 3;
  v(3) = -4;
  v(4) = 6.5;
  v(5) = -3.2;

  double total = sum(v);

  ASSERT_DOUBLE_EQ(total, 1.8);

  ASSERT_EQ(v.size(), 5);
  double mean = total / static_cast<double>(v.size());

  ASSERT_DOUBLE_EQ(mean, 0.36);

  v -= mean;

  ASSERT_NEAR(0.0, sum(v), 1.0e-12);
}
TEST_F(test_param_init_bounded_dev_vector, constructor)
{
  gradient_structure gs;
  param_init_bounded_dev_vector n;
}
