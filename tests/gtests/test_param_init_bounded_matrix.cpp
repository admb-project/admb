#include <gtest/gtest.h>
#include <admodel.h>

class test_param_init_bounded_matrix: public ::testing::Test {};

TEST_F(test_param_init_bounded_matrix, constructor)
{
  param_init_bounded_matrix p;
  ASSERT_EQ(1, p.indexmin());
  ASSERT_EQ(0, p.indexmax());
}
TEST_F(test_param_init_bounded_matrix, allocate_phase_start)
{
  gradient_structure gs;
  param_init_bounded_matrix p;

  ad_integer imin = 1;
  ad_integer imax = 2;
  ad_integer imin2 = 3;
  ad_integer imax2 = 4;
  ad_double bmin = 5;
  ad_double bmax = 10;
  ad_integer expected_phase_start = 5;

  p.allocate(imin, imax, imin2, imax2, bmin, bmax, expected_phase_start, "p");

  ASSERT_EQ(p.get_phase_start(), expected_phase_start);
}
