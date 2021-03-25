#include <gtest/gtest.h>
#include "admodel.h"

class test_param_init_number: public ::testing::Test {};

TEST_F(test_param_init_number, constructor)
{
  gradient_structure gs;
  dll_param_init_number n;
}
TEST_F(test_param_init_number, allocate_assignments)
{
  gradient_structure gs;
  dll_param_init_number n;

  double expected_pd = 5;
  n.allocate(&expected_pd, "test_param_init_number");
  ASSERT_DOUBLE_EQ(expected_pd, value(n));

  n = 10;
  ASSERT_DOUBLE_EQ(10, value(n));

  dvariable var = 20;
  n = var;
  ASSERT_DOUBLE_EQ(value(var), value(n));
}
TEST_F(test_param_init_number, save_value)
{
  gradient_structure gs;
  dll_param_init_number n;

  double expected_pd = 5.41000002;
  n.allocate(&expected_pd, "test_param_init_number");
  ASSERT_DOUBLE_EQ(expected_pd, value(n));

  ofstream ofs("test_param_init_number.txt");
  n.save_value(ofs);
  ofs.close();

  ifstream ifs("test_param_init_number.txt");
  std::string line;
  getline(ifs, line);
  ifs.close();
}
TEST_F(test_param_init_number, add_value)
{
  ad_comm::argc = 0;
  ad_comm::argv = NULL;
  gradient_structure gs;
  param_init_number p;

  int expected_phase_start = 1;

  p.allocate("p");
  p = 0;

  ASSERT_EQ(value(p), 0);

  dvector dev(1, 1);
  dev(1) = 823;

  int ii = 1;
  p.add_value(dev, ii);
  ASSERT_EQ(value(p), dev(1));

  ii = 1;
  double s;
  dvector diag(1, 4);
  diag(1) = -1;
  p.add_value(dev, dev, ii, s, diag);

  ASSERT_EQ(value(p), 0);
}
