#include <gtest/gtest.h>
#include <admodel.h>

class test_param_init_bounded_matrix_vector: public ::testing::Test {};

TEST_F(test_param_init_bounded_matrix_vector, constructor)
{
  param_init_bounded_matrix_vector p;
  ASSERT_FALSE(p.allocated());
  ASSERT_EQ(0, p.indexmin());
  ASSERT_EQ(-1, p.indexmax());
}
TEST_F(test_param_init_bounded_matrix_vector, set_initial_value)
{
  gradient_structure gs;

  param_init_bounded_matrix_vector p;
  p.set_initial_value(0.5);

  ASSERT_FALSE(p.allocated());
  ASSERT_EQ(0, p.indexmin());
  ASSERT_EQ(-1, p.indexmax());
}
TEST_F(test_param_init_bounded_matrix_vector, allocated)
{
  gradient_structure gs;

  param_init_bounded_matrix_vector p;
  p.set_initial_value(0.5);

  p.allocate(1, 4, 2, 3, 1, 4, 0.5, 2.5, "allocate");

  ASSERT_TRUE(p.allocated());
  ASSERT_EQ(1, p.indexmin());
  ASSERT_EQ(4, p.indexmax());
  ASSERT_EQ(2, p[1].indexmin());
  ASSERT_EQ(3, p[1].indexmax());
  ASSERT_EQ(2, p[2].indexmin());
  ASSERT_EQ(3, p[2].indexmax());
  ASSERT_EQ(2, p[3].indexmin());
  ASSERT_EQ(3, p[3].indexmax());
  ASSERT_EQ(2, p[4].indexmin());
  ASSERT_EQ(3, p[4].indexmax());
}
TEST_F(test_param_init_bounded_matrix_vector, noinitialvalue)
{
  gradient_structure gs;

  param_init_bounded_matrix_vector p;

  p.allocate(1, 4, 2, 3, 1, 4, 0.5, 2.5, "allocate");

  ASSERT_TRUE(p.allocated());
  ASSERT_EQ(1, p.indexmin());
  ASSERT_EQ(4, p.indexmax());
  ASSERT_EQ(2, p[1].indexmin());
  ASSERT_EQ(3, p[1].indexmax());
  ASSERT_EQ(2, p[2].indexmin());
  ASSERT_EQ(3, p[2].indexmax());
  ASSERT_EQ(2, p[3].indexmin());
  ASSERT_EQ(3, p[3].indexmax());
  ASSERT_EQ(2, p[4].indexmin());
  ASSERT_EQ(3, p[4].indexmax());
}
TEST_F(test_param_init_bounded_matrix_vector, allocate_error)
{
  param_init_bounded_matrix_vector p;
  ivector min(1, 4);
  min = 1;
  ivector max(1, 4);
  max = 4;
  p.allocate(1, -4, 1, 4, 1, 4, 0.5, 2.5, "allocate");
  ASSERT_FALSE(p.allocated());
  ASSERT_EQ(0, p.indexmin());
  ASSERT_EQ(-1, p.indexmax());
}
