#include <gtest/gtest.h>
#include <admodel.h>

class test_param_init_matrix_vector: public ::testing::Test {};

TEST_F(test_param_init_matrix_vector, constructor)
{
  param_init_matrix_vector p;
  ASSERT_FALSE(p.allocated());
  ASSERT_EQ(0, p.indexmin());
  ASSERT_EQ(0, p.indexmax());
}
TEST_F(test_param_init_matrix_vector, allocate)
{
  gradient_structure gs;
  param_init_matrix_vector p;
  ivector min(1, 4);
  min = 1;
  ivector max(1, 4);
  max = 4;
  p.allocate(1, 4, min, max, min, max, "allocate");
  ASSERT_TRUE(p.allocated());
  ASSERT_EQ(1, p.indexmin());
  ASSERT_EQ(4, p.indexmax());
}
TEST_F(test_param_init_matrix_vector, allocate_error)
{
  param_init_matrix_vector p;
  ivector min(1, 4);
  min = 1;
  ivector max(1, 4);
  max = 4;
  p.allocate(1, -4, min, max, min, max, "allocate");
  ASSERT_FALSE(p.allocated());
  ASSERT_EQ(0, p.indexmin());
  ASSERT_EQ(0, p.indexmax());
}
