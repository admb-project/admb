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
  ASSERT_TRUE(gradient_structure::gradients == nullptr);
  ASSERT_TRUE(gradient_structure::gradients_size == 0);

  gradient_structure::create(1);

  ASSERT_TRUE(gradient_structure::gradients != nullptr);
  ASSERT_TRUE(gradient_structure::gradients[0]->x == 0);
  ASSERT_TRUE(gradient_structure::gradients[1]->x == 1);
  ASSERT_TRUE(gradient_structure::gradients_size == 2);

  gradient_structure::clean();

  ASSERT_TRUE(gradient_structure::gradients == nullptr);
  ASSERT_TRUE(gradient_structure::gradients_size == 0);
}
TEST_F(test_gradient_structure_thread, get)
{
  gradient_structure gs;
  ASSERT_TRUE(gradient_structure::get() == &gs);
}
