#include <gtest/gtest.h>
#include <fvar.hpp>

class test_dfsdmat: public ::testing::Test {};

TEST_F(test_dfsdmat, default_constructor)
{
  gradient_structure gs;

  dfsdmat mat;
  ASSERT_TRUE(!mat);

  ASSERT_TRUE(gradient_structure::get_USE_FOR_HESSIAN());
}
