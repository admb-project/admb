#include <gtest/gtest.h>
#include "admb_messages.h"

extern "C"  
{
  void test_ad_exit(const int exit_code)
  {
    throw exit_code;
  }
}

class test_admb_messages: public ::testing::Test {};

#include <fvar.hpp>
#include <admodel.h>
#include <df1b2fun.h>

gradient_structure gs(1500000L);
#include "tools99_string1.cpp"
#include "tools99_string5.cpp"
#include "linad99_model49.cpp"
#include "linad99_d5arr.cpp"
#include "linad99_d6arr.cpp"
#include "linad99_d4arr.cpp"
#include "linad99_d7arr.cpp"
#include "linad99_lmat1_lmat2_lmat4.cpp"
#include "linad99_imat1_imat2_imat4_imat7.cpp"
#include "linad99_i3arr1_i4arr_i5arr.cpp"
#include "linad99_f6arr.cpp"
#include "linad99_f5arr.cpp"
#include "linad99_f4arr.cpp"
#include "linad99.cpp"
#include "linad99_f7arr.cpp"
#include "df1b2_separable.cpp"

int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  ad_exit=&test_ad_exit;
  return RUN_ALL_TESTS();
}
