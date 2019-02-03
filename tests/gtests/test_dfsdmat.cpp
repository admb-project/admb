#include <gtest/gtest.h>
#include <fvar.hpp>

class test_dfsdmat: public ::testing::Test {};

TEST_F(test_dfsdmat, default_constructor)
{
  gradient_structure gs;

  ASSERT_FALSE(gradient_structure::get_USE_FOR_HESSIAN());
  dfsdmat mat;
  ASSERT_TRUE(!mat);
}
TEST_F(test_dfsdmat, default_int_constructor_without_USE_FOR_HESSIAN)
{
  gradient_structure gs;

  ASSERT_FALSE(gradient_structure::get_USE_FOR_HESSIAN());

  dfsdmat mat(1);
  ASSERT_FALSE(!mat);
  ASSERT_TRUE(mat.get_ptr() != gradient_structure::get()->hessian_ptr);
}
TEST_F(test_dfsdmat, default_int_constructor_with_USE_FOR_HESSIAN)
{
  gradient_structure gs;

  gradient_structure::set_USE_FOR_HESSIAN(1);
  ASSERT_TRUE(gradient_structure::get_USE_FOR_HESSIAN());

  dfsdmat mat(1);
  ASSERT_FALSE(!mat);
  ASSERT_TRUE(mat.get_ptr() == gradient_structure::get()->hessian_ptr);
}
