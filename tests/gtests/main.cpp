#include <gtest/gtest.h>
#ifdef __MINGW32__
#include <windows.h>
#endif
#include <fvar.hpp>

extern "C"
{
  void test_ad_exit(const int exit_code)
  {
    throw exit_code;
  }
}

int main(int argc, char** argv)
{
#ifdef __MINGW32__
  SetErrorMode(SEM_NOGPFAULTERRORBOX);
#endif
  ::testing::InitGoogleTest(&argc, argv);

  ad_exitptr = &test_ad_exit;

  return RUN_ALL_TESTS();
}
