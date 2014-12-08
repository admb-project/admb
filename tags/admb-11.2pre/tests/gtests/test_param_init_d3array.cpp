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
