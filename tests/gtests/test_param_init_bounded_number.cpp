#include <gtest/gtest.h>
#include "admodel.h"

class test_param_init_bounded_number: public ::testing::Test {};

TEST_F(test_param_init_bounded_number, constructor)
{
  gradient_structure gs;
  param_init_bounded_number n;
  ASSERT_DOUBLE_EQ(0.0, n.get_minb());
  ASSERT_DOUBLE_EQ(0.0, n.get_maxb());

  n.set_maxb(-2.5);
  ASSERT_DOUBLE_EQ(-2.5, n.get_maxb());
}
