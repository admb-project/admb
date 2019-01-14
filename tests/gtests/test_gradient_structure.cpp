#include <gtest/gtest.h>
#include <fvar.hpp>
#include <gradient_structure.h>

extern "C"
{
  void test_ad_exit(const int exit_code);
}

class test_gradient_structure: public ::testing::Test {};

TEST_F(test_gradient_structure, checktypes)
{
  ASSERT_EQ(sizeof(long long), sizeof(long long int));
}
TEST_F(test_gradient_structure, gradnew_not_in_scope)
{
  ad_exit=&test_ad_exit;
  double_and_int* gradnew();
  ASSERT_THROW(gradnew(), int);
}
TEST_F(test_gradient_structure, MAX_NVAR_OFFSET)
{
  gradient_structure gs;
  ASSERT_EQ(gradient_structure::get()->MAX_NVAR_OFFSET, 5000);
}
TEST_F(test_gradient_structure, gradnew_in_scope)
{
  ad_exit=&test_ad_exit;
  gradient_structure gs;
  ASSERT_EQ(gradient_structure::GRAD_LIST->total_addresses(), 1750);

  double_and_int* gradnew();
  double_and_int* ptr = gradnew();

  ASSERT_EQ(gradient_structure::GRAD_LIST->total_addresses(), 1751);
}
TEST_F(test_gradient_structure, array_memblock_size)
{
  ASSERT_TRUE(gradient_structure::get() == NULL);
  size_t size = 1000000 + sizeof(double_and_int) - 1;
  gradient_structure gs(size);
  ASSERT_EQ(sizeof(double_and_int), 8);
  ASSERT_EQ((1000000 % sizeof(double_and_int)), 0);
  ASSERT_EQ(gradient_structure::get()->ARRAY_MEMBLOCK_SIZE, 1000000);
}
TEST_F(test_gradient_structure, cmpdif_buffer_size)
{
  ASSERT_TRUE(gradient_structure::get() == NULL);
  gradient_structure gs;
  ASSERT_EQ(gradient_structure::get()->CMPDIF_BUFFER_SIZE, 140000000);
}
TEST_F(test_gradient_structure, gradstack_buffer_size)
{
  ASSERT_TRUE(gradient_structure::get() == NULL);
  gradient_structure gs;
  ASSERT_EQ(gradient_structure::get()->GRADSTACK_BUFFER_SIZE, 4000000);
}
TEST_F(test_gradient_structure, arr_new)
{
  ASSERT_TRUE(gradient_structure::get() == NULL);
  gradient_structure gs;

  ASSERT_TRUE(gradient_structure::get()->ARR_LIST1->get_last() == NULL);
  ASSERT_EQ(gradient_structure::get()->ARR_LIST1->get_number_arr_links(), 0);

  double_and_int* ptr = arr_new(100);

  ASSERT_TRUE(ptr != NULL);

  arr_link* arrlink = *(arr_link**)(ptr);

  ASSERT_EQ(gradient_structure::get()->ARR_LIST1->get_number_arr_links(), 1);
  ASSERT_TRUE(arrlink->get_prev() == NULL);
  ASSERT_TRUE(gradient_structure::get()->ARR_LIST1->get_last() == arrlink);
  ASSERT_EQ(arrlink->get_size(), 100 * sizeof(double_and_int));
  ASSERT_TRUE(arrlink->get_next() == NULL);
  ASSERT_EQ(arrlink->get_status(), 1);
  ASSERT_EQ(arrlink->get_offset(), 0);
  ASSERT_EQ(gradient_structure::get()->ARR_LIST1->get_last_offset(), 100 * sizeof(double_and_int));

  arr_free(ptr);

  ASSERT_EQ(gradient_structure::get()->ARR_LIST1->get_number_arr_links(), 0);
  ASSERT_TRUE(gradient_structure::get()->ARR_LIST1->get_last() == NULL);
  ASSERT_EQ(gradient_structure::get()->ARR_LIST1->get_last_offset(), 0);
}
TEST_F(test_gradient_structure, arr_new_max_plus_one)
{
  ad_exit=&test_ad_exit;

  ASSERT_TRUE(gradient_structure::get() == NULL);
  gradient_structure gs;

  size_t max_plus_one = (gradient_structure::get()->ARRAY_MEMBLOCK_SIZE / sizeof(double_and_int)) + 1;
  ASSERT_THROW(arr_new(max_plus_one), int);
}
TEST_F(test_gradient_structure, arr_new_2x)
{
  ASSERT_TRUE(gradient_structure::get() == NULL);
  gradient_structure gs;

  ASSERT_EQ(gradient_structure::get()->ARR_LIST1->get_number_arr_links(), 0);
  ASSERT_TRUE(gradient_structure::get()->ARR_LIST1->get_last() == NULL);
  ASSERT_TRUE(gradient_structure::get()->ARR_LIST1->get_free_last() == NULL);

  double_and_int* ptr = arr_new(100);
  ASSERT_TRUE(ptr != NULL);
  arr_link* arrlink = *(arr_link**)(ptr);

  ASSERT_EQ(gradient_structure::get()->ARR_LIST1->get_number_arr_links(), 1);
  ASSERT_TRUE(gradient_structure::get()->ARR_LIST1->get_last() == arrlink);
  ASSERT_TRUE(gradient_structure::get()->ARR_LIST1->get_free_last() == NULL);

  double_and_int* ptr2 = arr_new(20);
  ASSERT_TRUE(ptr2 != NULL);
  arr_link* arrlink2 = *(arr_link**)(ptr2);

  ASSERT_EQ(gradient_structure::get()->ARR_LIST1->get_number_arr_links(), 2);
  ASSERT_TRUE(arrlink->get_prev() == NULL);
  ASSERT_TRUE(arrlink2->get_prev() == arrlink);

  ASSERT_TRUE(gradient_structure::get()->ARR_LIST1->get_last() == arrlink2);
  ASSERT_EQ(arrlink->get_size(), 100 * sizeof(double_and_int));
  ASSERT_EQ(arrlink2->get_size(), 20 * sizeof(double_and_int));
  ASSERT_TRUE(arrlink->get_next() == arrlink2);
  ASSERT_TRUE(arrlink2->get_next() == NULL);
  ASSERT_EQ(arrlink->get_status(), 1);
  ASSERT_EQ(arrlink2->get_status(), 1);
  ASSERT_EQ(arrlink->get_offset(), 0);
  ASSERT_EQ(arrlink2->get_offset(), 100 * sizeof(double_and_int));
  ASSERT_EQ(gradient_structure::get()->ARR_LIST1->get_last_offset(), (100 + 20) * sizeof(double_and_int));

  arr_free(ptr);
  ASSERT_TRUE(gradient_structure::get()->ARR_LIST1->get_free_last() == arrlink);
  arr_free(ptr2);
  ASSERT_TRUE(gradient_structure::get()->ARR_LIST1->get_free_last() == NULL);

  ASSERT_TRUE(gradient_structure::get()->ARR_LIST1->get_last() == NULL);
  ASSERT_EQ(gradient_structure::get()->ARR_LIST1->get_number_arr_links(), 0);
  ASSERT_EQ(gradient_structure::get()->ARR_LIST1->get_last_offset(), 0);
}
TEST_F(test_gradient_structure, arr_new_readd_samesize)
{
  gradient_structure gs;

  double_and_int* ptr = arr_new(100);
  arr_link* arrlink = *(arr_link**)(ptr);

  double_and_int* ptr2 = arr_new(20);
  arr_link* arrlink2 = *(arr_link**)(ptr2);

  ASSERT_EQ(gradient_structure::get()->ARR_LIST1->get_number_arr_links(), 2);
  arr_free(ptr);
  ASSERT_EQ(gradient_structure::get()->ARR_LIST1->get_number_arr_links(), 2);

  constexpr size_t allowable = sizeof(double_and_int) * 10;

  ASSERT_EQ(arrlink->get_status(), 0);
  ASSERT_TRUE(gradient_structure::get()->ARR_LIST1->get_free_last() == arrlink);
  ASSERT_EQ(arrlink->get_size(), 100 * sizeof(double_and_int));
  ASSERT_TRUE(arrlink->get_size() >= 100 * sizeof(double_and_int));
  ASSERT_TRUE(arrlink->get_size() - 100 * sizeof(double_and_int) <= sizeof(double_and_int) * 10);
  ASSERT_TRUE(arrlink->get_size() - 100 * sizeof(double_and_int) <= sizeof(double_and_int) * 10);

  double_and_int* ptr3 = arr_new(100);
  arr_link* arrlink3 = *(arr_link**)(ptr);
  ASSERT_EQ(gradient_structure::get()->ARR_LIST1->get_number_arr_links(), 2);
  ASSERT_EQ(arrlink3->get_status(), 1);
  ASSERT_EQ(arrlink3->get_size(), 100 * sizeof(double_and_int));
  ASSERT_TRUE(arrlink3 == arrlink);

  arr_free(ptr3);
  ASSERT_EQ(gradient_structure::get()->ARR_LIST1->get_number_arr_links(), 2);
  arr_free(ptr2);
  ASSERT_EQ(gradient_structure::get()->ARR_LIST1->get_number_arr_links(), 0);
}
TEST_F(test_gradient_structure, arr_new_readd_almostsamesize)
{
  gradient_structure gs;

  double_and_int* ptr = arr_new(100);
  arr_link* arrlink = *(arr_link**)(ptr);

  double_and_int* ptr2 = arr_new(20);
  arr_link* arrlink2 = *(arr_link**)(ptr2);

  ASSERT_EQ(gradient_structure::get()->ARR_LIST1->get_number_arr_links(), 2);
  arr_free(ptr);
  ASSERT_EQ(gradient_structure::get()->ARR_LIST1->get_number_arr_links(), 2);

  constexpr size_t allowable = sizeof(double_and_int) * 10;

  ASSERT_EQ(arrlink->get_status(), 0);
  ASSERT_TRUE(gradient_structure::get()->ARR_LIST1->get_free_last() == arrlink);
  ASSERT_EQ(arrlink->get_size(), 100 * sizeof(double_and_int));
  ASSERT_TRUE(arrlink->get_size() >= 90 * sizeof(double_and_int));
  ASSERT_TRUE(arrlink->get_size() - 90 * sizeof(double_and_int) <= sizeof(double_and_int) * 10);
  ASSERT_TRUE(arrlink->get_size() - 90 * sizeof(double_and_int) <= sizeof(double_and_int) * 10);

  double_and_int* ptr3 = arr_new(90);
  arr_link* arrlink3 = *(arr_link**)(ptr);
  ASSERT_EQ(gradient_structure::get()->ARR_LIST1->get_number_arr_links(), 2);
  ASSERT_EQ(arrlink3->get_status(), 1);
  ASSERT_EQ(arrlink3->get_size(), 100 * sizeof(double_and_int));
  ASSERT_TRUE(arrlink3 == arrlink);

  arr_free(ptr3);
  ASSERT_EQ(gradient_structure::get()->ARR_LIST1->get_number_arr_links(), 2);
  arr_free(ptr2);
  ASSERT_EQ(gradient_structure::get()->ARR_LIST1->get_number_arr_links(), 0);
}
TEST_F(test_gradient_structure, arr_new_readd_smaller_than_allowable)
{
  gradient_structure gs;

  double_and_int* ptr = arr_new(100);
  arr_link* arrlink = *(arr_link**)(ptr);

  double_and_int* ptr2 = arr_new(20);
  arr_link* arrlink2 = *(arr_link**)(ptr2);

  ASSERT_EQ(gradient_structure::get()->ARR_LIST1->get_number_arr_links(), 2);
  arr_free(ptr);
  ASSERT_EQ(gradient_structure::get()->ARR_LIST1->get_number_arr_links(), 2);

  constexpr size_t allowable = sizeof(double_and_int) * 10;

  ASSERT_EQ(arrlink->get_status(), 0);
  ASSERT_TRUE(gradient_structure::get()->ARR_LIST1->get_free_last() == arrlink);
  ASSERT_EQ(arrlink->get_size(), 100 * sizeof(double_and_int));
  ASSERT_TRUE(arrlink->get_size() >= 100 * sizeof(double_and_int));
  ASSERT_TRUE(arrlink->get_size() - 100 * sizeof(double_and_int) <= allowable);
  ASSERT_FALSE(arrlink->get_size() - 1 * sizeof(double_and_int) <= allowable);

  double_and_int* ptr3 = arr_new(1);
  arr_link* arrlink3 = *(arr_link**)(ptr);
  ASSERT_EQ(gradient_structure::get()->ARR_LIST1->get_number_arr_links(), 3);
  ASSERT_EQ(arrlink3->get_status(), 1);
  ASSERT_EQ(arrlink3->get_size(), 1 * sizeof(double_and_int));
  ASSERT_FALSE(arrlink3 == arrlink);

  arr_free(ptr3);
  ASSERT_EQ(gradient_structure::get()->ARR_LIST1->get_number_arr_links(), 2);
  arr_free(ptr2);
  ASSERT_EQ(gradient_structure::get()->ARR_LIST1->get_number_arr_links(), 0);
}
TEST_F(test_gradient_structure, arr_new_readd_smallerby1)
{
  gradient_structure gs;

  double_and_int* ptr = arr_new(100);
  arr_link* arrlink = *(arr_link**)(ptr);

  double_and_int* ptr2 = arr_new(20);
  arr_link* arrlink2 = *(arr_link**)(ptr2);

  ASSERT_EQ(gradient_structure::get()->ARR_LIST1->get_number_arr_links(), 2);
  arr_free(ptr);
  ASSERT_EQ(gradient_structure::get()->ARR_LIST1->get_number_arr_links(), 2);

  ASSERT_EQ(arrlink->get_status(), 0);
  ASSERT_TRUE(gradient_structure::get()->ARR_LIST1->get_free_last() == arrlink);
  ASSERT_EQ(arrlink->get_size(), 100 * sizeof(double_and_int));
  ASSERT_TRUE(arrlink->get_size() >= 100 * sizeof(double_and_int));
  constexpr size_t allowable = sizeof(double_and_int) * 10;
  ASSERT_TRUE(arrlink->get_size() - 100 * sizeof(double_and_int) <= allowable);
  ASSERT_FALSE(arrlink->get_size() - 1 * sizeof(double_and_int) <= allowable);

  double_and_int* ptr3 = arr_new(1);
  arr_link* arrlink3 = *(arr_link**)(ptr);
  ASSERT_EQ(gradient_structure::get()->ARR_LIST1->get_number_arr_links(), 3);
  ASSERT_EQ(arrlink3->get_status(), 1);
  ASSERT_EQ(arrlink3->get_size(), 1 * sizeof(double_and_int));
  ASSERT_TRUE(arrlink3 != arrlink);

  arr_free(ptr3);
  ASSERT_EQ(gradient_structure::get()->ARR_LIST1->get_number_arr_links(), 2);
  arr_free(ptr2);
  ASSERT_EQ(gradient_structure::get()->ARR_LIST1->get_number_arr_links(), 0);
}
TEST_F(test_gradient_structure, default_constructor)
{
  ASSERT_EQ(gradient_structure::NUM_RETURN_ARRAYS, 25);
  ASSERT_EQ(gradient_structure::RETURN_ARRAYS_SIZE, 70);
  //ASSERT_EQ(gradient_structure::MAX_NVAR_OFFSET, 5000);
  ASSERT_EQ(gradient_structure::NUM_DEPENDENT_VARIABLES, 2000);
  ASSERT_TRUE(gradient_structure::get() == NULL);
  ASSERT_TRUE(gradient_structure::RETURN_ARRAYS == NULL);
  ASSERT_TRUE(gradient_structure::MIN_RETURN == NULL);
  ASSERT_TRUE(gradient_structure::MAX_RETURN == NULL);
  ASSERT_TRUE(gradient_structure::RETURN_PTR == NULL);
  ASSERT_TRUE(gradient_structure::RETURN_PTR_CONTAINER == NULL);
  //ASSERT_TRUE(gradient_structure::INDVAR_LIST == NULL);
  //ASSERT_TRUE(gradient_structure::GRAD_STACK1 == NULL);
  //ASSERT_TRUE(gradient_structure::get()->ARR_LIST1 == NULL);
  ASSERT_TRUE(gradient_structure::GRAD_LIST == NULL);
  ASSERT_TRUE(gradient_structure::fp == NULL);
  ASSERT_TRUE(gradient_structure::DEPVARS_INFO == NULL);
  ASSERT_TRUE(gradient_structure::ARRAY_MEMBLOCK_BASE == NULL);

  gradient_structure gs;

  ASSERT_EQ(sizeof(double_and_int), 8);
  ASSERT_EQ((1000000 % sizeof(double_and_int)), 0);
  ASSERT_EQ(gradient_structure::get()->ARRAY_MEMBLOCK_SIZE, 1000000);

  ASSERT_EQ(gradient_structure::GRAD_LIST->total_addresses(), 1750);
  ASSERT_EQ(gradient_structure::get()->MAX_NVAR_OFFSET, 5000);
  ASSERT_TRUE(gradient_structure::get()->INDVAR_LIST == NULL);

  /*
  ASSERT_EQ(gradient_structure::NUM_RETURN_ARRAYS, 25);
  ASSERT_EQ(gradient_structure::RETURN_ARRAYS_SIZE, 70);
  ASSERT_EQ(gradient_structure::NUM_DEPENDENT_VARIABLES, 2000);
  ASSERT_TRUE(gradient_structure::ARRAY_MEMBLOCK_BASE == NULL);
  ASSERT_TRUE(gradient_structure::DEPVARS_INFO != NULL);
  ASSERT_TRUE(gradient_structure::fp != NULL);
  ASSERT_TRUE(gradient_structure::GRAD_LIST != NULL);
  ASSERT_TRUE(gradient_structure::ARR_LIST1 != NULL);
  ASSERT_TRUE(gradient_structure::GRAD_STACK1 != NULL);
  ASSERT_TRUE(gradient_structure::RETURN_ARRAYS != NULL);
  for (unsigned int i = 0; i < gradient_structure::NUM_RETURN_ARRAYS; ++i)
  {
    ASSERT_TRUE(gradient_structure::RETURN_ARRAYS[i] != NULL);
  }
  ASSERT_EQ(gradient_structure::RETURN_ARRAYS_PTR, 0);
  ASSERT_TRUE(gradient_structure::MIN_RETURN == gradient_structure::RETURN_ARRAYS[0]);
  ASSERT_TRUE(gradient_structure::MAX_RETURN == (gradient_structure::MIN_RETURN + 69));
  ASSERT_TRUE(gradient_structure::MIN_RETURN == gradient_structure::RETURN_PTR);
  ASSERT_TRUE(gradient_structure::RETURN_PTR_CONTAINER != NULL);
  for (unsigned int i = 0; i < gradient_structure::NUM_RETURN_ARRAYS; ++i)
  {
    ASSERT_TRUE(gradient_structure::RETURN_PTR_CONTAINER[i] == 0);
  }
  */
}
TEST_F(test_gradient_structure, default_constructor2x)
{
  {
    gradient_structure gs;
  }
  {
    gradient_structure gs;
  }
}
/*
TEST_F(test_gradient_structure, default_constructorb2b)
{
  ad_exit = &test_ad_exit;

  ASSERT_ANY_THROW({
    gradient_structure gs;
    gradient_structure gs2;
  });
  gradient_structure gs;
}
*/
TEST_F(test_gradient_structure, grad_stack1_defaults)
{
  gradient_structure gs;
  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0); 
}
TEST_F(test_gradient_structure, make_indvar_list)
{
  ASSERT_TRUE(gradient_structure::get() == NULL);
  gradient_structure gs;
  ASSERT_EQ(gradient_structure::get()->MAX_NVAR_OFFSET, 5000);

  dvar_vector t(1, 5);
  ASSERT_TRUE(gradient_structure::get()->INDVAR_LIST == NULL);
  make_indvar_list(t);
  ASSERT_TRUE(gradient_structure::get()->INDVAR_LIST != NULL);

  ASSERT_EQ(gradient_structure::NVAR, 5);
  for (int i = 0; i < gradient_structure::NVAR; ++i)
  {
    ASSERT_TRUE(gradient_structure::get()->INDVAR_LIST->get_address(i) == &(t.va[i + 1].x));
  }
}
