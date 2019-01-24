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
