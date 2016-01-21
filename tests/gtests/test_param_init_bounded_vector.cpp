#include <gtest/gtest.h>
#include "admodel.h"

class test_param_init_bounded_vector: public ::testing::Test {};

TEST_F(test_param_init_bounded_vector, constructor)
{
  gradient_structure gs;
  dll_param_init_bounded_vector n;
  ASSERT_DOUBLE_EQ(0.0, n.get_minb());
  ASSERT_DOUBLE_EQ(0.0, n.get_maxb());
}
