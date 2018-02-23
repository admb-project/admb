#include <gtest/gtest.h>
#include <fvar.hpp>
#include <climits>

class test_grad_stack: public ::testing::Test {};

/*
TEST_F(test_grad_stack, constructor_grad_stack_entry)
{
  {
    grad_stack_entry entry;
    ASSERT_TRUE(entry.func != NULL);
    ASSERT_TRUE(entry.dep_addr == NULL);
    ASSERT_TRUE(entry.ind_addr1 == NULL);
    ASSERT_DOUBLE_EQ(entry.mult1, 0.0);
    ASSERT_TRUE(entry.ind_addr2 == NULL);
    ASSERT_DOUBLE_EQ(entry.mult2, 0.0);
  }
}
*/
TEST_F(test_grad_stack, constructor)
{
  {
    grad_stack gstack;
    ASSERT_TRUE(gstack.ptr->func == NULL);
    ASSERT_TRUE(gstack.ptr->dep_addr == NULL);
    ASSERT_TRUE(gstack.ptr->ind_addr1 == NULL);
    ASSERT_DOUBLE_EQ(gstack.ptr->mult1, 0.0);
    ASSERT_TRUE(gstack.ptr->ind_addr2 == NULL);
    ASSERT_DOUBLE_EQ(gstack.ptr->mult2, 0.0);
  }
}
TEST_F(test_grad_stack, total)
{
  grad_stack gstack;
  ASSERT_TRUE(gstack.ptr != NULL);
  ASSERT_EQ(gstack.total(), 0);
  ++gstack.ptr;
  ASSERT_EQ(gstack.total(), 1);
  ++gstack.ptr;
  ASSERT_EQ(gstack.total(), 2);
}
TEST_F(test_grad_stack, set_gradient_stack)
{
  grad_stack gstack;
  ASSERT_EQ(gstack.total(), 0);
  gstack.set_gradient_stack(default_evaluation0);
  ASSERT_EQ(gstack.total(), 1);
  --gstack.ptr;
  ASSERT_TRUE(gstack.ptr->func == &default_evaluation0);
}
