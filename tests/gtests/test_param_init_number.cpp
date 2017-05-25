#include <gtest/gtest.h>
#include "admodel.h"

class test_param_init_number: public ::testing::Test {};

TEST_F(test_param_init_number, constructor)
{
  gradient_structure gs;
  dll_param_init_number n;
  //double pd = 5;
  //n.allocate(&pd, 0, "test_param_init_number");
}
