#include <gtest/gtest.h>
#include <admodel.h>

class test_param_init_matrix: public ::testing::Test {};

TEST_F(test_param_init_matrix, constructor)
{
  param_init_matrix p;
  ASSERT_EQ(1, p.indexmin());
  ASSERT_EQ(0, p.indexmax());
}
TEST_F(test_param_init_matrix, assignment_operator_empty_dmatrix)
{
  param_init_matrix p;
  dmatrix m;
  try
  {
    p = m;
  }
  catch (const int exit_code)
  {
    return;
  }
  FAIL();
}
TEST_F(test_param_init_matrix, allocate_nogradient)
{
  param_init_matrix p;
  try
  {
    p.allocate(1, 2, 1, 3, "p");
  }
  catch (const int exit_code)
  {
    return;
  }
  FAIL();
}
TEST_F(test_param_init_matrix, assignment_operator_allocated_matrix)
{
  param_init_matrix p;
  dmatrix m(1, 2, 1, 3);
  try
  {
    p = m;
  }
  catch (const int exit_code)
  {
    return;
  }
  FAIL();
}
TEST_F(test_param_init_matrix, assignment_operator_dmatrix)
{
  gradient_structure gs;
  param_init_matrix p;
  p.allocate(1, 2, 1, 3, "p");
  p.initialize();
  ASSERT_DOUBLE_EQ(value(p(1, 1)), 0);
  ASSERT_DOUBLE_EQ(value(p(1, 2)), 0);
  ASSERT_DOUBLE_EQ(value(p(1, 3)), 0);
  ASSERT_DOUBLE_EQ(value(p(2, 1)), 0);
  ASSERT_DOUBLE_EQ(value(p(2, 2)), 0);
  ASSERT_DOUBLE_EQ(value(p(2, 3)), 0);

  dmatrix m(1, 2, 1, 3);
  m(1, 1) = 1;
  m(1, 2) = 2;
  m(1, 3) = 3;
  m(2, 1) = 4;
  m(2, 2) = 5;
  m(2, 3) = 6;
  p = m;
  ASSERT_DOUBLE_EQ(value(p(1, 1)), m(1, 1));
  ASSERT_DOUBLE_EQ(value(p(1, 2)), m(1, 2));
  ASSERT_DOUBLE_EQ(value(p(1, 3)), m(1, 3));
  ASSERT_DOUBLE_EQ(value(p(2, 1)), m(2, 1));
  ASSERT_DOUBLE_EQ(value(p(2, 2)), m(2, 2));
  ASSERT_DOUBLE_EQ(value(p(2, 3)), m(2, 3));
}
TEST_F(test_param_init_matrix, assignment_operator_dvar_matrix)
{
  gradient_structure gs;
  param_init_matrix p;
  p.allocate(1, 2, 1, 3, "p");
  p.initialize();
  ASSERT_DOUBLE_EQ(value(p(1, 1)), 0);
  ASSERT_DOUBLE_EQ(value(p(1, 2)), 0);
  ASSERT_DOUBLE_EQ(value(p(1, 3)), 0);
  ASSERT_DOUBLE_EQ(value(p(2, 1)), 0);
  ASSERT_DOUBLE_EQ(value(p(2, 2)), 0);
  ASSERT_DOUBLE_EQ(value(p(2, 3)), 0);

  dvar_matrix m(1, 2, 1, 3);
  m(1, 1) = 1;
  m(1, 2) = 2;
  m(1, 3) = 3;
  m(2, 1) = 4;
  m(2, 2) = 5;
  m(2, 3) = 6;
  p = m;
  ASSERT_DOUBLE_EQ(value(p(1, 1)), value(m(1, 1)));
  ASSERT_DOUBLE_EQ(value(p(1, 2)), value(m(1, 2)));
  ASSERT_DOUBLE_EQ(value(p(1, 3)), value(m(1, 3)));
  ASSERT_DOUBLE_EQ(value(p(2, 1)), value(m(2, 1)));
  ASSERT_DOUBLE_EQ(value(p(2, 2)), value(m(2, 2)));
  ASSERT_DOUBLE_EQ(value(p(2, 3)), value(m(2, 3)));
}
TEST_F(test_param_init_matrix, assignment_operator_dvariable)
{
  gradient_structure gs;
  param_init_matrix p;
  p.allocate(1, 2, 1, 3, "p");
  p.initialize();
  ASSERT_DOUBLE_EQ(value(p(1, 1)), 0);
  ASSERT_DOUBLE_EQ(value(p(1, 2)), 0);
  ASSERT_DOUBLE_EQ(value(p(1, 3)), 0);
  ASSERT_DOUBLE_EQ(value(p(2, 1)), 0);
  ASSERT_DOUBLE_EQ(value(p(2, 2)), 0);
  ASSERT_DOUBLE_EQ(value(p(2, 3)), 0);

  dvariable d = 5.5;
  p = d;
  ASSERT_DOUBLE_EQ(value(p(1, 1)), value(d));
  ASSERT_DOUBLE_EQ(value(p(1, 2)), value(d));
  ASSERT_DOUBLE_EQ(value(p(1, 3)), value(d));
  ASSERT_DOUBLE_EQ(value(p(2, 1)), value(d));
  ASSERT_DOUBLE_EQ(value(p(2, 2)), value(d));
  ASSERT_DOUBLE_EQ(value(p(2, 3)), value(d));
}
TEST_F(test_param_init_matrix, assignment_operator_double)
{
  gradient_structure gs;
  param_init_matrix p;
  p.allocate(1, 2, 1, 3, "p");
  p.initialize();
  ASSERT_DOUBLE_EQ(value(p(1, 1)), 0);
  ASSERT_DOUBLE_EQ(value(p(1, 2)), 0);
  ASSERT_DOUBLE_EQ(value(p(1, 3)), 0);
  ASSERT_DOUBLE_EQ(value(p(2, 1)), 0);
  ASSERT_DOUBLE_EQ(value(p(2, 2)), 0);
  ASSERT_DOUBLE_EQ(value(p(2, 3)), 0);

  double d = 5.5;
  p = d;
  ASSERT_DOUBLE_EQ(value(p(1, 1)), d);
  ASSERT_DOUBLE_EQ(value(p(1, 2)), d);
  ASSERT_DOUBLE_EQ(value(p(1, 3)), d);
  ASSERT_DOUBLE_EQ(value(p(2, 1)), d);
  ASSERT_DOUBLE_EQ(value(p(2, 2)), d);
  ASSERT_DOUBLE_EQ(value(p(2, 3)), d);
}
TEST_F(test_param_init_matrix, allocate_phase_start)
{
  gradient_structure gs;
  param_init_matrix p;

  ad_integer rmin = 1;
  ad_integer rmax = 2;
  index_type cmin = 1;
  index_type cmax = 3;
  int expected_phase_start = 5;
  p.allocate(rmin, rmax, cmin, cmax, expected_phase_start, "p");

  ASSERT_EQ(p.get_phase_start(), expected_phase_start);
}
TEST_F(test_param_init_matrix, allocate_phase_start2)
{
  gradient_structure gs;
  param_init_matrix p;

  ad_integer rmin = 1;
  ad_integer rmax = 2;
  index_type cmin = 1;
  index_type cmax = 3;
  ad_integer expected_phase_start = 5;
  p.allocate(rmin, rmax, cmin, cmax, expected_phase_start, "p");

  ASSERT_EQ(p.get_phase_start(), expected_phase_start);
}
TEST_F(test_param_init_matrix, allocate_default_phase_start)
{
  gradient_structure gs;
  param_init_matrix p;

  ad_integer rmin = 1;
  ad_integer rmax = 2;
  index_type cmin = 1;
  index_type cmax = 3;
  int expected_phase_start = 1;
  p.allocate(rmin, rmax, cmin, cmax,  "p");

  ASSERT_EQ(p.get_phase_start(), expected_phase_start);
}
