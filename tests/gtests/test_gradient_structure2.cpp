#include <gtest/gtest.h>
#include <fvar.hpp>

extern "C"
{
  void test_ad_exit(const int exit_code);
}

class test_gradient_structure2: public ::testing::Test {};

TEST_F(test_gradient_structure2, RETURN_ARRAYS_PTR)
{
  ASSERT_TRUE(gradient_structure::get() == NULL);
  ASSERT_EQ(gradient_structure::NUM_RETURN_ARRAYS, 25);
  ASSERT_EQ(gradient_structure::RETURN_ARRAYS_SIZE, 70);

  gradient_structure gs;

  for (int i = 0; i < gradient_structure::NUM_RETURN_ARRAYS; ++i)
  {
    ASSERT_TRUE(gradient_structure::get()->RETURN_PTR_CONTAINER[i] == NULL);
  }

  ASSERT_TRUE(gradient_structure::get() != NULL);

  ASSERT_EQ(gradient_structure::get()->RETURN_ARRAYS_PTR, 0);
}
TEST_F(test_gradient_structure2, RETURN_ARRAYS_INCREMENT_DECREMENT)
{
  gradient_structure gs;

  dvariable* RETURN_PTR = gradient_structure::get()->RETURN_PTR;

  RETURN_ARRAYS_INCREMENT();

  ASSERT_EQ(gradient_structure::get()->RETURN_ARRAYS_PTR, 1);
  ASSERT_TRUE(gradient_structure::get()->RETURN_PTR_CONTAINER[0]  == RETURN_PTR);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == gradient_structure::get()->RETURN_ARRAYS[1]);
  ASSERT_TRUE(gradient_structure::get()->MAX_RETURN == gradient_structure::get()->RETURN_ARRAYS[1] + 69);
  ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == gradient_structure::get()->MIN_RETURN);

  RETURN_ARRAYS_DECREMENT();

  ASSERT_EQ(gradient_structure::get()->RETURN_ARRAYS_PTR, 0);

  ASSERT_TRUE(gradient_structure::get()->RETURN_PTR_CONTAINER[0]  == RETURN_PTR);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == gradient_structure::get()->RETURN_ARRAYS[0]);
  ASSERT_TRUE(gradient_structure::get()->MAX_RETURN == gradient_structure::get()->RETURN_ARRAYS[0] + 69);
  ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == gradient_structure::get()->RETURN_PTR_CONTAINER[0]);
}
TEST_F(test_gradient_structure2, RETURN_ARRAYS_INCREMENT_overflow)
{
  gradient_structure gs;

  for (int i = 1; i < gradient_structure::NUM_RETURN_ARRAYS; ++i)
  {
    RETURN_ARRAYS_INCREMENT();
  }

  ad_exit=&test_ad_exit;
  ASSERT_THROW(RETURN_ARRAYS_INCREMENT(), int);
}
TEST_F(test_gradient_structure2, RETURN_ARRAYS_DECREMENT_error)
{
  gradient_structure gs;

  ad_exit=&test_ad_exit;

  ASSERT_THROW(RETURN_ARRAYS_DECREMENT(), int);
}
TEST_F(test_gradient_structure2, ARRAY_MEMBLOCK_BASE_save_arrays)
{
  ASSERT_TRUE(gradient_structure::get() == NULL);
  {
    ASSERT_EQ(gradient_structure::NUM_DEPENDENT_VARIABLES, 2000);

    gradient_structure gs;

    ASSERT_EQ(gradient_structure::get()->save_var_file_flag, 0);
    ASSERT_EQ(gradient_structure::get()->ARRAY_MEMBLOCK_SIZE, 1000000);
    ASSERT_EQ(gradient_structure::get()->ARRAY_MEMBLOCK_BASE.adjustment, 0);
    ASSERT_TRUE(gradient_structure::get()->ARRAY_MEMBLOCK_BASE != NULL);
    ASSERT_TRUE(gradient_structure::get()->ARRAY_MEMBLOCK_SAVE == NULL);
  }
  ASSERT_TRUE(gradient_structure::get() == NULL);
}
TEST_F(test_gradient_structure2, ARRAY_MEMBLOCK_BASE_save_restore)
{
  gradient_structure gs;

  double_and_int* v[10];

  double value = 0;
  for (unsigned int i = 0; i < 10; ++i)
  {
    v[i] = arr_new(i + 1);
    for (unsigned int j = 0; j < i + 1; ++j)
    {
      v[i][j].x = value;
      value += 0.5;
    }
  }
  ASSERT_TRUE(gradient_structure::get()->ARRAY_MEMBLOCK_SAVE == NULL);
  gradient_structure::save_arrays();
  ASSERT_TRUE(gradient_structure::get()->ARRAY_MEMBLOCK_SAVE != NULL);
  value = 0;
  for (unsigned int i = 0; i < 10; ++i)
  {
    for (unsigned int j = 0; j < i + 1; ++j)
    {
      v[i][j].x = value;
    }
  }
  ASSERT_TRUE(gradient_structure::get()->ARRAY_MEMBLOCK_SAVE != NULL);
  gradient_structure::restore_arrays();
  ASSERT_TRUE(gradient_structure::get()->ARRAY_MEMBLOCK_SAVE == NULL);
  for (unsigned int i = 0; i < 10; ++i)
  {
    for (unsigned int j = 0; j < i + 1; ++j)
    {
      ASSERT_DOUBLE_EQ(v[i][j].x, value);
      value += 0.5;
    }
  }
}
TEST_F(test_gradient_structure2, TOTAL_BYTES)
{
  ASSERT_TRUE(gradient_structure::get() == NULL);
  {
    ASSERT_EQ(gradient_structure::TOTAL_BYTES, 0);
    ASSERT_EQ(gradient_structure::PREVIOUS_TOTAL_BYTES, 0);

    gradient_structure gs;

    ASSERT_EQ(gradient_structure::TOTAL_BYTES, 0);
    ASSERT_EQ(gradient_structure::PREVIOUS_TOTAL_BYTES, 0);
  }
  ASSERT_TRUE(gradient_structure::get() == NULL);
}
TEST_F(test_gradient_structure2, TOTAL_BYTES_write_read_grad_stack_buffer)
{
  ASSERT_TRUE(gradient_structure::get() == NULL);
  {
    ASSERT_EQ(gradient_structure::TOTAL_BYTES, 0);

    gradient_structure gs;

    //ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
    //gradient_structure::get()->GRAD_STACK1->write_grad_stack_buffer();

    dvariable x;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
    x = 1;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 1);

    gradient_structure::get()->GRAD_STACK1->write_grad_stack_buffer();

    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
    //ASSERT_EQ(gradient_structure::TOTAL_BYTES, sizeof(grad_stack_entry));
    ASSERT_EQ(gradient_structure::TOTAL_BYTES, sizeof(grad_stack_entry) * gradient_structure::get()->GRAD_STACK1->length);

    OFF_T endpos = LSEEK(gradient_structure::get()->GRAD_STACK1->_GRADFILE_PTR, 0, SEEK_END);
    ASSERT_EQ(endpos, sizeof(grad_stack_entry) * gradient_structure::get()->GRAD_STACK1->length);

    OFF_T offset = (OFF_T)(sizeof(grad_stack_entry) * gradient_structure::get()->GRAD_STACK1->length);
    OFF_T lpos=LSEEK(gradient_structure::get()->GRAD_STACK1->_GRADFILE_PTR, -offset, SEEK_CUR);
    ASSERT_EQ(lpos, 0);

    gradient_structure::get()->GRAD_STACK1->read_grad_stack_buffer(lpos);
    ASSERT_EQ(lpos, 0);
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), gradient_structure::get()->GRAD_STACK1->length - 1);
    size_t count = 0;
    for (grad_stack_entry* p = gradient_structure::get()->GRAD_STACK1->ptr_first; p <= gradient_structure::get()->GRAD_STACK1->ptr; ++p)
    {
      if (p->func != NULL) ++count;
    }
    ASSERT_EQ(count, 1);
  }
  ASSERT_TRUE(gradient_structure::get() == NULL);
}
