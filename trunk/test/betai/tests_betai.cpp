#include <gtest/gtest.h>

extern "C"  
{
  void test_ad_exit(const int exit_code)
  {
    throw exit_code;
  }
}

class test_admb_messages: public ::testing::Test {};

#define main betai_main
#include "betai.cpp"
#undef main

TEST(betai, test2)
{
  const int argc = 1;
  const char* argv[] = {"betai"};
  betai_main(argc, argv);
}
TEST(betai, test3)
{
  const int argc = 1;
  const char* argv[] = {"betai"};
  betai_main(argc, argv);
}
int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  ad_exit=&test_ad_exit;
  return RUN_ALL_TESTS();
}
