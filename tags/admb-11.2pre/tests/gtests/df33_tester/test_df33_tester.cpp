#include <gtest/gtest.h>
#include <fvar.hpp>
#include <admodel.h>
#include <df1b2fun.h>

gradient_structure gs(1500000L);

extern "C"  
{
  void test_ad_exit(const int exit_code)
  {
    throw exit_code;
  }
}

class test_df33_tester : public ::testing::Test 
{
};

int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  ad_exit=&test_ad_exit;
  return RUN_ALL_TESTS();
}
