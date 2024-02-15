#include <gtest/gtest.h>
#include "admodel.h"

void test_ad_exit(const int exit_code);

class test_dll_param_init_bounded_vector: public ::testing::Test
{
protected:
  double d;
};

TEST_F(test_dll_param_init_bounded_vector, constructor)
{
  gradient_structure gs;
  dll_param_init_bounded_vector v;
  ASSERT_EQ(0, v.indexmin());
  ASSERT_EQ(-1, v.indexmax());
  ASSERT_EQ(0, v.get_phase_start());
}
TEST_F(test_dll_param_init_bounded_vector, allocate)
{
  double* values = new double[4];
  values[0] = 0;
  values[1] = 1;
  values[2] = 2;
  values[3] = 3;
  gradient_structure gs;
  dll_param_init_bounded_vector v;
  v.allocate(values, 1, 4, 0, 0, 5, "v");
  ASSERT_EQ(1, v.indexmin());
  ASSERT_EQ(4, v.indexmax());
  ASSERT_EQ(5, v.get_phase_start());

  delete [] values;
  values = nullptr;
}
