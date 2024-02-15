#include <gtest/gtest.h>
#include "admb_messages.h"
#include <fvar.hpp>
#include <admodel.h>
#include <df1b2fun.h>

void test_ad_exit(const int exit_code);

class test_admb_messages: public ::testing::Test 
{
  gradient_structure gs;
  void SetUp()
  {
    ad_exit = &test_ad_exit;
  }
  void TearDown()
  {
    ad_exit = nullptr;
  }
};

#define _CONST const
#include "admb_messages/tools99_string1.cpp"
#include "admb_messages/tools99_string5.cpp"
//#include "admb_messages/linad99_model49.cpp"
#include "admb_messages/linad99_d5arr.cpp"
#include "admb_messages/linad99_d6arr.cpp"
#include "admb_messages/linad99_d4arr.cpp"
#include "admb_messages/linad99_d7arr.cpp"
#include "admb_messages/linad99_lmat1_lmat2_lmat4.cpp"
#include "admb_messages/linad99_imat1_imat2_imat4_imat7.cpp"
#include "admb_messages/linad99_i3arr1_i4arr_i5arr.cpp"
#include "admb_messages/linad99_f6arr.cpp"
#include "admb_messages/linad99_f5arr.cpp"
#include "admb_messages/linad99_f4arr.cpp"
#include "admb_messages/linad99.cpp"
#include "admb_messages/linad99_f7arr.cpp"
//#include "admb_messages/df1b2_separable.cpp"
