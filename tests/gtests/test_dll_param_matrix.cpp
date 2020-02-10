#include <gtest/gtest.h>
#include "admodel.h"

class test_dll_param_matrix: public ::testing::Test 
{
protected:
  double d;
};

TEST_F(test_dll_param_matrix, constructor)
{
  gradient_structure gs;
  dll_param_matrix m;
  m.allocate(&d, 1, 4, 2, 3, "m");

  ASSERT_STREQ("m", m.get_name());
}
