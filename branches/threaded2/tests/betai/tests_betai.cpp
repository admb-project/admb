#include <gtest/gtest.h>

extern "C"  
{
  void test_ad_exit(const int exit_code)
  {
    throw exit_code;
  }
}

#define main betai_main
#include "betai.cpp"
#undef main

class tests_betai: public ::testing::Test 
{
protected:
  tests_betai() {
  }
  virtual ~tests_betai() {
  }
  virtual void SetUp() {
  }
  virtual void TearDown() {
  }
};

TEST(tests_betai, a)
{
  const int argc = 1;
  const char* argv[] = {"betai"};
  betai_main(argc, argv);
}

TEST(tests_betai, b)
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
