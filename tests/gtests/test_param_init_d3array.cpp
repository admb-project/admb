#include <gtest/gtest.h>
#include <admodel.h>

extern "C"
{
  void test_ad_exit(const int exit_code);
}

class test_param_init_d3array: public ::testing::Test {};

TEST_F(test_param_init_d3array, constructor)
{
  ad_exit=&test_ad_exit;

  param_init_d3array p;
}
TEST_F(test_param_init_d3array, allocate_phase_start)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;
  param_init_d3array p;

  ad_integer sl = 1;
  ad_integer sh = 2;
  index_type nrl = 3;
  index_type nrh = 3;
  index_type ncl = 4;
  index_type nch = 5;
  int expected_phase_start = 6;
  
  p.allocate(sl, sh, nrl, nrh, ncl, nch, expected_phase_start, "p");

  ASSERT_EQ(p.get_phase_start(), expected_phase_start);
}
TEST_F(test_param_init_d3array, allocate_phase_start_int)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;
  param_init_d3array p;

  int sl = 1;
  int sh = 2;
  int nrl = 3;
  int nrh = 4;
  int ncl = 5;
  int nch = 6;
  int expected_phase_start = 7;
  
  p.allocate(sl, sh, nrl, nrh, ncl, nch, expected_phase_start, "p");

  ASSERT_EQ(p.get_phase_start(), expected_phase_start);
}
TEST_F(test_param_init_d3array, allocate_phase_start_default)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;
  param_init_d3array p;

  ad_integer sl = 1;
  ad_integer sh = 2;
  index_type nrl = 3;
  index_type nrh = 3;
  index_type ncl = 4;
  index_type nch = 5;
  int expected_phase_start = 1;
  
  p.allocate(sl, sh, nrl, nrh, ncl, nch, "p");

  ASSERT_EQ(p.get_phase_start(), expected_phase_start);
}
TEST_F(test_param_init_d3array, allocate_phase_start_int_default)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;
  param_init_d3array p;

  int sl = 1;
  int sh = 2;
  int nrl = 3;
  int nrh = 3;
  int ncl = 4;
  int nch = 5;
  int expected_phase_start = 1;
  
  p.allocate(sl, sh, nrl, nrh, ncl, nch, "p");

  ASSERT_EQ(p.get_phase_start(), expected_phase_start);
}
