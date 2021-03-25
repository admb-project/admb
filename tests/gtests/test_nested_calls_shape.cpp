#include <gtest/gtest.h>
#include <fvar.hpp>
#include <df1b2fun.h>
#include <adrndeff.h>

class test_nested_calls_shape: public ::testing::Test {};

TEST_F(test_nested_calls_shape, default_constructor)
{
  nested_calls_shape data;
  ASSERT_TRUE(data.get_ptr1() == nullptr);
  ASSERT_TRUE(data.get_ptr2() == nullptr);
  ASSERT_TRUE(data.get_ptr3() == nullptr);
  ASSERT_TRUE(data.get_ptr4() == nullptr);
}
TEST_F(test_nested_calls_shape, allocate1)
{
  nested_calls_shape data;

  ASSERT_TRUE(data.get_ptr1() == nullptr);
  data.allocate(2);
  ASSERT_TRUE(data.get_ptr1() != nullptr);
  ASSERT_TRUE(data.get_ptr2() == nullptr);
  ASSERT_TRUE(data.get_ptr3() == nullptr);
  ASSERT_TRUE(data.get_ptr4() == nullptr);

  ivector* ptr1 = data.get_ptr1();

  ASSERT_EQ(ptr1->indexmin(), 1);
  ASSERT_EQ(ptr1->indexmax(), 2);

  data.allocate(2);
  ASSERT_TRUE(data.get_ptr1() != nullptr);
  ASSERT_TRUE(data.get_ptr2() == nullptr);
  ASSERT_TRUE(data.get_ptr3() == nullptr);
  ASSERT_TRUE(data.get_ptr4() == nullptr);

  ptr1 = data.get_ptr1();

  ASSERT_EQ(ptr1->indexmin(), 1);
  ASSERT_EQ(ptr1->indexmax(), 2);
}
TEST_F(test_nested_calls_shape, allocate2)
{
  nested_calls_shape data;

  ASSERT_TRUE(data.get_ptr1() == nullptr);
  ASSERT_TRUE(data.get_ptr2() == nullptr);
  data.allocate(2, 3);
  ASSERT_TRUE(data.get_ptr1() != nullptr);
  ASSERT_TRUE(data.get_ptr2() != nullptr);
  ASSERT_TRUE(data.get_ptr3() == nullptr);
  ASSERT_TRUE(data.get_ptr4() == nullptr);

  ivector* ptr1 = data.get_ptr1();

  ASSERT_EQ(ptr1->indexmin(), 1);
  ASSERT_EQ(ptr1->indexmax(), 2);

  imatrix* ptr2 = data.get_ptr2();
  ASSERT_EQ(ptr2->rowmin(), 1);
  ASSERT_EQ(ptr2->rowmax(), 2);
  ASSERT_EQ((*ptr2)(1).indexmin(), 1);
  ASSERT_EQ((*ptr2)(1).indexmax(), 3);
  ASSERT_EQ((*ptr2)(2).indexmin(), 1);
  ASSERT_EQ((*ptr2)(2).indexmax(), 3);

  data.allocate(2, 3);
  ASSERT_TRUE(data.get_ptr1() != nullptr);
  ASSERT_TRUE(data.get_ptr2() != nullptr);
  ASSERT_TRUE(data.get_ptr3() == nullptr);
  ASSERT_TRUE(data.get_ptr4() == nullptr);

  ptr1 = data.get_ptr1();

  ASSERT_EQ(ptr1->indexmin(), 1);
  ASSERT_EQ(ptr1->indexmax(), 2);

  ptr2 = data.get_ptr2();
  ASSERT_EQ(ptr2->rowmin(), 1);
  ASSERT_EQ(ptr2->rowmax(), 2);
  ASSERT_EQ((*ptr2)(1).indexmin(), 1);
  ASSERT_EQ((*ptr2)(1).indexmax(), 3);
  ASSERT_EQ((*ptr2)(2).indexmin(), 1);
  ASSERT_EQ((*ptr2)(2).indexmax(), 3);
}
TEST_F(test_nested_calls_shape, allocate3)
{
  nested_calls_shape data;

  ASSERT_TRUE(data.get_ptr1() == nullptr);
  ASSERT_TRUE(data.get_ptr2() == nullptr);
  data.allocate(2, 3, 4);
  ASSERT_TRUE(data.get_ptr1() != nullptr);
  ASSERT_TRUE(data.get_ptr2() != nullptr);
  ASSERT_TRUE(data.get_ptr3() != nullptr);
  ASSERT_TRUE(data.get_ptr4() == nullptr);

  ivector* ptr1 = data.get_ptr1();

  ASSERT_EQ(ptr1->indexmin(), 1);
  ASSERT_EQ(ptr1->indexmax(), 2);

  imatrix* ptr2 = data.get_ptr2();
  ASSERT_EQ(ptr2->rowmin(), 1);
  ASSERT_EQ(ptr2->rowmax(), 2);
  ASSERT_EQ((*ptr2)(1).indexmin(), 1);
  ASSERT_EQ((*ptr2)(1).indexmax(), 3);
  ASSERT_EQ((*ptr2)(2).indexmin(), 1);
  ASSERT_EQ((*ptr2)(2).indexmax(), 3);

  i3_array* ptr3 = data.get_ptr3();
  ASSERT_EQ(ptr3->rowmin(), 1);
  ASSERT_EQ(ptr3->rowmax(), 3);
  ASSERT_EQ((*ptr3)(1).rowmin(), 1);
  ASSERT_EQ((*ptr3)(1).rowmax(), 3);
  ASSERT_EQ((*ptr3)(2).rowmin(), 1);
  ASSERT_EQ((*ptr3)(2).rowmax(), 3);
  ASSERT_EQ((*ptr3)(1, 1).indexmin(), 1);
  ASSERT_EQ((*ptr3)(1, 1).indexmax(), 4);
  ASSERT_EQ((*ptr3)(2, 1).indexmin(), 1);
  ASSERT_EQ((*ptr3)(2, 1).indexmax(), 4);
  ASSERT_EQ((*ptr3)(1, 2).indexmin(), 1);
  ASSERT_EQ((*ptr3)(1, 2).indexmax(), 4);
  ASSERT_EQ((*ptr3)(2, 2).indexmin(), 1);
  ASSERT_EQ((*ptr3)(2, 2).indexmax(), 4);
  ASSERT_EQ((*ptr3)(1, 3).indexmin(), 1);
  ASSERT_EQ((*ptr3)(1, 3).indexmax(), 4);
  ASSERT_EQ((*ptr3)(2, 3).indexmin(), 1);
  ASSERT_EQ((*ptr3)(2, 3).indexmax(), 4);

  data.allocate(2, 3, 4);
  ASSERT_TRUE(data.get_ptr1() != nullptr);
  ASSERT_TRUE(data.get_ptr2() != nullptr);
  ASSERT_TRUE(data.get_ptr3() != nullptr);
  ASSERT_TRUE(data.get_ptr4() == nullptr);

  ptr1 = data.get_ptr1();

  ASSERT_EQ(ptr1->indexmin(), 1);
  ASSERT_EQ(ptr1->indexmax(), 2);

  ptr2 = data.get_ptr2();
  ASSERT_EQ(ptr2->rowmin(), 1);
  ASSERT_EQ(ptr2->rowmax(), 2);
  ASSERT_EQ((*ptr2)(1).indexmin(), 1);
  ASSERT_EQ((*ptr2)(1).indexmax(), 3);
  ASSERT_EQ((*ptr2)(2).indexmin(), 1);
  ASSERT_EQ((*ptr2)(2).indexmax(), 3);

  ptr3 = data.get_ptr3();
  ASSERT_EQ(ptr3->rowmin(), 1);
  ASSERT_EQ(ptr3->rowmax(), 3);
  ASSERT_EQ((*ptr3)(1).rowmin(), 1);
  ASSERT_EQ((*ptr3)(1).rowmax(), 3);
  ASSERT_EQ((*ptr3)(2).rowmin(), 1);
  ASSERT_EQ((*ptr3)(2).rowmax(), 3);
  ASSERT_EQ((*ptr3)(1, 1).indexmin(), 1);
  ASSERT_EQ((*ptr3)(1, 1).indexmax(), 4);
  ASSERT_EQ((*ptr3)(2, 1).indexmin(), 1);
  ASSERT_EQ((*ptr3)(2, 1).indexmax(), 4);
  ASSERT_EQ((*ptr3)(1, 2).indexmin(), 1);
  ASSERT_EQ((*ptr3)(1, 2).indexmax(), 4);
  ASSERT_EQ((*ptr3)(2, 2).indexmin(), 1);
  ASSERT_EQ((*ptr3)(2, 2).indexmax(), 4);
  ASSERT_EQ((*ptr3)(1, 3).indexmin(), 1);
  ASSERT_EQ((*ptr3)(1, 3).indexmax(), 4);
  ASSERT_EQ((*ptr3)(2, 3).indexmin(), 1);
  ASSERT_EQ((*ptr3)(2, 3).indexmax(), 4);
}
