#include <gtest/gtest.h>
#include <fvar.hpp>
#include <df1b2fun.h>
#include <adrndeff.h>

extern "C"
{
  void test_ad_exit(const int exit_code);
}

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
TEST_F(test_nested_calls_shape, trim_and_output)
{
  nested_calls_shape data;
  data.allocate(2, 3, 4);

  ASSERT_TRUE(data.get_ptr1() != nullptr);
  ASSERT_TRUE(data.get_ptr2() != nullptr);
  ASSERT_TRUE(data.get_ptr3() != nullptr);
  ASSERT_TRUE(data.get_ptr4() == nullptr);

  data.initialize();
  cout << data << endl;

  data.trim();
  ASSERT_TRUE(data.get_ptr1() == nullptr);
  ASSERT_TRUE(data.get_ptr2() == nullptr);
  ASSERT_TRUE(data.get_ptr3() == nullptr);
  ASSERT_TRUE(data.get_ptr4() == nullptr);

  cout << data << endl;
}
TEST_F(test_nested_calls_shape, nonzero_trim_and_output)
{
  nested_calls_shape data;
  data.allocate(2, 3, 4);

  ASSERT_TRUE(data.get_ptr1() != nullptr);
  ASSERT_TRUE(data.get_ptr2() != nullptr);
  ASSERT_TRUE(data.get_ptr3() != nullptr);
  ASSERT_TRUE(data.get_ptr4() == nullptr);

  ivector* ptr1 = data.get_ptr1();
  *ptr1 = 1;
  imatrix* ptr2 = data.get_ptr2();
  *ptr2 = 2;
  i3_array* ptr3 = data.get_ptr3();
  *ptr3 = 3;
  cout << data << endl;

  data.trim();
  ASSERT_TRUE(data.get_ptr1() != nullptr);
  ASSERT_TRUE(data.get_ptr2() != nullptr);
  ASSERT_TRUE(data.get_ptr3() == nullptr);
  ASSERT_TRUE(data.get_ptr4() == nullptr);

  cout << data << endl;
}
TEST_F(test_nested_calls_shape, nested_calls_indices)
{
  nested_calls_shape data;
  data.allocate(2, 2, 2);

  ivector* ptr1 = data.get_ptr1();
  *ptr1 = 2;
  imatrix* ptr2 = data.get_ptr2();
  *ptr2 = 2;
  i3_array* ptr3 = data.get_ptr3();
  *ptr3 = 2;

  nested_calls_indices indices;
  indices.allocate(data);

  ivector& level11 = indices.level1(1);  
  ASSERT_EQ(level11.indexmin(), 1);
  ASSERT_EQ(level11.indexmax(), 2);
  ivector& level12 = indices.level1(2);  
  ASSERT_EQ(level12.indexmin(), 1);
  ASSERT_EQ(level12.indexmax(), 2);
  ivector& level211 = indices.level2(1, 1);
  ASSERT_EQ(level211.indexmin(), 1);
  ASSERT_EQ(level211.indexmax(), 2);
  ivector& level212 = indices.level2(1, 2);
  ASSERT_EQ(level212.indexmin(), 1);
  ASSERT_EQ(level212.indexmax(), 2);
  ivector& level221 = indices.level2(2, 1);
  ASSERT_EQ(level221.indexmin(), 1);
  ASSERT_EQ(level221.indexmax(), 2);
  ivector& level222 = indices.level2(2, 2);
  ASSERT_EQ(level222.indexmin(), 1);
  ASSERT_EQ(level222.indexmax(), 2);
  ivector& level3111 = indices.level3(1, 1, 1);  
  ASSERT_EQ(level3111.indexmin(), 1);
  ASSERT_EQ(level3111.indexmax(), 2);
  ivector& level3112 = indices.level3(1, 1, 2);  
  ASSERT_EQ(level3112.indexmin(), 1);
  ASSERT_EQ(level3112.indexmax(), 2);
  ivector& level3121 = indices.level3(1, 2, 1);  
  ASSERT_EQ(level3121.indexmin(), 1);
  ASSERT_EQ(level3121.indexmax(), 2);
  ivector& level3122 = indices.level3(1, 2, 2);  
  ASSERT_EQ(level3122.indexmin(), 1);
  ASSERT_EQ(level3122.indexmax(), 2);
  ivector& level3211 = indices.level3(2, 1, 1);  
  ASSERT_EQ(level3211.indexmin(), 1);
  ASSERT_EQ(level3211.indexmax(), 2);
  ivector& level3212 = indices.level3(2, 1, 2);  
  ASSERT_EQ(level3212.indexmin(), 1);
  ASSERT_EQ(level3212.indexmax(), 2);
  ivector& level3221 = indices.level3(2, 2, 1);  
  ivector& level3222 = indices.level3(2, 2, 2);  
  ASSERT_EQ(level3222.indexmin(), 1);
  ASSERT_EQ(level3222.indexmax(), 2);
}
TEST_F(test_nested_calls_shape, allocate_nsc)
{
  ad_exit=&test_ad_exit;

  nested_calls_indices indices;

  nested_calls_shape data;
  data.allocate(2, 2, 2);
  ivector* ptr1 = data.get_ptr1();
  *ptr1 = 2;
  imatrix* ptr2 = data.get_ptr2();
  *ptr2 = 2;
  i3_array* ptr3 = data.get_ptr3();
  *ptr3 = 2;
  indices.allocate(data);
  ASSERT_EQ(indices.level1(1).indexmin(), 1);
  ASSERT_EQ(indices.level1(1).indexmax(), 2);

  nested_calls_shape data2;
  data2.allocate(1, 1, 1);

  ivector* nptr1 = data2.get_ptr1();
  *nptr1 = 1;
  imatrix* nptr2 = data2.get_ptr2();
  *nptr2 = 1;
  i3_array* nptr3 = data2.get_ptr3();
  *nptr3 = 1;

  indices.allocate(data2);

  ASSERT_TRUE(nptr1 != ptr1);
  ASSERT_TRUE(nptr2 != ptr2);
  ASSERT_TRUE(nptr3 != ptr3);
  ASSERT_EQ(indices.level1(1).indexmin(), 1);
  ASSERT_EQ(indices.level1(1).indexmax(), 1);
}
