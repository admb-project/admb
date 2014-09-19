#include <gtest/gtest.h>
#include <admodel.h>
#include <climits>

class test_param_init_vector_vector: public ::testing::Test {};

TEST_F(test_param_init_vector_vector, constructor)
{
  param_init_vector_vector p;
  ASSERT_FALSE(p.allocated());
  ASSERT_EQ(0, p.indexmin());
  ASSERT_EQ(0, p.indexmax());
}
TEST_F(test_param_init_vector_vector, allocate)
{
  gradient_structure gs;
  param_init_vector_vector p;
  p.allocate(1, 4, -5, 5, "allocate");
  ASSERT_TRUE(p.allocated());
  ASSERT_EQ(1, p.indexmin());
  ASSERT_EQ(4, p.indexmax());
}
TEST_F(test_param_init_vector_vector, allocate_error)
{
  param_init_vector_vector p;
  p.allocate(1, -4, -5, 5, "allocate");
  ASSERT_FALSE(p.allocated());
  ASSERT_EQ(0, p.indexmin());
  ASSERT_EQ(0, p.indexmax());
}
/*
TEST_F(test_param_init_vector_vector, allocate_big_error)
{
  param_init_vector_vector p;
  p.allocate(1, INT_MAX, -5, 5, "allocate");
  ASSERT_FALSE(p.allocated());
  ASSERT_EQ(0, p.indexmin());
  ASSERT_EQ(0, p.indexmax());
}
*/
