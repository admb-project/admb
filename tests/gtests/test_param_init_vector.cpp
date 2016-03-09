#include <gtest/gtest.h>
#include <admodel.h>
#include <climits>

class test_param_init_vector: public ::testing::Test {};

TEST_F(test_param_init_vector, constructor)
{
  param_init_vector p;
  ASSERT_EQ(0, p.indexmin());
  ASSERT_EQ(-1, p.indexmax());
}
/*
TEST_F(test_param_init_vector, allocate_phase_start)
{
  param_init_vector p;
  int min = 2;
  int max = 3;
  int expected_phase_start = 4;
  p.allocate(min, max, expected_phase_start, "p");
  ASSERT_EQ(min, p.indexmin());
  ASSERT_EQ(max, p.indexmax());
  ASSERT_EQ(expected_phase_start, p.get_phase_start());
}
*/
