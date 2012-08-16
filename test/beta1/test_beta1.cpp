#include <gtest/gtest.h>

extern "C"  
{
  void test_ad_exit(const int exit_code)
  {
    throw exit_code;
  }
}

class test_admb_messages: public ::testing::Test {};

#define main beta1_main
#include "beta1.cpp"
#undef main

TEST(beta1, test2)
{
  const int argc = 1;
  const char* argv[] = {"beta1"};
  beta1_main(argc, argv);
}
TEST(beta1, test3)
{
  const int argc = 1;
  const char* argv[] = {"beta1"};
  beta1_main(argc, argv);
}
int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  ad_exit=&test_ad_exit;
  return RUN_ALL_TESTS();
}
