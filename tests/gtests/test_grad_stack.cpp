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
  grad_stack gstack(10);

  ASSERT_EQ(gstack.length, 10);
  ASSERT_TRUE(&gstack.true_ptr_first[0] == gstack.ptr_first);
  ASSERT_TRUE(&gstack.true_ptr_first[9] == gstack.ptr_last);
  ASSERT_TRUE(gstack.ptr == gstack.ptr_first);
  ASSERT_EQ(gstack.end_pos, 0);
  ASSERT_EQ(gstack.end_pos1, 0);
  ASSERT_EQ(gstack.end_pos2, 0);
  ASSERT_EQ(gstack.total(), 0);
  ASSERT_EQ(strcmp(gstack.gradfile_name2, "gradfil2.tmp"), 0);
  ASSERT_EQ(strcmp(gstack.gradfile_name1, "gradfil1.tmp"), 0);
  ASSERT_EQ(strcmp(gstack.gradfile_name, "gradfil1.tmp"), 0);
  ASSERT_EQ(strcmp(gstack.get_gradfile_name(), "gradfil1.tmp"), 0);
  ASSERT_EQ(strcmp(gstack.var_store_file_name, "varssave.tmp"), 0);
  ASSERT_TRUE(gstack._GRADFILE_PTR != -1);
  ASSERT_TRUE(gstack.gradfile_handle() != -1);
  ASSERT_TRUE(gstack._GRADFILE_PTR == gstack._GRADFILE_PTR1);
  ASSERT_TRUE(gstack._GRADFILE_PTR2 != -1);
  ASSERT_TRUE(gstack._VARSSAV_PTR != -1);
  ASSERT_TRUE(lseek(gstack._VARSSAV_PTR, 0, SEEK_CUR) == 0);
  ASSERT_TRUE(lseek(gstack._GRADFILE_PTR, 0, SEEK_CUR) == 0);
  ASSERT_TRUE(lseek(gstack._GRADFILE_PTR2, 0, SEEK_CUR) == 0);

  size_t count = 1;
  while (gstack.ptr != gstack.ptr_last)
  {
    ASSERT_TRUE(gstack.ptr->func == NULL);
    ASSERT_TRUE(gstack.ptr->dep_addr == NULL);
    ASSERT_TRUE(gstack.ptr->ind_addr1 == NULL);
    ASSERT_DOUBLE_EQ(gstack.ptr->mult1, 0.0);
    ASSERT_TRUE(gstack.ptr->ind_addr2 == NULL);
    ASSERT_DOUBLE_EQ(gstack.ptr->mult2, 0.0);
    ++(gstack.ptr);
    ++count;
  }
  ASSERT_EQ(gstack.length, count);
}
TEST_F(test_grad_stack, total)
{
  grad_stack gstack(10);
  ASSERT_TRUE(gstack.ptr != NULL);
  ASSERT_EQ(gstack.total(), 0);
  ++gstack.ptr;
  ASSERT_EQ(gstack.total(), 1);
  ++gstack.ptr;
  ASSERT_EQ(gstack.total(), 2);
}
TEST_F(test_grad_stack, set_gradient_stack)
{
  grad_stack gstack(10);
  ASSERT_EQ(gstack.total(), 0);
  gstack.set_gradient_stack(default_evaluation0);
  ASSERT_EQ(gstack.total(), 1);
  --gstack.ptr;
}
TEST_F(test_grad_stack, write_grad_stack_buffer)
{
  double values[4];
  grad_stack gstack(3);
  gstack.set_gradient_stack0(default_evaluation0, &values[0]);
  gstack.set_gradient_stack0(default_evaluation0, &values[1]);
  gstack.set_gradient_stack0(default_evaluation0, &values[2]);
  ASSERT_EQ(gstack.total(), 3);

  int i = 0;
  for (grad_stack_entry* p = gstack.ptr_first; p <= gstack.ptr_last; ++p)
  {
    ASSERT_TRUE(p->func == &default_evaluation0);
    ASSERT_TRUE(p->dep_addr == &values[i]);
    ASSERT_TRUE(p->ind_addr1 == NULL);
    ASSERT_DOUBLE_EQ(p->mult1, 0.0);
    ASSERT_TRUE(p->ind_addr2 == NULL);
    ASSERT_DOUBLE_EQ(p->mult2, 0.0);
    ++i;
  }

  ASSERT_TRUE(lseek(gstack._VARSSAV_PTR, 0, SEEK_CUR) == 0);
  ASSERT_TRUE(lseek(gstack._GRADFILE_PTR, 0, SEEK_CUR) == 0);
  ASSERT_TRUE(lseek(gstack._GRADFILE_PTR2, 0, SEEK_CUR) == 0);

  gstack.set_gradient_stack0(default_evaluation0, &values[3]);
  ASSERT_EQ(gstack.total(), 1);

  for (grad_stack_entry* p = gstack.ptr; p <= gstack.ptr_last; ++p)
  {
    ASSERT_TRUE(p->func == NULL);
    ASSERT_TRUE(p->dep_addr == NULL);
    ASSERT_TRUE(p->ind_addr1 == NULL);
    ASSERT_DOUBLE_EQ(p->mult1, 0.0);
    ASSERT_TRUE(p->ind_addr2 == NULL);
    ASSERT_DOUBLE_EQ(p->mult2, 0.0);
    ++i;
  }

  ASSERT_TRUE(lseek(gstack._VARSSAV_PTR, 0, SEEK_CUR) == 0);
  ASSERT_TRUE(lseek(gstack._GRADFILE_PTR, 0, SEEK_CUR) == sizeof(grad_stack_entry) * 3);
  ASSERT_TRUE(lseek(gstack._GRADFILE_PTR2, 0, SEEK_CUR) == 0);

  off_t offset= sizeof(grad_stack_entry) * 3;
  off_t lpos = lseek(gstack._GRADFILE_PTR, -offset, SEEK_CUR);
  int result = gstack.read_grad_stack_buffer(lpos);
  ASSERT_EQ(result, 1);

  ASSERT_TRUE(lseek(gstack._VARSSAV_PTR, 0, SEEK_CUR) == 0);
  ASSERT_TRUE(lseek(gstack._GRADFILE_PTR, 0, SEEK_CUR) == 0);
  ASSERT_TRUE(lseek(gstack._GRADFILE_PTR2, 0, SEEK_CUR) == 0);

  i = 0;
  for (grad_stack_entry* p = gstack.ptr_first; p <= gstack.ptr_last; ++p)
  {
    ASSERT_TRUE(p->func == &default_evaluation0);
    ASSERT_TRUE(p->dep_addr == &values[i]);
    ASSERT_TRUE(p->ind_addr1 == NULL);
    ASSERT_DOUBLE_EQ(p->mult1, 0.0);
    ASSERT_TRUE(p->ind_addr2 == NULL);
    ASSERT_DOUBLE_EQ(p->mult2, 0.0);
    ++i;
  }
}
