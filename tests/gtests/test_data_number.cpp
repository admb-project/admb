#include <gtest/gtest.h>
#include <df1b2fun.h>

extern "C"
{
  void test_ad_exit(const int exit_code);
}

class test_data_number: public ::testing::Test {};

TEST_F(test_data_number, constructor)
{
  ad_exit=&test_ad_exit;

  data_number M;
  M = 4;
  double d = M;
  try
  {
    value(d);
  }
  catch (const int exit_code)
  {
    SUCCEED();
    return;
  }
  FAIL();
}
