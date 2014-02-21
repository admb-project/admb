#include <gtest/gtest.h>

extern "C"
{
  void test_ad_exit(const int exit_code)
  {
    throw exit_code;
  }
}

int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
