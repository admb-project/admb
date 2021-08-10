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
  ASSERT_TRUE(gradient_structure::get() == nullptr);
}
TEST_F(test_gradient_structure_thread, clean_empty)
{
  gradient_structure gs(1000, 0);

  ASSERT_TRUE(gradient_structure::get() == &gs);
  ASSERT_TRUE(gs.gradients == nullptr);
  ASSERT_TRUE(gs.gradients_size == 0);

  gs.clean();

  ASSERT_TRUE(gradient_structure::get() == &gs);
  ASSERT_TRUE(gs.gradients == nullptr);
  ASSERT_TRUE(gs.gradients_size == 0);
}
TEST_F(test_gradient_structure_thread, clean0)
{
  gradient_structure gs(1000, 0);
  ASSERT_TRUE(gradient_structure::get() == &gs);
  ASSERT_TRUE(gs.gradients == nullptr);
  ASSERT_TRUE(gs.gradients_size == 0);

  gs.create(0);
  ASSERT_TRUE(gradient_structure::get() == &gs);
  ASSERT_TRUE(gs.gradients == nullptr);
  ASSERT_TRUE(gs.gradients_size == 0);

  gs.clean();
  ASSERT_TRUE(gradient_structure::get() == &gs);
  ASSERT_TRUE(gs.gradients == nullptr);
  ASSERT_TRUE(gs.gradients_size == 0);
}
TEST_F(test_gradient_structure_thread, clean1)
{
  gradient_structure gs;

  ASSERT_TRUE(gradient_structure::get() == &gs);
  ASSERT_TRUE(gs.gradients == nullptr);
  ASSERT_TRUE(gs.gradients_size == 0);

  gs.create(1);

  ASSERT_TRUE(gs.gradients != nullptr);
  ASSERT_TRUE(gs.gradients[0] == &gs);
  ASSERT_TRUE(gs.gradients[0]->x == 0);
  ASSERT_TRUE(gs.gradients_size == 1);

  gs.clean();

  ASSERT_TRUE(gradient_structure::get() == &gs);
  ASSERT_TRUE(gs.gradients == nullptr);
  ASSERT_TRUE(gs.gradients_size == 0);
}
TEST_F(test_gradient_structure_thread, clean2)
{
  ASSERT_TRUE(gradient_structure::get()->instances == 0);

  gradient_structure gs;

  ASSERT_TRUE(gradient_structure::get()->instances == 1);

  ASSERT_TRUE(gradient_structure::get() == &gs);
  ASSERT_TRUE(gs.gradients == nullptr);
  ASSERT_TRUE(gs.gradients_size == 0);

  gs.create(2);

  ASSERT_TRUE(gradient_structure::get()->instances == 2);

  ASSERT_TRUE(gradient_structure::get() == &gs);
  ASSERT_TRUE(gs.gradients != nullptr);
  ASSERT_TRUE(gs.gradients[0] == &gs);
  ASSERT_TRUE(gs.gradients[1] != &gs);
  ASSERT_TRUE(gs.gradients[1] != gs.gradients[0]);
  ASSERT_TRUE(gs.gradients[0]->x == 0);
  ASSERT_TRUE(gs.gradients[1]->x == 1);
  ASSERT_TRUE(gs.gradients_size == 2);

  gs.clean();

  ASSERT_TRUE(gradient_structure::get()->instances == 1);

  ASSERT_TRUE(gradient_structure::get() == &gs);
  ASSERT_TRUE(gs.gradients == nullptr);
  ASSERT_TRUE(gs.gradients_size == 0);
}
TEST_F(test_gradient_structure_thread, get)
{
  gradient_structure gs;
  ASSERT_TRUE(gradient_structure::get() == &gs);
}
TEST_F(test_gradient_structure_thread, nested_fp)
{
  gradient_structure top;
  ASSERT_TRUE(strcmp(gradient_structure::get()->fp->cmpdif_file_name, "cmpdiff.tmp") == 0);
  ASSERT_TRUE(gradient_structure::get() == &top);
  {
    gradient_structure nested(10000L, 10);
    ASSERT_TRUE(gradient_structure::get() == &nested);
    ASSERT_TRUE(strcmp(gradient_structure::get()->fp->cmpdif_file_name, "cmpdiff10.tmp") == 0);
  }
  ASSERT_TRUE(gradient_structure::get() == nullptr);
  gradient_structure::reset(&top);
  ASSERT_TRUE(gradient_structure::get() == &top);
}
TEST_F(test_gradient_structure_thread, nested_grad_stack)
{
  gradient_structure top;
  ASSERT_TRUE(strcmp(gradient_structure::get()->GRAD_STACK1->gradfile_name, "gradfil1.tmp") == 0);
  ASSERT_TRUE(strcmp(gradient_structure::get()->GRAD_STACK1->gradfile_name1, "gradfil1.tmp") == 0);
  ASSERT_TRUE(strcmp(gradient_structure::get()->GRAD_STACK1->gradfile_name2, "gradfil2.tmp") == 0);
  ASSERT_TRUE(strcmp(gradient_structure::get()->GRAD_STACK1->var_store_file_name, "varssave.tmp") == 0);

  ASSERT_TRUE(gradient_structure::get() == &top);
  {
    gradient_structure nested(10000L, 10);
    ASSERT_TRUE(gradient_structure::get() == &nested);
    ASSERT_TRUE(strcmp(gradient_structure::get()->GRAD_STACK1->gradfile_name, "gradfil110.tmp") == 0);
    ASSERT_TRUE(strcmp(gradient_structure::get()->GRAD_STACK1->gradfile_name1, "gradfil110.tmp") == 0);
    ASSERT_TRUE(strcmp(gradient_structure::get()->GRAD_STACK1->gradfile_name2, "gradfil210.tmp") == 0);
    ASSERT_TRUE(strcmp(gradient_structure::get()->GRAD_STACK1->var_store_file_name, "varssave10.tmp") == 0);
  }
  ASSERT_TRUE(gradient_structure::get() == nullptr);
  gradient_structure::reset(&top);
  ASSERT_TRUE(gradient_structure::get() == &top);
}
