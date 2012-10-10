#include <gtest/gtest.h>

extern "C"  
{
  void test_ad_exit(const int exit_code)
  {
    throw exit_code;
  }
}

#define main beta_deviate_main
#include "minto.cpp"
#undef main

class tests_beta_deviate: public ::testing::Test 
{
protected:
  tests_beta_deviate() {
  }
  virtual ~tests_beta_deviate() {
  }
  virtual void SetUp() {
  }
  virtual void TearDown() {
  }
};
TEST(tests_beta_deviate, a)
{
  const int argc = 1;
  const char* argv[] = {"minto"};
  beta_deviate_main(argc, argv);
}
TEST(tests_beta_deviate, b)
{
  const int argc = 1;
  const char* argv[] = {"minto"};
  beta_deviate_main(argc, argv);
}
TEST(tests_beta_deviate, c)
{
  const int argc = 1;
  const char* argv[] = {"minto"};
  beta_deviate_main(argc, argv);
}
int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  ad_exit=&test_ad_exit;
  return RUN_ALL_TESTS();
}
