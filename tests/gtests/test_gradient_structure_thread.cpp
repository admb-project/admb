#include <cstring>
#include <gtest/gtest.h>
#include <fvar.hpp>
#include <gradient_structure.h>

void test_ad_exit(const int exit_code);

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
  //ASSERT_TRUE(gs.gradients[0]->x == 0);
  ASSERT_TRUE(gs.gradients_size == 1);

  gs.clean();

  ASSERT_TRUE(gradient_structure::get() == &gs);
  ASSERT_TRUE(gs.gradients == nullptr);
  ASSERT_TRUE(gs.gradients_size == 0);
}
TEST_F(test_gradient_structure_thread, clean2)
{

  gradient_structure gs;


  ASSERT_TRUE(gradient_structure::get() == &gs);
  ASSERT_TRUE(gs.gradients == nullptr);
  ASSERT_TRUE(gs.gradients_size == 0);

  gs.create(2);


  ASSERT_TRUE(gradient_structure::get() == &gs);
  ASSERT_TRUE(gs.gradients != nullptr);
  ASSERT_TRUE(gs.gradients[0] == &gs);
  ASSERT_TRUE(gs.gradients[1] != &gs);
  ASSERT_TRUE(gs.gradients[1] != gs.gradients[0]);
  //ASSERT_TRUE(gs.gradients[0]->x == 0);
  //ASSERT_TRUE(gs.gradients[1]->x == 1);
  ASSERT_TRUE(gs.gradients_size == 2);

  gs.clean();


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
#ifndef USE_THREAD
  //ASSERT_TRUE(strcmp(gradient_structure::get()->fp->cmpdif_file_name, "cmpdiff.tmp") == 0);
#endif
  ASSERT_TRUE(gradient_structure::get() == &top);
  {
    gradient_structure nested(10000L, 10);
    ASSERT_TRUE(gradient_structure::get() == &nested);
#ifndef USE_THREAD
    //ASSERT_TRUE(strcmp(gradient_structure::get()->fp->cmpdif_file_name, "cmpdiff10.tmp") == 0);
#endif
  }
  ASSERT_TRUE(gradient_structure::get() == nullptr);
  gradient_structure::reset(&top);
  ASSERT_TRUE(gradient_structure::get() == &top);
}
TEST_F(test_gradient_structure_thread, nested_grad_stack)
{
  gradient_structure top;
#ifndef USE_THREAD
  /*
  ASSERT_TRUE(strcmp(gradient_structure::get()->GRAD_STACK1->gradfile_name, "gradfil1.tmp") == 0);
  ASSERT_TRUE(strcmp(gradient_structure::get()->GRAD_STACK1->gradfile_name1, "gradfil1.tmp") == 0);
  ASSERT_TRUE(strcmp(gradient_structure::get()->GRAD_STACK1->gradfile_name2, "gradfil2.tmp") == 0);
  ASSERT_TRUE(strcmp(gradient_structure::get()->GRAD_STACK1->var_store_file_name, "varssave.tmp") == 0);
  */
#endif

  ASSERT_TRUE(gradient_structure::get() == &top);
  {
    gradient_structure nested(10000L, 10);
    ASSERT_TRUE(gradient_structure::get() == &nested);
#ifndef USE_THREAD
    /*
    ASSERT_TRUE(strcmp(gradient_structure::get()->GRAD_STACK1->gradfile_name, "gradfil110.tmp") == 0);
    ASSERT_TRUE(strcmp(gradient_structure::get()->GRAD_STACK1->gradfile_name1, "gradfil110.tmp") == 0);
    ASSERT_TRUE(strcmp(gradient_structure::get()->GRAD_STACK1->gradfile_name2, "gradfil210.tmp") == 0);
    ASSERT_TRUE(strcmp(gradient_structure::get()->GRAD_STACK1->var_store_file_name, "varssave10.tmp") == 0);
    */
#endif
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
  }
  ASSERT_TRUE(gradient_structure::get() == nullptr);
}
TEST_F(test_gradient_structure_thread, multiple_fp)
{
  {
  gradient_structure a(100000L, 1);
  DF_FILE* afp = a.fp;
  gradient_structure b(100000L, 5);
  DF_FILE* bfp = b.fp;

  ASSERT_TRUE(a.x == 1);
  ASSERT_TRUE(b.x == 5);
  ASSERT_TRUE(afp != bfp);
  ASSERT_TRUE(afp->file_ptr != bfp->file_ptr);
  /*
  ASSERT_TRUE(strcmp(afp->cmpdif_file_name, "cmpdiff1.tmp") == 0);
  ASSERT_TRUE(strcmp(bfp->cmpdif_file_name, "cmpdiff5.tmp") == 0);
  */

  int expected_a_int = 5;
  double expected_a_double = 5.9;
  int expected_b_int = -2;
  double expected_b_double = -2.5;
  afp->fwrite(expected_a_int);
  bfp->fwrite(expected_b_int);
  afp->fwrite(expected_a_double);
  bfp->fwrite(expected_b_double);
  int read_a_int;
  double read_a_double;
  int read_b_int;
  double read_b_double;
  bfp->fread(read_b_double);
  bfp->fread(read_b_int);
  afp->fread(read_a_double);
  afp->fread(read_a_int);

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
  grad_stack* aGRAD_STACK1 = a.GRAD_STACK1;
  gradient_structure b(100000L, 5);
  grad_stack* bGRAD_STACK1 = b.GRAD_STACK1;

  ASSERT_TRUE(aGRAD_STACK1 != bGRAD_STACK1);

  /*
  ASSERT_TRUE(strcmp(aGRAD_STACK1->gradfile_name, "gradfil11.tmp") == 0);
  ASSERT_TRUE(strcmp(aGRAD_STACK1->gradfile_name1, "gradfil11.tmp") == 0);
  ASSERT_TRUE(strcmp(aGRAD_STACK1->gradfile_name2, "gradfil21.tmp") == 0);
  ASSERT_TRUE(strcmp(aGRAD_STACK1->var_store_file_name, "varssave1.tmp") == 0);
  ASSERT_TRUE(strcmp(bGRAD_STACK1->gradfile_name, "gradfil15.tmp") == 0);
  ASSERT_TRUE(strcmp(bGRAD_STACK1->gradfile_name1, "gradfil15.tmp") == 0);
  ASSERT_TRUE(strcmp(bGRAD_STACK1->gradfile_name2, "gradfil25.tmp") == 0);
  ASSERT_TRUE(strcmp(bGRAD_STACK1->var_store_file_name, "varssave5.tmp") == 0);
  */

  aGRAD_STACK1->set_gradient_stack(empty_a1);
  aGRAD_STACK1->set_gradient_stack(empty_a2);
  aGRAD_STACK1->set_gradient_stack(empty_a3);

  ASSERT_EQ(aGRAD_STACK1->total(), 3);
  ASSERT_EQ(bGRAD_STACK1->total(), 0);

  bGRAD_STACK1->set_gradient_stack(empty_b1);
  bGRAD_STACK1->set_gradient_stack(empty_b2);

  ASSERT_EQ(aGRAD_STACK1->total(), 3);
  ASSERT_EQ(bGRAD_STACK1->total(), 2);

  ASSERT_TRUE(gradient_structure::get() == &b);

  ASSERT_EQ(a.TOTAL_BYTES, 0);
  ASSERT_EQ(b.TOTAL_BYTES, 0);

  OFF_T abegin_lpos = LSEEK(aGRAD_STACK1->_GRADFILE_PTR, 0, SEEK_CUR);
  OFF_T bbegin_lpos = LSEEK(bGRAD_STACK1->_GRADFILE_PTR, 0, SEEK_CUR);

  ASSERT_EQ(abegin_lpos, 0);
  ASSERT_EQ(bbegin_lpos, 0);

  aGRAD_STACK1->write_grad_stack_buffer(&a);
  ASSERT_EQ(aGRAD_STACK1->total(), 0);
  ASSERT_EQ(bGRAD_STACK1->total(), 2);
  // 5000 because of grad_stack::set_gbuffer_pointers
  ASSERT_EQ(aGRAD_STACK1->length, 5000);
  size_t aexpected_total_bytes = aGRAD_STACK1->length * sizeof(grad_stack_entry);
  ASSERT_EQ(a.TOTAL_BYTES, aexpected_total_bytes);
  ASSERT_EQ(b.TOTAL_BYTES, 0);

  bGRAD_STACK1->write_grad_stack_buffer(&b);
  ASSERT_EQ(aGRAD_STACK1->total(), 0);
  ASSERT_EQ(bGRAD_STACK1->total(), 0);
  ASSERT_EQ(bGRAD_STACK1->length, 5000);
  size_t bexpected_total_bytes = bGRAD_STACK1->length * sizeof(grad_stack_entry);
  ASSERT_EQ(a.TOTAL_BYTES, aexpected_total_bytes);
  ASSERT_EQ(b.TOTAL_BYTES, bexpected_total_bytes);

  OFF_T aend_lpos = LSEEK(aGRAD_STACK1->_GRADFILE_PTR, 0, SEEK_CUR);
  OFF_T bend_lpos = LSEEK(bGRAD_STACK1->_GRADFILE_PTR, 0, SEEK_CUR);

  ASSERT_EQ(aend_lpos, aexpected_total_bytes);
  ASSERT_EQ(bend_lpos, bexpected_total_bytes);

  OFF_T reta = LSEEK(aGRAD_STACK1->_GRADFILE_PTR, -aend_lpos, SEEK_CUR);
  ASSERT_EQ(abegin_lpos, reta);
  aGRAD_STACK1->read_grad_stack_buffer(abegin_lpos);
  OFF_T retb = LSEEK(bGRAD_STACK1->_GRADFILE_PTR, -bend_lpos, SEEK_CUR);
  ASSERT_EQ(bbegin_lpos, retb);
  bGRAD_STACK1->read_grad_stack_buffer(bbegin_lpos);

  ASSERT_TRUE(aGRAD_STACK1->true_ptr_first[0].func == empty_a1);
  ASSERT_TRUE(aGRAD_STACK1->true_ptr_first[1].func == empty_a2);
  ASSERT_TRUE(aGRAD_STACK1->true_ptr_first[2].func == empty_a3);
  ASSERT_TRUE(bGRAD_STACK1->true_ptr_first[0].func == empty_b1);
  ASSERT_TRUE(bGRAD_STACK1->true_ptr_first[1].func == empty_b2);

  ASSERT_EQ(aGRAD_STACK1->total(), 4999);
  ASSERT_EQ(bGRAD_STACK1->total(), 4999);

  //Must manually reset ptr
  aGRAD_STACK1->ptr = aGRAD_STACK1->ptr_first + 3;
  bGRAD_STACK1->ptr = bGRAD_STACK1->ptr_first + 2;

  ASSERT_EQ(aGRAD_STACK1->total(), 3);
  ASSERT_EQ(bGRAD_STACK1->total(), 2);
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
TEST_F(test_gradient_structure_thread, multiple_save_var_file_flag)
{
  {
  gradient_structure a(100000L, 1);
  gradient_structure b(100000L, 5);

  ASSERT_EQ(a.save_var_file_flag, 0);
  ASSERT_EQ(b.save_var_file_flag, 0);

  a.save_var_file_flag = 1;

  ASSERT_EQ(a.save_var_file_flag, 1);
  ASSERT_EQ(b.save_var_file_flag, 0);

  a.save_var_file_flag = 0;
  b.save_var_file_flag = 1;

  ASSERT_EQ(a.save_var_file_flag, 0);
  ASSERT_EQ(b.save_var_file_flag, 1);
  }
}
TEST_F(test_gradient_structure_thread, multiple_save_arrays)
{
  {
  gradient_structure a(100000L, 1);
  gradient_structure b(100000L, 5);

  ASSERT_EQ(a.save_var_file_flag, 0);
  ASSERT_EQ(b.save_var_file_flag, 0);

  ASSERT_EQ(a.ARR_LIST1->get_last_offset(), 0);
  ASSERT_EQ(b.ARR_LIST1->get_last_offset(), 0);

  ASSERT_TRUE(a.ARR_LIST1->ARRAY_MEMBLOCK_SAVE == nullptr);
  ASSERT_TRUE(b.ARR_LIST1->ARRAY_MEMBLOCK_SAVE == nullptr);
  a.save_arrays();
  ASSERT_TRUE(a.ARR_LIST1->ARRAY_MEMBLOCK_SAVE != nullptr);
  ASSERT_TRUE(b.ARR_LIST1->ARRAY_MEMBLOCK_SAVE == nullptr);
  b.save_arrays();
  ASSERT_TRUE(a.ARR_LIST1->ARRAY_MEMBLOCK_SAVE != nullptr);
  ASSERT_TRUE(b.ARR_LIST1->ARRAY_MEMBLOCK_SAVE != nullptr);

  a.restore_arrays();
  ASSERT_TRUE(a.ARR_LIST1->ARRAY_MEMBLOCK_SAVE == nullptr);
  ASSERT_TRUE(b.ARR_LIST1->ARRAY_MEMBLOCK_SAVE != nullptr);
  b.restore_arrays();
  ASSERT_TRUE(a.ARR_LIST1->ARRAY_MEMBLOCK_SAVE == nullptr);
  ASSERT_TRUE(b.ARR_LIST1->ARRAY_MEMBLOCK_SAVE == nullptr);
  }
}
TEST_F(test_gradient_structure_thread, multiple_gradcalc)
{
  {
    gradient_structure a(100000L, 1);
    gradient_structure b(100000L, 5);

    gradient_structure::_instance = &a;
    {
      independent_variables independents(1, 2);
      independents(1) = 1;
      independents(2) = 1;
      dvar_vector variables(independents);

      ASSERT_EQ(a.NVAR, 2);
      ASSERT_EQ(b.NVAR, 0);

      dvariable f = 2 * variables(1) + 3 * variables(2);
      ASSERT_DOUBLE_EQ(value(f), 5);

      dvector g(1, 2);
      a.gradcalc(2, g);

      ASSERT_DOUBLE_EQ(g(1), 2);
      ASSERT_DOUBLE_EQ(g(2), 3);
    }
    gradient_structure::_instance = &b;
    {
      independent_variables independents(1, 4);
      independents(1) = -1;
      independents(2) = -1;
      independents(3) = -1;
      independents(4) = -1;
      dvar_vector variables(independents);

      ASSERT_EQ(a.NVAR, 2);
      ASSERT_EQ(b.NVAR, 4);

      dvariable f = 2 * variables(1) + 3 * variables(2) + 4 * variables(3) + 5 * variables(4);
      ASSERT_DOUBLE_EQ(value(f), -14);

      dvector g(1, 4);
      b.gradcalc(4, g);

      ASSERT_DOUBLE_EQ(g(1), 2);
      ASSERT_DOUBLE_EQ(g(2), 3);
      ASSERT_DOUBLE_EQ(g(3), 4);
      ASSERT_DOUBLE_EQ(g(4), 5);
    }
    gradient_structure::_instance = &b;
    {
      independent_variables independents(1, 2);
      independents(1) = 1;
      independents(2) = 1;
      dvar_vector variables(independents);

      ASSERT_EQ(a.NVAR, 2);
      ASSERT_EQ(b.NVAR, 2);

      dvariable f = 2 * variables(1) + 3 * variables(2);
      ASSERT_DOUBLE_EQ(value(f), 5);

      dvector g(1, 2);
      b.gradcalc(2, g);

      ASSERT_DOUBLE_EQ(g(1), 2);
      ASSERT_DOUBLE_EQ(g(2), 3);
    }
    gradient_structure::_instance = &a;
    {
      independent_variables independents(1, 4);
      independents(1) = -1;
      independents(2) = -1;
      independents(3) = -1;
      independents(4) = -1;
      dvar_vector variables(independents);

      ASSERT_EQ(a.NVAR, 4);
      ASSERT_EQ(b.NVAR, 2);

      dvariable f = 2 * variables(1) + 3 * variables(2) + 4 * variables(3) + 5 * variables(4);
      ASSERT_DOUBLE_EQ(value(f), -14);

      dvector g(1, 4);
      a.gradcalc(4, g);

      ASSERT_DOUBLE_EQ(g(1), 2);
      ASSERT_DOUBLE_EQ(g(2), 3);
      ASSERT_DOUBLE_EQ(g(3), 4);
      ASSERT_DOUBLE_EQ(g(4), 5);
    }
  }
}
