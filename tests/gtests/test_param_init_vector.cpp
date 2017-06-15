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
TEST_F(test_param_init_vector, allocate_phase_start)
{
  gradient_structure gs;

  dll_param_init_vector p;
  int min = 2;
  int max = 3;
  int expected_phase_start = 4;
  double array[2];
  p.allocate(&array[0], min, max, expected_phase_start, "p");
  ASSERT_EQ(min, p.indexmin());
  ASSERT_EQ(max, p.indexmax());
  ASSERT_EQ(expected_phase_start, p.get_phase_start());

  dvector vec(2, 3);
  vec(2) = 2.5;
  vec(3) = 3.5;

  p = vec;
  ASSERT_DOUBLE_EQ(2.5, value(p(2)));
  ASSERT_DOUBLE_EQ(3.5, value(p(3)));

  dvar_vector varvec(2, 3);
  varvec(2) = 12.5;
  varvec(3) = 13.5;

  p = varvec;

  ASSERT_DOUBLE_EQ(12.5, value(p(2)));
  ASSERT_DOUBLE_EQ(13.5, value(p(3)));

  dvariable var = 6.5;
  p = var;

  ASSERT_DOUBLE_EQ(6.5, value(p(2)));
  ASSERT_DOUBLE_EQ(6.5, value(p(3)));

  double val = 16.5;
  p = val;
  ASSERT_DOUBLE_EQ(16.5, value(p(2)));
  ASSERT_DOUBLE_EQ(16.5, value(p(3)));
}
