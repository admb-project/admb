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
