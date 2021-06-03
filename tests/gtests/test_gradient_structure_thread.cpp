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
TEST_F(test_gradient_structure_thread, clean)
{
  ASSERT_TRUE(gradient_structure::_instance == nullptr);

  gradient_structure::create();

  ASSERT_TRUE(gradient_structure::get() != nullptr);

  gradient_structure::clean();

  ASSERT_TRUE(gradient_structure::get() == nullptr);
}
TEST_F(test_gradient_structure_thread, get)
{
  gradient_structure gs;
  ASSERT_TRUE(gradient_structure::get() == &gs);
}
