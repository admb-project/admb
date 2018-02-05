#include <gtest/gtest.h>
#include <fvar.hpp>
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
TEST_F(test_gradient_structure, default_constructor2x)
{
  {
    gradient_structure gs;
  }
  {
    gradient_structure gs;
  }
}
/*
TEST_F(test_gradient_structure, default_constructorb2b)
{
  ad_exit = &test_ad_exit;

  ASSERT_ANY_THROW({
    gradient_structure gs;
    gradient_structure gs2;
  });
  gradient_structure gs;
}
*/
