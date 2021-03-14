#include <gtest/gtest.h>
#include "admodel.h"

extern "C"
{
  void test_ad_exit(const int exit_code);
}

class test_dll_param_init_bounded_vector: public ::testing::Test 
{
protected:
  double d;
};

TEST_F(test_dll_param_init_bounded_vector, constructor)
{
  //ad_exit=&test_ad_exit;

  gradient_structure gs;
  dll_param_init_bounded_vector m;
  m.allocate(&d, 1, 4, 2.0, 3.0, 5, "m");
  ASSERT_EQ(1, m.indexmin());
  ASSERT_EQ(4, m.indexmax());
  ASSERT_EQ(5, m.get_phase_start());
}
