#include <gtest/gtest.h>
#include <admodel.h>

class test_param_init_matrix: public ::testing::Test {};

TEST_F(test_param_init_matrix, constructor)
{
  param_init_matrix p;
  ASSERT_EQ(1, p.indexmin());
  ASSERT_EQ(0, p.indexmax());
}
