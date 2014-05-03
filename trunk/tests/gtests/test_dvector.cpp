#include <gtest/gtest.h>
#include <dvector.h>

extern "C"
{
  void test_ad_exit(const int exit_code);
}

class test_dvector: public ::testing::Test {};

TEST_F(test_dvector, constructor)
{
  ad_exit=&test_ad_exit;

  try
  {
    dvector v(1, 10);
    dvector w(0, 1000);
    v(0, 1000) = w;
  }
  catch (const int exit_code)          
  {   
    const int expected_exit_code = 1;
    if (exit_code == expected_exit_code)
    {
      return;
    }
  }
  FAIL();
}
