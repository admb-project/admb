#include <cstring>
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
TEST_F(test_gradient_structure_thread, multiple)
{
  {
  gradient_structure a;
  ASSERT_TRUE(gradient_structure::get() == &a);
  gradient_structure b;
  ASSERT_TRUE(gradient_structure::get() == &b);
  gradient_structure c;
  ASSERT_TRUE(gradient_structure::get() == &c);

  gradient_structure::reset(&a);
  ASSERT_TRUE(gradient_structure::get() == &a);
  gradient_structure::reset(&c);
  ASSERT_TRUE(gradient_structure::get() == &c);
  gradient_structure::reset(&b);
  ASSERT_TRUE(gradient_structure::get() == &b);
  ASSERT_TRUE(gradient_structure::instances == 3);
  }
  ASSERT_TRUE(gradient_structure::get() == nullptr);
  ASSERT_TRUE(gradient_structure::instances == 0);
}
TEST_F(test_gradient_structure_thread, multiple_fp)
{
  {
  gradient_structure a(100000L, 1);
  gradient_structure b(100000L, 5);

  ASSERT_TRUE(a.x == 1);
  ASSERT_TRUE(b.x == 5);
  ASSERT_TRUE(a.fp != b.fp);
  ASSERT_TRUE(a.fp->file_ptr != b.fp->file_ptr);
  ASSERT_TRUE(strcmp(a.fp->cmpdif_file_name, "cmpdiff1.tmp") == 0);
  ASSERT_TRUE(strcmp(b.fp->cmpdif_file_name, "cmpdiff5.tmp") == 0);

  int expected_a_int = 5;
  double expected_a_double = 5.9;
  int expected_b_int = -2;
  double expected_b_double = -2.5;
  a.fp->fwrite(expected_a_int);
  b.fp->fwrite(expected_b_int);
  a.fp->fwrite(expected_a_double);
  b.fp->fwrite(expected_b_double);
  int read_a_int;
  double read_a_double;
  int read_b_int;
  double read_b_double;
  b.fp->fread(read_b_double);
  b.fp->fread(read_b_int);
  a.fp->fread(read_a_double);
  a.fp->fread(read_a_int);

  ASSERT_EQ(read_a_int, expected_a_int);
  ASSERT_EQ(read_b_int, expected_b_int);
  ASSERT_EQ(read_a_double, expected_a_double);
  ASSERT_EQ(read_b_double, expected_b_double);
  }
}
void empty_a1() { }
void empty_a2() { }
void empty_a3() { }
void empty_b1() { }
void empty_b2() { }
TEST_F(test_gradient_structure_thread, multiple_grad_stack)
{
  {
  gradient_structure a(100000L, 1);
  gradient_structure b(100000L, 5);

  ASSERT_TRUE(a.GRAD_STACK1 != b.GRAD_STACK1);

  ASSERT_TRUE(strcmp(a.GRAD_STACK1->gradfile_name, "gradfil11.tmp") == 0);
  ASSERT_TRUE(strcmp(a.GRAD_STACK1->gradfile_name1, "gradfil11.tmp") == 0);
  ASSERT_TRUE(strcmp(a.GRAD_STACK1->gradfile_name2, "gradfil21.tmp") == 0);
  ASSERT_TRUE(strcmp(a.GRAD_STACK1->var_store_file_name, "varssave1.tmp") == 0);
  ASSERT_TRUE(strcmp(b.GRAD_STACK1->gradfile_name, "gradfil15.tmp") == 0);
  ASSERT_TRUE(strcmp(b.GRAD_STACK1->gradfile_name1, "gradfil15.tmp") == 0);
  ASSERT_TRUE(strcmp(b.GRAD_STACK1->gradfile_name2, "gradfil25.tmp") == 0);
  ASSERT_TRUE(strcmp(b.GRAD_STACK1->var_store_file_name, "varssave5.tmp") == 0);

  a.GRAD_STACK1->set_gradient_stack(empty_a1);
  a.GRAD_STACK1->set_gradient_stack(empty_a2);
  a.GRAD_STACK1->set_gradient_stack(empty_a3);

  ASSERT_EQ(a.GRAD_STACK1->total(), 3);
  ASSERT_EQ(b.GRAD_STACK1->total(), 0);

  b.GRAD_STACK1->set_gradient_stack(empty_b1);
  b.GRAD_STACK1->set_gradient_stack(empty_b2);

  ASSERT_EQ(a.GRAD_STACK1->total(), 3);
  ASSERT_EQ(b.GRAD_STACK1->total(), 2);

  ASSERT_TRUE(gradient_structure::get() == &b);

  ASSERT_EQ(a.TOTAL_BYTES, 0);
  ASSERT_EQ(b.TOTAL_BYTES, 0);

  OFF_T abegin_lpos = LSEEK(a.GRAD_STACK1->_GRADFILE_PTR, 0, SEEK_CUR);
  OFF_T bbegin_lpos = LSEEK(b.GRAD_STACK1->_GRADFILE_PTR, 0, SEEK_CUR);

  ASSERT_EQ(abegin_lpos, 0);
  ASSERT_EQ(bbegin_lpos, 0);

  a.GRAD_STACK1->write_grad_stack_buffer(&a);
  ASSERT_EQ(a.GRAD_STACK1->total(), 0);
  ASSERT_EQ(b.GRAD_STACK1->total(), 2);
  // 5000 because of grad_stack::set_gbuffer_pointers
  ASSERT_EQ(a.GRAD_STACK1->length, 5000);
  size_t aexpected_total_bytes = a.GRAD_STACK1->length * sizeof(grad_stack_entry);
  ASSERT_EQ(a.TOTAL_BYTES, aexpected_total_bytes);
  ASSERT_EQ(b.TOTAL_BYTES, 0);

  b.GRAD_STACK1->write_grad_stack_buffer(&b);
  ASSERT_EQ(a.GRAD_STACK1->total(), 0);
  ASSERT_EQ(b.GRAD_STACK1->total(), 0);
  ASSERT_EQ(b.GRAD_STACK1->length, 5000);
  size_t bexpected_total_bytes = b.GRAD_STACK1->length * sizeof(grad_stack_entry);
  ASSERT_EQ(a.TOTAL_BYTES, aexpected_total_bytes);
  ASSERT_EQ(b.TOTAL_BYTES, bexpected_total_bytes);

  OFF_T aend_lpos = LSEEK(a.GRAD_STACK1->_GRADFILE_PTR, 0, SEEK_CUR);
  OFF_T bend_lpos = LSEEK(b.GRAD_STACK1->_GRADFILE_PTR, 0, SEEK_CUR);

  ASSERT_EQ(aend_lpos, aexpected_total_bytes);
  ASSERT_EQ(bend_lpos, bexpected_total_bytes);

  OFF_T reta = LSEEK(a.GRAD_STACK1->_GRADFILE_PTR, -aend_lpos, SEEK_CUR);
  ASSERT_EQ(abegin_lpos, reta);
  a.GRAD_STACK1->read_grad_stack_buffer(abegin_lpos);
  OFF_T retb = LSEEK(b.GRAD_STACK1->_GRADFILE_PTR, -bend_lpos, SEEK_CUR);
  ASSERT_EQ(bbegin_lpos, retb);
  b.GRAD_STACK1->read_grad_stack_buffer(bbegin_lpos);

  ASSERT_TRUE(a.GRAD_STACK1->true_ptr_first[0].func == empty_a1);
  ASSERT_TRUE(a.GRAD_STACK1->true_ptr_first[1].func == empty_a2);
  ASSERT_TRUE(a.GRAD_STACK1->true_ptr_first[2].func == empty_a3);
  ASSERT_TRUE(b.GRAD_STACK1->true_ptr_first[0].func == empty_b1);
  ASSERT_TRUE(b.GRAD_STACK1->true_ptr_first[1].func == empty_b2);

  ASSERT_EQ(a.GRAD_STACK1->total(), 4999);
  ASSERT_EQ(b.GRAD_STACK1->total(), 4999);

  //Must manually reset ptr
  a.GRAD_STACK1->ptr = a.GRAD_STACK1->ptr_first + 3;
  b.GRAD_STACK1->ptr = b.GRAD_STACK1->ptr_first + 2;

  ASSERT_EQ(a.GRAD_STACK1->total(), 3);
  ASSERT_EQ(b.GRAD_STACK1->total(), 2);
  }
}
TEST_F(test_gradient_structure_thread, cleanup_temporary_files)
{
  {
  gradient_structure* a = new gradient_structure(100000L, 1);

  ASSERT_TRUE(gradient_structure::get() == a);

  a = nullptr;

  ASSERT_TRUE(gradient_structure::get() != a);

  void cleanup_temporary_files();
  cleanup_temporary_files();

  ASSERT_TRUE(gradient_structure::get() == nullptr);
  }
}