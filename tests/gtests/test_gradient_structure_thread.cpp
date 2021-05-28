#include <gtest/gtest.h>
#include <fvar.hpp>
#include <gradient_structure.h>

extern "C"
{
  void test_ad_exit(const int exit_code);
}

class test_gradient_structure_thread: public ::testing::Test {};

TEST_F(test_gradient_structure_thread, instance)
{
  ASSERT_TRUE(gradient_structure::_instance == nullptr);
}
TEST_F(test_gradient_structure_thread, create)
{
  gradient_structure::create();

  ASSERT_TRUE(gradient_structure::get() != nullptr);

  delete gradient_structure::_instance;
  gradient_structure::_instance = nullptr;

  ASSERT_TRUE(gradient_structure::get() == nullptr);
}
