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

  ad_comm::argc = 0;
  ad_comm::argv = NULL;
  gradient_structure gs;
  param_init_d3array p;

  ad_integer sl = 1;
  ad_integer sh = 2;
  index_type nrl = 3;
  index_type nrh = 4;
  index_type ncl = 5;
  index_type nch = 6;
  int expected_phase_start = 7;

  p.allocate(sl, sh, nrl, nrh, ncl, nch, expected_phase_start, "p");

  ASSERT_EQ(p.get_phase_start(), expected_phase_start);
}
TEST_F(test_param_init_d3array, allocate_phase_start_int)
{
  ad_exit=&test_ad_exit;

  ad_comm::argc = 0;
  ad_comm::argv = NULL;
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

  ad_comm::argc = 0;
  ad_comm::argv = NULL;
  gradient_structure gs;
  param_init_d3array p;

  ad_integer sl = 1;
  ad_integer sh = 2;
  index_type nrl = 3;
  index_type nrh = 4;
  index_type ncl = 5;
  index_type nch = 6;
  int expected_phase_start = 1;

  p.allocate(sl, sh, nrl, nrh, ncl, nch, "p");

  ASSERT_EQ(p.get_phase_start(), expected_phase_start);
}
TEST_F(test_param_init_d3array, allocate_phase_start_int_default)
{
  ad_exit=&test_ad_exit;

  ad_comm::argc = 0;
  ad_comm::argv = NULL;
  gradient_structure gs;
  param_init_d3array p;

  int sl = 1;
  int sh = 2;
  int nrl = 3;
  int nrh = 4;
  int ncl = 5;
  int nch = 6;
  int expected_phase_start = 1;

  p.allocate(sl, sh, nrl, nrh, ncl, nch, "p");

  ASSERT_EQ(p.get_phase_start(), expected_phase_start);
}
TEST_F(test_param_init_d3array, add_value)
{
  ad_exit=&test_ad_exit;

  ad_comm::argc = 0;
  ad_comm::argv = NULL;
  gradient_structure gs;
  param_init_d3array p;

  int sl = 1;
  int sh = 2;
  int nrl = 3;
  int nrh = 4;
  int ncl = 5;
  int nch = 6;
  int expected_phase_start = 1;

  p.allocate(sl, sh, nrl, nrh, ncl, nch, "p");

  p.initialize();

  ASSERT_EQ(p(1, 3, 5), 0);
  ASSERT_EQ(p(1, 3, 6), 0);
  ASSERT_EQ(p(1, 4, 5), 0);
  ASSERT_EQ(p(1, 4, 6), 0);
  ASSERT_EQ(p(2, 3, 5), 0);
  ASSERT_EQ(p(2, 3, 6), 0);
  ASSERT_EQ(p(2, 4, 5), 0);
  ASSERT_EQ(p(2, 4, 6), 0);

  dvector dev(1, 8);
  dev(1) = 823;
  dev(2) = -7;
  dev(3) = 9086;
  dev(4) = 2;
  dev(5) = -98;
  dev(6) = 83;
  dev(7) = -878947;
  dev(8) = -234;

  int ii = 1;
  p.add_value(dev, ii);
  ASSERT_EQ(p(1, 3, 5), dev(1));
  ASSERT_EQ(p(1, 3, 6), dev(2));
  ASSERT_EQ(p(1, 4, 5), dev(3));
  ASSERT_EQ(p(1, 4, 6), dev(4));
  ASSERT_EQ(p(2, 3, 5), dev(5));
  ASSERT_EQ(p(2, 3, 6), dev(6));
  ASSERT_EQ(p(2, 4, 5), dev(7));
  ASSERT_EQ(p(2, 4, 6), dev(8));

  ii = 1;
  double s;
  dvector diag(1, 8);
  diag(1) = -1;
  diag(2) = -1;
  diag(3) = -1;
  diag(4) = -1;
  diag(5) = -1;
  diag(6) = -1;
  diag(7) = -1;
  diag(8) = -1;
  p.add_value(dev, dev, ii, s, diag);

  ASSERT_EQ(p(1, 3, 5), 0);
  ASSERT_EQ(p(1, 3, 6), 0);
  ASSERT_EQ(p(1, 4, 5), 0);
  ASSERT_EQ(p(1, 4, 6), 0);
  ASSERT_EQ(p(2, 3, 5), 0);
  ASSERT_EQ(p(2, 3, 6), 0);
  ASSERT_EQ(p(2, 4, 5), 0);
  ASSERT_EQ(p(2, 4, 6), 0);
}
