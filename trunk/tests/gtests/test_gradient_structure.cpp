#include <gtest/gtest.h>
#include <gradient_structure.h>
#include <gradient_structure.h>

extern "C"
{
  void test_ad_exit(const int exit_code);
}

class test_gradient_structure :public ::testing::Test {};

TEST_F(test_gradient_structure, checktypes)
{
  ASSERT_EQ(sizeof(long long), sizeof(long long int));
}
TEST_F(test_gradient_structure, default_constructor)
{
  gradient_structure gs;
}
/*
TEST_F(test_gradient_structure, default_constructor2x)
{
  {
    gradient_structure gs;
  }
  {
    gradient_structure gs;
  }
}
TEST_F(test_gradient_structure, default_constructorb2b)
{
  ad_exit=&test_ad_exit;
  try
  {
    gradient_structure gs;
    gradient_structure gs2;
  }
  catch (const int exit_code)          
  {   
    return;
  }

  FAIL();
}
*/
