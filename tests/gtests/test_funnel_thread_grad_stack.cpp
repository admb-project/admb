#include <gtest/gtest.h>
#include <fvar.hpp>

class test_test_funnel_thread_grad_stack: public ::testing::Test {};

TEST_F(test_test_funnel_thread_grad_stack, default)
{
  grad_stack gs;

  ASSERT_EQ(gs.TOTAL_BYTES, 0);
  ASSERT_EQ(gs.PREVIOUS_TOTAL_BYTES, 0);
  ASSERT_NE(gs.gradfile_handle(), -1);
  ASSERT_STREQ(gs.get_gradfile_name(), "gradfil1.tmp");
  ASSERT_EQ(gs.total(), 0);
  ASSERT_TRUE(gs.ptr != nullptr);
}
TEST_F(test_test_funnel_thread_grad_stack, size_id)
{
  grad_stack gs(10, 0, 0, 0, 0, 2);

  ASSERT_EQ(gs.TOTAL_BYTES, 0);
  ASSERT_EQ(gs.PREVIOUS_TOTAL_BYTES, 0);
  ASSERT_NE(gs.gradfile_handle(), -1);
  ASSERT_STREQ(gs.get_gradfile_name(), "gradfil12.tmp");
  ASSERT_EQ(gs.total(), 0);
  ASSERT_TRUE(gs.ptr != nullptr);
}
TEST_F(test_test_funnel_thread_grad_stack, add_lambdas)
{
  grad_stack gs;

  ASSERT_EQ(gs.total(), 0);
  gs.set_gradient_stack([](){});
  ASSERT_EQ(gs.total(), 1);
  gs.set_gradient_stack([](){});
  ASSERT_EQ(gs.total(), 2);
  gs.set_gradient_stack([](){});
  ASSERT_EQ(gs.total(), 3);
  gs.set_gradient_stack([](){});
  ASSERT_EQ(gs.total(), 4);
}
TEST_F(test_test_funnel_thread_grad_stack, write_grad_stack_buffer)
{
  grad_stack gs;
  ASSERT_EQ(gs.TOTAL_BYTES, 0);
  ASSERT_EQ(gs.PREVIOUS_TOTAL_BYTES, 0);
  gs.write_grad_stack_buffer();
  ASSERT_EQ(gs.TOTAL_BYTES, 5000 * sizeof(grad_stack_entry));
  ASSERT_EQ(gs.PREVIOUS_TOTAL_BYTES, 0);
}
TEST_F(test_test_funnel_thread_grad_stack, write_grad_stack_buffer1x)
{
  grad_stack gs(1);
  ASSERT_EQ(gs.TOTAL_BYTES, 0);
  ASSERT_EQ(gs.PREVIOUS_TOTAL_BYTES, 0);
  gs.write_grad_stack_buffer();
  ASSERT_EQ(gs.TOTAL_BYTES, sizeof(grad_stack_entry));
  ASSERT_EQ(gs.PREVIOUS_TOTAL_BYTES, 0);
}
TEST_F(test_test_funnel_thread_grad_stack, write_grad_stack_buffer2x)
{
  grad_stack gs(2);
  ASSERT_EQ(gs.TOTAL_BYTES, 0);
  ASSERT_EQ(gs.PREVIOUS_TOTAL_BYTES, 0);
  gs.write_grad_stack_buffer();
  ASSERT_EQ(gs.TOTAL_BYTES, 2 * sizeof(grad_stack_entry));
  ASSERT_EQ(gs.PREVIOUS_TOTAL_BYTES, 0);
}
TEST_F(test_test_funnel_thread_grad_stack, no_gradient_structure)
{
  ASSERT_TRUE(gradient_structure::GRAD_STACK1 == nullptr);
  ASSERT_EQ(gradient_structure::totalbytes(), 0);
  ASSERT_EQ(gradient_structure::NUM_GRADSTACK_BYTES_WRITTEN(), 0);
}
TEST_F(test_test_funnel_thread_grad_stack, gradient_structure)
{
  gradient_structure gs;
  ASSERT_TRUE(gradient_structure::GRAD_STACK1 != nullptr);
  ASSERT_EQ(gradient_structure::totalbytes(), 0);
  ASSERT_EQ(gradient_structure::NUM_GRADSTACK_BYTES_WRITTEN(), 0);
}
