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
  ASSERT_EQ(gradient_structure::get()->MAX_NVAR_OFFSET, 15000);
}
TEST_F(test_gradient_structure, gradnew_in_scope)
{
  ad_exit=&test_ad_exit;
  gradient_structure gs;
  ASSERT_EQ(gradient_structure::get()->GRAD_LIST->total_addresses(), 1750);

  double_and_int* gradnew();
  double_and_int* ptr = gradnew();

  ASSERT_EQ(gradient_structure::get()->GRAD_LIST->total_addresses(), 1751);
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
  //ASSERT_TRUE(gradient_structure::MIN_RETURN == NULL);
  //ASSERT_TRUE(gradient_structure::MAX_RETURN == NULL);
  //ASSERT_TRUE(gradient_structure::RETURN_PTR == NULL);
  ASSERT_TRUE(gradient_structure::RETURN_PTR_CONTAINER == NULL);
  //ASSERT_TRUE(gradient_structure::INDVAR_LIST == NULL);
  //ASSERT_TRUE(gradient_structure::GRAD_STACK1 == NULL);
  //ASSERT_TRUE(gradient_structure::get()->ARR_LIST1 == NULL);
  //ASSERT_TRUE(gradient_structure::get()->GRAD_LIST == NULL);
  //ASSERT_TRUE(gradient_structure::fp == NULL);
  ASSERT_TRUE(gradient_structure::DEPVARS_INFO == NULL);
  ASSERT_TRUE(gradient_structure::ARRAY_MEMBLOCK_BASE == NULL);

  gradient_structure gs;

  ASSERT_EQ(sizeof(double_and_int), 8);
  ASSERT_EQ((1000000 % sizeof(double_and_int)), 0);
  ASSERT_EQ(gradient_structure::get()->ARRAY_MEMBLOCK_SIZE, 1000000);

  ASSERT_EQ(gradient_structure::get()->GRAD_LIST->total_addresses(), 1750);
  ASSERT_EQ(gradient_structure::get()->MAX_NVAR_OFFSET, 15000);
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
  ASSERT_EQ(gradient_structure::get()->MAX_NVAR_OFFSET, 15000);

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
TEST_F(test_gradient_structure, return_arrays)
{
  gradient_structure gs;
  ASSERT_EQ(gradient_structure::get()->NUM_RETURN_ARRAYS, 25);
  ASSERT_EQ(gradient_structure::get()->RETURN_ARRAYS_SIZE, 70);
  ASSERT_EQ(gradient_structure::get()->RETURN_ARRAYS_PTR, 0);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
  ASSERT_TRUE(gradient_structure::get()->MAX_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][69]);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == gradient_structure::get()->RETURN_PTR);
}
TEST_F(test_gradient_structure, return_arrays_sqr)
{
  gradient_structure gs;

  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  dvariable v;
  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  ASSERT_EQ(gradient_structure::get()->RETURN_ARRAYS_PTR, 0);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
  ASSERT_TRUE(gradient_structure::get()->MAX_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][69]);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == gradient_structure::get()->RETURN_PTR);

  int count = 0;
  for (int i = 1; i <= gradient_structure::get()->RETURN_ARRAYS_SIZE; ++i)
  {
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    v = i;
    ++count;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    grad_stack_entry* ptr = gradient_structure::get()->GRAD_STACK1->ptr;
    dvariable result = sqr(v);
    ASSERT_TRUE(ptr->func == default_evaluation);
    dvariable* return_ptr = gradient_structure::get()->RETURN_PTR;
    ASSERT_TRUE(ptr->dep_addr == &(return_ptr->v->x));
    ASSERT_TRUE(ptr->ind_addr1 == &(v.v->x));
    ASSERT_DOUBLE_EQ(ptr->mult1, 2.0 * i);
    ASSERT_TRUE(ptr->ind_addr2 == NULL);
    ASSERT_DOUBLE_EQ(ptr->mult2, 0.0);
    count += 2;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    ASSERT_DOUBLE_EQ(value(result), std::pow(i, 2.0));
    if (i == 70)
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
    else
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][i]);
  }
}
TEST_F(test_gradient_structure, sqrt_zero)
{
  ad_exit=&test_ad_exit;
  gradient_structure gs;

  dvariable v;
  v = 0;
  ASSERT_THROW(sqrt(v), int);
}
TEST_F(test_gradient_structure, return_arrays_sqrt)
{
  gradient_structure gs;

  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  dvariable v;
  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  ASSERT_EQ(gradient_structure::get()->RETURN_ARRAYS_PTR, 0);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
  ASSERT_TRUE(gradient_structure::get()->MAX_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][69]);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == gradient_structure::get()->RETURN_PTR);

  int count = 0;
  for (int i = 1; i <= gradient_structure::get()->RETURN_ARRAYS_SIZE; ++i)
  {
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    v = i;
    ++count;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    grad_stack_entry* ptr = gradient_structure::get()->GRAD_STACK1->ptr;
    dvariable result = sqrt(v);
    ASSERT_TRUE(ptr->func == default_evaluation);
    dvariable* return_ptr = gradient_structure::get()->RETURN_PTR;
    ASSERT_TRUE(ptr->dep_addr == &(return_ptr->v->x));
    ASSERT_TRUE(ptr->ind_addr1 == &(v.v->x));
    ASSERT_DOUBLE_EQ(ptr->mult1, 1.0 / (2.0 * std::sqrt(static_cast<double>(i))));
    ASSERT_TRUE(ptr->ind_addr2 == NULL);
    ASSERT_DOUBLE_EQ(ptr->mult2, 0.0);
    count += 2;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    ASSERT_DOUBLE_EQ(value(result), std::sqrt(static_cast<double>(i)));
    if (i == 70)
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
    else
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][i]);
  }
}
TEST_F(test_gradient_structure, return_arrays_prevariable_plus_prevariable)
{
  gradient_structure gs;

  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  dvariable v1;
  dvariable v2;
  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  ASSERT_EQ(gradient_structure::get()->RETURN_ARRAYS_PTR, 0);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
  ASSERT_TRUE(gradient_structure::get()->MAX_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][69]);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == gradient_structure::get()->RETURN_PTR);

  int count = 0;
  for (int i = 1; i <= gradient_structure::get()->RETURN_ARRAYS_SIZE; ++i)
  {
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    v1 = i * 2;
    v2 = i;
    count += 2;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    grad_stack_entry* ptr = gradient_structure::get()->GRAD_STACK1->ptr;
    dvariable result = v1 + v2;
    ASSERT_TRUE(ptr->func == default_evaluation4);
    dvariable* return_ptr = gradient_structure::get()->RETURN_PTR;
    ASSERT_TRUE(ptr->dep_addr == &(return_ptr->v->x));
    ASSERT_TRUE(ptr->ind_addr1 == &(v1.v->x));
    ASSERT_DOUBLE_EQ(ptr->mult1, 0.0);
    ASSERT_TRUE(ptr->ind_addr2 == &(v2.v->x));
    ASSERT_DOUBLE_EQ(ptr->mult2, 0.0);
    count += 2;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    ASSERT_DOUBLE_EQ(value(result), static_cast<double>(i * 2) + static_cast<double>(i));
    if (i == 70)
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
    else
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][i]);
  }
}
TEST_F(test_gradient_structure, return_arrays_prevariable_times_prevariable)
{
  gradient_structure gs;

  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  dvariable v1;
  dvariable v2;
  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  ASSERT_EQ(gradient_structure::get()->RETURN_ARRAYS_PTR, 0);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
  ASSERT_TRUE(gradient_structure::get()->MAX_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][69]);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == gradient_structure::get()->RETURN_PTR);

  int count = 0;
  for (int i = 1; i <= gradient_structure::get()->RETURN_ARRAYS_SIZE; ++i)
  {
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    v1 = i * 2;
    v2 = i;
    count += 2;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    grad_stack_entry* ptr = gradient_structure::get()->GRAD_STACK1->ptr;
    dvariable result = v1 * v2;
    ASSERT_TRUE(ptr->func == default_evaluation3);
    dvariable* return_ptr = gradient_structure::get()->RETURN_PTR;
    ASSERT_TRUE(ptr->dep_addr == &(return_ptr->v->x));
    ASSERT_TRUE(ptr->ind_addr1 == &(v1.v->x));
    ASSERT_DOUBLE_EQ(ptr->mult1, v2.v->x);
    ASSERT_TRUE(ptr->ind_addr2 == &(v2.v->x));
    ASSERT_DOUBLE_EQ(ptr->mult2, v1.v->x);
    count += 2;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    ASSERT_DOUBLE_EQ(value(result), static_cast<double>(i * 2 * i));
    if (i == 70)
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
    else
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][i]);
  }
}
TEST_F(test_gradient_structure, return_arrays_double_plus_prevariable)
{
  gradient_structure gs;

  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  dvariable v2;
  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  ASSERT_EQ(gradient_structure::get()->RETURN_ARRAYS_PTR, 0);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
  ASSERT_TRUE(gradient_structure::get()->MAX_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][69]);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == gradient_structure::get()->RETURN_PTR);

  int count = 0;
  for (int i = 1; i <= gradient_structure::get()->RETURN_ARRAYS_SIZE; ++i)
  {
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    double v1 = i * 2;
    v2 = i;
    count += 1;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    grad_stack_entry* ptr = gradient_structure::get()->GRAD_STACK1->ptr;
    dvariable result = v1 + v2;
    ASSERT_TRUE(ptr->func == default_evaluation1);
    dvariable* return_ptr = gradient_structure::get()->RETURN_PTR;
    ASSERT_TRUE(ptr->dep_addr == &(return_ptr->v->x));
    ASSERT_TRUE(ptr->ind_addr1 == &(v2.v->x));
    ASSERT_DOUBLE_EQ(ptr->mult1, 0.0);
    ASSERT_TRUE(ptr->ind_addr2 == NULL);
    ASSERT_DOUBLE_EQ(ptr->mult2, 0.0);
    count += 2;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    ASSERT_DOUBLE_EQ(value(result), static_cast<double>(i * 2 + i));
    if (i == 70)
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
    else
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][i]);
  }
}
TEST_F(test_gradient_structure, return_arrays_prevariable_plus_double)
{
  gradient_structure gs;

  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  dvariable v1;
  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  ASSERT_EQ(gradient_structure::get()->RETURN_ARRAYS_PTR, 0);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
  ASSERT_TRUE(gradient_structure::get()->MAX_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][69]);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == gradient_structure::get()->RETURN_PTR);

  int count = 0;
  for (int i = 1; i <= gradient_structure::get()->RETURN_ARRAYS_SIZE; ++i)
  {
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    double v2 = i * 2;
    v1 = i;
    count += 1;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    grad_stack_entry* ptr = gradient_structure::get()->GRAD_STACK1->ptr;
    dvariable result = v1 + v2;
    ASSERT_TRUE(ptr->func == default_evaluation1);
    dvariable* return_ptr = gradient_structure::get()->RETURN_PTR;
    ASSERT_TRUE(ptr->dep_addr == &(return_ptr->v->x));
    ASSERT_TRUE(ptr->ind_addr1 == &(v1.v->x));
    ASSERT_DOUBLE_EQ(ptr->mult1, 0.0);
    ASSERT_TRUE(ptr->ind_addr2 == NULL);
    ASSERT_DOUBLE_EQ(ptr->mult2, 0.0);
    count += 2;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    ASSERT_DOUBLE_EQ(value(result), static_cast<double>(i * 2 + i));
    if (i == 70)
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
    else
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][i]);
  }
}
TEST_F(test_gradient_structure, return_arrays_prevariable_minus_prevariable)
{
  gradient_structure gs;

  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  dvariable v1;
  dvariable v2;
  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  ASSERT_EQ(gradient_structure::get()->RETURN_ARRAYS_PTR, 0);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
  ASSERT_TRUE(gradient_structure::get()->MAX_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][69]);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == gradient_structure::get()->RETURN_PTR);

  int count = 0;
  for (int i = 1; i <= gradient_structure::get()->RETURN_ARRAYS_SIZE; ++i)
  {
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    v1 = i * 2;
    v2 = i;
    count += 2;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    grad_stack_entry* ptr = gradient_structure::get()->GRAD_STACK1->ptr;
    dvariable result = v1 - v2;
    ASSERT_TRUE(ptr->func == default_evaluation4m);
    dvariable* return_ptr = gradient_structure::get()->RETURN_PTR;
    ASSERT_TRUE(ptr->dep_addr == &(return_ptr->v->x));
    ASSERT_TRUE(ptr->ind_addr1 == &(v1.v->x));
    ASSERT_DOUBLE_EQ(ptr->mult1, 0.0);
    ASSERT_TRUE(ptr->ind_addr2 == &(v2.v->x));
    ASSERT_DOUBLE_EQ(ptr->mult2, 0.0);
    count += 2;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    ASSERT_DOUBLE_EQ(value(result), static_cast<double>(i * 2 - i));
    if (i == 70)
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
    else
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][i]);
  }
}
TEST_F(test_gradient_structure, return_arrays_double_minus_prevariable)
{
  gradient_structure gs;

  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  dvariable v2;
  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  ASSERT_EQ(gradient_structure::get()->RETURN_ARRAYS_PTR, 0);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
  ASSERT_TRUE(gradient_structure::get()->MAX_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][69]);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == gradient_structure::get()->RETURN_PTR);

  int count = 0;
  for (int i = 1; i <= gradient_structure::get()->RETURN_ARRAYS_SIZE; ++i)
  {
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    double v1 = i * 2;
    v2 = i;
    count += 1;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    grad_stack_entry* ptr = gradient_structure::get()->GRAD_STACK1->ptr;
    dvariable result = v1 - v2;
    ASSERT_TRUE(ptr->func == default_evaluation1m);
    dvariable* return_ptr = gradient_structure::get()->RETURN_PTR;
    ASSERT_TRUE(ptr->dep_addr == &(return_ptr->v->x));
    ASSERT_TRUE(ptr->ind_addr1 == &(v2.v->x));
    ASSERT_DOUBLE_EQ(ptr->mult1, 0.0);
    ASSERT_TRUE(ptr->ind_addr2 == NULL);
    ASSERT_DOUBLE_EQ(ptr->mult2, 0.0);
    count += 2;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    ASSERT_DOUBLE_EQ(value(result), static_cast<double>(i * 2 - i));
    if (i == 70)
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
    else
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][i]);
  }
}
TEST_F(test_gradient_structure, return_arrays_prevariable_minus_double)
{
  gradient_structure gs;

  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  dvariable v1;
  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  ASSERT_EQ(gradient_structure::get()->RETURN_ARRAYS_PTR, 0);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
  ASSERT_TRUE(gradient_structure::get()->MAX_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][69]);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == gradient_structure::get()->RETURN_PTR);

  int count = 0;
  for (int i = 1; i <= gradient_structure::get()->RETURN_ARRAYS_SIZE; ++i)
  {
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    double v2 = i * 2;
    v1 = i;
    count += 1;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    grad_stack_entry* ptr = gradient_structure::get()->GRAD_STACK1->ptr;
    dvariable result = v1 - v2;
    ASSERT_TRUE(ptr->func == default_evaluation1);
    dvariable* return_ptr = gradient_structure::get()->RETURN_PTR;
    ASSERT_TRUE(ptr->dep_addr == &(return_ptr->v->x));
    ASSERT_TRUE(ptr->ind_addr1 == &(v1.v->x));
    ASSERT_DOUBLE_EQ(ptr->mult1, 0.0);
    ASSERT_TRUE(ptr->ind_addr2 == NULL);
    ASSERT_DOUBLE_EQ(ptr->mult2, 0.0);
    count += 2;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    ASSERT_DOUBLE_EQ(value(result), static_cast<double>(i - i * 2));
    if (i == 70)
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
    else
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][i]);
  }
}
TEST_F(test_gradient_structure, return_arrays_prevariable_minus)
{
  gradient_structure gs;

  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  dvariable v1;
  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  ASSERT_EQ(gradient_structure::get()->RETURN_ARRAYS_PTR, 0);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
  ASSERT_TRUE(gradient_structure::get()->MAX_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][69]);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == gradient_structure::get()->RETURN_PTR);

  int count = 0;
  for (int i = 1; i <= gradient_structure::get()->RETURN_ARRAYS_SIZE; ++i)
  {
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    v1 = i;
    count += 1;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    grad_stack_entry* ptr = gradient_structure::get()->GRAD_STACK1->ptr;
    dvariable result = -v1;
    ASSERT_TRUE(ptr->func == default_evaluation1m);
    dvariable* return_ptr = gradient_structure::get()->RETURN_PTR;
    ASSERT_TRUE(ptr->dep_addr == &(return_ptr->v->x));
    ASSERT_TRUE(ptr->ind_addr1 == &(v1.v->x));
    ASSERT_DOUBLE_EQ(ptr->mult1, 0.0);
    ASSERT_TRUE(ptr->ind_addr2 == NULL);
    ASSERT_DOUBLE_EQ(ptr->mult2, 0.0);
    count += 2;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    ASSERT_DOUBLE_EQ(value(result), static_cast<double>(-i));
    if (i == 70)
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
    else
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][i]);
  }
}
TEST_F(test_gradient_structure, return_arrays_prevariable_div_prevariable)
{
  gradient_structure gs;

  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  dvariable v1;
  dvariable v2;
  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  ASSERT_EQ(gradient_structure::get()->RETURN_ARRAYS_PTR, 0);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
  ASSERT_TRUE(gradient_structure::get()->MAX_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][69]);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == gradient_structure::get()->RETURN_PTR);

  int count = 0;
  for (int i = 1; i <= gradient_structure::get()->RETURN_ARRAYS_SIZE; ++i)
  {
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    v1 = i * 2;
    v2 = i;
    count += 2;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    grad_stack_entry* ptr = gradient_structure::get()->GRAD_STACK1->ptr;
    dvariable result = v1 / v2;
    ASSERT_TRUE(ptr->func == default_evaluation3);
    dvariable* return_ptr = gradient_structure::get()->RETURN_PTR;
    ASSERT_TRUE(ptr->dep_addr == &(return_ptr->v->x));
    ASSERT_TRUE(ptr->ind_addr1 == &(v1.v->x));
    ASSERT_DOUBLE_EQ(ptr->mult1, 1.0 / v2.v->x);
    ASSERT_TRUE(ptr->ind_addr2 == &(v2.v->x));
    ASSERT_DOUBLE_EQ(ptr->mult2, -(v1.v->x) / (v2.v->x * v2.v->x));
    count += 2;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    ASSERT_DOUBLE_EQ(value(result), static_cast<double>(i * 2) / i);
    if (i == 70)
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
    else
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][i]);
  }
}
TEST_F(test_gradient_structure, return_arrays_double_div_prevariable)
{
  gradient_structure gs;

  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  dvariable v2;
  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  ASSERT_EQ(gradient_structure::get()->RETURN_ARRAYS_PTR, 0);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
  ASSERT_TRUE(gradient_structure::get()->MAX_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][69]);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == gradient_structure::get()->RETURN_PTR);

  int count = 0;
  for (int i = 1; i <= gradient_structure::get()->RETURN_ARRAYS_SIZE; ++i)
  {
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    double v1 = i * 2;
    v2 = i;
    count += 1;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    grad_stack_entry* ptr = gradient_structure::get()->GRAD_STACK1->ptr;
    dvariable result = v1 / v2;
    ASSERT_TRUE(ptr->func == default_evaluation);
    dvariable* return_ptr = gradient_structure::get()->RETURN_PTR;
    ASSERT_TRUE(ptr->dep_addr == &(return_ptr->v->x));
    ASSERT_TRUE(ptr->ind_addr1 == &(v2.v->x));
    ASSERT_DOUBLE_EQ(ptr->mult1, -v1 / (v2.v->x * v2.v->x));
    ASSERT_TRUE(ptr->ind_addr2 == NULL);
    ASSERT_DOUBLE_EQ(ptr->mult2, 0.0);
    count += 2;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    ASSERT_DOUBLE_EQ(value(result), static_cast<double>(i * 2) / i);
    if (i == 70)
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
    else
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][i]);
  }
}
TEST_F(test_gradient_structure, return_arrays_prevariable_div_double)
{
  gradient_structure gs;

  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  dvariable v1;
  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  ASSERT_EQ(gradient_structure::get()->RETURN_ARRAYS_PTR, 0);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
  ASSERT_TRUE(gradient_structure::get()->MAX_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][69]);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == gradient_structure::get()->RETURN_PTR);

  int count = 0;
  for (int i = 1; i <= gradient_structure::get()->RETURN_ARRAYS_SIZE; ++i)
  {
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    double v2 = i * 2;
    v1 = i;
    count += 1;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    grad_stack_entry* ptr = gradient_structure::get()->GRAD_STACK1->ptr;
    dvariable result = v1 / v2;
    ASSERT_TRUE(ptr->func == default_evaluation);
    dvariable* return_ptr = gradient_structure::get()->RETURN_PTR;
    ASSERT_TRUE(ptr->dep_addr == &(return_ptr->v->x));
    ASSERT_TRUE(ptr->ind_addr1 == &(v1.v->x));
    ASSERT_DOUBLE_EQ(ptr->mult1, 1.0 / v2);
    ASSERT_TRUE(ptr->ind_addr2 == NULL);
    ASSERT_DOUBLE_EQ(ptr->mult2, 0.0);
    count += 2;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    ASSERT_DOUBLE_EQ(value(result), static_cast<double>(i)/ (i * 2));
    if (i == 70)
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
    else
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][i]);
  }
}
TEST_F(test_gradient_structure, return_arrays_prevariable_times_double)
{
  gradient_structure gs;

  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  dvariable v1;
  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  ASSERT_EQ(gradient_structure::get()->RETURN_ARRAYS_PTR, 0);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
  ASSERT_TRUE(gradient_structure::get()->MAX_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][69]);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == gradient_structure::get()->RETURN_PTR);

  int count = 0;
  for (int i = 1; i <= gradient_structure::get()->RETURN_ARRAYS_SIZE; ++i)
  {
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    double v2 = i * 2;
    v1 = i;
    count += 1;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    grad_stack_entry* ptr = gradient_structure::get()->GRAD_STACK1->ptr;
    dvariable result = v1 * v2;
    ASSERT_TRUE(ptr->func == default_evaluation2);
    dvariable* return_ptr = gradient_structure::get()->RETURN_PTR;
    ASSERT_TRUE(ptr->dep_addr == &(return_ptr->v->x));
    ASSERT_TRUE(ptr->ind_addr1 == &(v1.v->x));
    ASSERT_DOUBLE_EQ(ptr->mult1, v2);
    ASSERT_TRUE(ptr->ind_addr2 == NULL);
    ASSERT_DOUBLE_EQ(ptr->mult2, 0.0);
    count += 2;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    ASSERT_DOUBLE_EQ(value(result), static_cast<double>(i) * (i * 2));
    if (i == 70)
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
    else
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][i]);
  }
}
TEST_F(test_gradient_structure, return_arrays_double_times_prevariable)
{
  gradient_structure gs;

  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  dvariable v2;
  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  ASSERT_EQ(gradient_structure::get()->RETURN_ARRAYS_PTR, 0);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
  ASSERT_TRUE(gradient_structure::get()->MAX_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][69]);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == gradient_structure::get()->RETURN_PTR);

  int count = 0;
  for (int i = 1; i <= gradient_structure::get()->RETURN_ARRAYS_SIZE; ++i)
  {
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    double v1 = i * 2;
    v2 = i;
    count += 1;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    grad_stack_entry* ptr = gradient_structure::get()->GRAD_STACK1->ptr;
    dvariable result = v1 * v2;
    ASSERT_TRUE(ptr->func == default_evaluation2);
    dvariable* return_ptr = gradient_structure::get()->RETURN_PTR;
    ASSERT_TRUE(ptr->dep_addr == &(return_ptr->v->x));
    ASSERT_TRUE(ptr->ind_addr1 == &(v2.v->x));
    ASSERT_DOUBLE_EQ(ptr->mult1, v1);
    ASSERT_TRUE(ptr->ind_addr2 == NULL);
    ASSERT_DOUBLE_EQ(ptr->mult2, 0.0);
    count += 2;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    ASSERT_DOUBLE_EQ(value(result), static_cast<double>(i * 2) * i);
    if (i == 70)
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
    else
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][i]);
  }
}
TEST_F(test_gradient_structure, return_arrays_square)
{
  gradient_structure gs;

  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  dvariable v1;
  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  ASSERT_EQ(gradient_structure::get()->RETURN_ARRAYS_PTR, 0);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
  ASSERT_TRUE(gradient_structure::get()->MAX_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][69]);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == gradient_structure::get()->RETURN_PTR);

  int count = 0;
  for (int i = 1; i <= gradient_structure::get()->RETURN_ARRAYS_SIZE; ++i)
  {
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    v1 = i;
    count += 1;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    grad_stack_entry* ptr = gradient_structure::get()->GRAD_STACK1->ptr;
    dvariable result = square(v1);
    ASSERT_TRUE(ptr->func == default_evaluation2);
    dvariable* return_ptr = gradient_structure::get()->RETURN_PTR;
    ASSERT_TRUE(ptr->dep_addr == &(return_ptr->v->x));
    ASSERT_TRUE(ptr->ind_addr1 == &(v1.v->x));
    ASSERT_DOUBLE_EQ(ptr->mult1, static_cast<double>(2 * i));
    ASSERT_TRUE(ptr->ind_addr2 == NULL);
    ASSERT_DOUBLE_EQ(ptr->mult2, 0.0);
    count += 2;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    ASSERT_DOUBLE_EQ(value(result), static_cast<double>(i * i));
    if (i == 70)
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
    else
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][i]);
  }
}
TEST_F(test_gradient_structure, return_arrays_cube)
{
  gradient_structure gs;

  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  dvariable v1;
  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  ASSERT_EQ(gradient_structure::get()->RETURN_ARRAYS_PTR, 0);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
  ASSERT_TRUE(gradient_structure::get()->MAX_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][69]);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == gradient_structure::get()->RETURN_PTR);

  int count = 0;
  for (int i = 1; i <= gradient_structure::get()->RETURN_ARRAYS_SIZE; ++i)
  {
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    v1 = i;
    count += 1;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    grad_stack_entry* ptr = gradient_structure::get()->GRAD_STACK1->ptr;
    dvariable result = cube(v1);
    ASSERT_TRUE(ptr->func == default_evaluation2);
    dvariable* return_ptr = gradient_structure::get()->RETURN_PTR;
    ASSERT_TRUE(ptr->dep_addr == &(return_ptr->v->x));
    ASSERT_TRUE(ptr->ind_addr1 == &(v1.v->x));
    ASSERT_DOUBLE_EQ(ptr->mult1, static_cast<double>(3 * i * i));
    ASSERT_TRUE(ptr->ind_addr2 == NULL);
    ASSERT_DOUBLE_EQ(ptr->mult2, 0.0);
    count += 2;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    ASSERT_DOUBLE_EQ(value(result), static_cast<double>(i * i * i));
    if (i == 70)
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
    else
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][i]);
  }
}
TEST_F(test_gradient_structure, return_arrays_fourth)
{
  gradient_structure gs;

  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  dvariable v1;
  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  ASSERT_EQ(gradient_structure::get()->RETURN_ARRAYS_PTR, 0);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
  ASSERT_TRUE(gradient_structure::get()->MAX_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][69]);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == gradient_structure::get()->RETURN_PTR);

  prevariable& fourth(const prevariable& v1);

  int count = 0;
  for (int i = 1; i <= gradient_structure::get()->RETURN_ARRAYS_SIZE; ++i)
  {
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    v1 = i;
    count += 1;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    grad_stack_entry* ptr = gradient_structure::get()->GRAD_STACK1->ptr;
    dvariable result = fourth(v1);
    ASSERT_TRUE(ptr->func == default_evaluation2);
    dvariable* return_ptr = gradient_structure::get()->RETURN_PTR;
    ASSERT_TRUE(ptr->dep_addr == &(return_ptr->v->x));
    ASSERT_TRUE(ptr->ind_addr1 == &(v1.v->x));
    ASSERT_DOUBLE_EQ(ptr->mult1, static_cast<double>(4 * i * i * i));
    ASSERT_TRUE(ptr->ind_addr2 == NULL);
    ASSERT_DOUBLE_EQ(ptr->mult2, 0.0);
    count += 2;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    ASSERT_DOUBLE_EQ(value(result), static_cast<double>(i * i * i * i));
    if (i == 70)
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
    else
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][i]);
  }
}
TEST_F(test_gradient_structure, return_arrays_cos)
{
  gradient_structure gs;

  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  dvariable v1;
  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  ASSERT_EQ(gradient_structure::get()->RETURN_ARRAYS_PTR, 0);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
  ASSERT_TRUE(gradient_structure::get()->MAX_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][69]);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == gradient_structure::get()->RETURN_PTR);

  prevariable& fourth(const prevariable& v1);

  int count = 0;
  for (int i = 1; i <= gradient_structure::get()->RETURN_ARRAYS_SIZE; ++i)
  {
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    v1 = i;
    count += 1;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    grad_stack_entry* ptr = gradient_structure::get()->GRAD_STACK1->ptr;
    dvariable result = cos(v1);
    ASSERT_TRUE(ptr->func == default_evaluation);
    dvariable* return_ptr = gradient_structure::get()->RETURN_PTR;
    ASSERT_TRUE(ptr->dep_addr == &(return_ptr->v->x));
    ASSERT_TRUE(ptr->ind_addr1 == &(v1.v->x));
    ASSERT_DOUBLE_EQ(ptr->mult1, -1.0 * std::sin(static_cast<double>(i)));
    ASSERT_TRUE(ptr->ind_addr2 == NULL);
    ASSERT_DOUBLE_EQ(ptr->mult2, 0.0);
    count += 2;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    ASSERT_DOUBLE_EQ(value(result), std::cos(static_cast<double>(i)));
    if (i == 70)
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
    else
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][i]);
  }
}
TEST_F(test_gradient_structure, return_arrays_sin)
{
  gradient_structure gs;

  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  dvariable v1;
  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  ASSERT_EQ(gradient_structure::get()->RETURN_ARRAYS_PTR, 0);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
  ASSERT_TRUE(gradient_structure::get()->MAX_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][69]);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == gradient_structure::get()->RETURN_PTR);

  int count = 0;
  for (int i = 1; i <= gradient_structure::get()->RETURN_ARRAYS_SIZE; ++i)
  {
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    v1 = i;
    count += 1;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    grad_stack_entry* ptr = gradient_structure::get()->GRAD_STACK1->ptr;
    dvariable result = sin(v1);
    ASSERT_TRUE(ptr->func == default_evaluation);
    dvariable* return_ptr = gradient_structure::get()->RETURN_PTR;
    ASSERT_TRUE(ptr->dep_addr == &(return_ptr->v->x));
    ASSERT_TRUE(ptr->ind_addr1 == &(v1.v->x));
    ASSERT_DOUBLE_EQ(ptr->mult1, std::cos(static_cast<double>(i)));
    ASSERT_TRUE(ptr->ind_addr2 == NULL);
    ASSERT_DOUBLE_EQ(ptr->mult2, 0.0);
    count += 2;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    ASSERT_DOUBLE_EQ(value(result), std::sin(static_cast<double>(i)));
    if (i == 70)
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
    else
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][i]);
  }
}
TEST_F(test_gradient_structure, return_arrays_log)
{
  gradient_structure gs;

  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  dvariable v1;
  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  ASSERT_EQ(gradient_structure::get()->RETURN_ARRAYS_PTR, 0);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
  ASSERT_TRUE(gradient_structure::get()->MAX_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][69]);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == gradient_structure::get()->RETURN_PTR);

  int count = 0;
  for (int i = 1; i <= gradient_structure::get()->RETURN_ARRAYS_SIZE; ++i)
  {
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    v1 = i + 1;
    count += 1;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    grad_stack_entry* ptr = gradient_structure::get()->GRAD_STACK1->ptr;
    dvariable result = log(v1);
    ASSERT_TRUE(ptr->func == default_evaluation);
    dvariable* return_ptr = gradient_structure::get()->RETURN_PTR;
    ASSERT_TRUE(ptr->dep_addr == &(return_ptr->v->x));
    ASSERT_TRUE(ptr->ind_addr1 == &(v1.v->x));
    ASSERT_DOUBLE_EQ(ptr->mult1, 1.0 / (static_cast<double>(i + 1)));
    ASSERT_TRUE(ptr->ind_addr2 == NULL);
    ASSERT_DOUBLE_EQ(ptr->mult2, 0.0);
    count += 2;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    ASSERT_DOUBLE_EQ(value(result), std::log(static_cast<double>(i + 1)));
    if (i == 70)
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
    else
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][i]);
  }
}
TEST_F(test_gradient_structure, return_arrays_log10)
{
  gradient_structure gs;

  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  dvariable v1;
  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  ASSERT_EQ(gradient_structure::get()->RETURN_ARRAYS_PTR, 0);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
  ASSERT_TRUE(gradient_structure::get()->MAX_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][69]);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == gradient_structure::get()->RETURN_PTR);

  int count = 0;
  for (int i = 1; i <= gradient_structure::get()->RETURN_ARRAYS_SIZE; ++i)
  {
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    v1 = i + 1;
    count += 1;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    grad_stack_entry* ptr = gradient_structure::get()->GRAD_STACK1->ptr;
    dvariable result = log10(v1);
    ASSERT_TRUE(ptr->func == default_evaluation);
    dvariable* return_ptr = gradient_structure::get()->RETURN_PTR;
    ASSERT_TRUE(ptr->dep_addr == &(return_ptr->v->x));
    ASSERT_TRUE(ptr->ind_addr1 == &(v1.v->x));
    ASSERT_DOUBLE_EQ(ptr->mult1, 1.0 / (2.3025851 * static_cast<double>(i + 1)));
    ASSERT_TRUE(ptr->ind_addr2 == NULL);
    ASSERT_DOUBLE_EQ(ptr->mult2, 0.0);
    count += 2;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    ASSERT_DOUBLE_EQ(value(result), std::log10(static_cast<double>(i + 1)));
    if (i == 70)
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
    else
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][i]);
  }
}
TEST_F(test_gradient_structure, return_arrays_sigmoid)
{
  gradient_structure gs;

  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  dvariable v1;
  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  ASSERT_EQ(gradient_structure::get()->RETURN_ARRAYS_PTR, 0);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
  ASSERT_TRUE(gradient_structure::get()->MAX_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][69]);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == gradient_structure::get()->RETURN_PTR);

  int count = 0;
  for (int i = 1; i <= gradient_structure::get()->RETURN_ARRAYS_SIZE; ++i)
  {
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    v1 = i + 1;
    count += 1;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    grad_stack_entry* ptr = gradient_structure::get()->GRAD_STACK1->ptr;
    dvariable result = sigmoid(v1);
    ASSERT_TRUE(ptr->func == default_evaluation);
    dvariable* return_ptr = gradient_structure::get()->RETURN_PTR;
    ASSERT_TRUE(ptr->dep_addr == &(return_ptr->v->x));
    ASSERT_TRUE(ptr->ind_addr1 == &(v1.v->x));
    ASSERT_DOUBLE_EQ(ptr->mult1, 1.0 / (2.8 * (1.0 + static_cast<double>(i + 1) * static_cast<double>(i + 1))));
    ASSERT_TRUE(ptr->ind_addr2 == NULL);
    ASSERT_DOUBLE_EQ(ptr->mult2, 0.0);
    count += 2;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    ASSERT_DOUBLE_EQ(value(result), std::atan(static_cast<double>(i + 1)) / 2.8);
    if (i == 70)
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
    else
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][i]);
  }
}
TEST_F(test_gradient_structure, return_arrays_pow)
{
  gradient_structure gs;

  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  dvariable v1;
  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  ASSERT_EQ(gradient_structure::get()->RETURN_ARRAYS_PTR, 0);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
  ASSERT_TRUE(gradient_structure::get()->MAX_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][69]);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == gradient_structure::get()->RETURN_PTR);

  int count = 0;
  for (int i = 1; i <= gradient_structure::get()->RETURN_ARRAYS_SIZE; ++i)
  {
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    v1 = i;
    count += 1;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    grad_stack_entry* ptr = gradient_structure::get()->GRAD_STACK1->ptr;
    dvariable result = pow(v1, static_cast<double>(i) + 0.5);
    ASSERT_TRUE(ptr->func == default_evaluation);
    dvariable* return_ptr = gradient_structure::get()->RETURN_PTR;
    ASSERT_TRUE(ptr->dep_addr == &(return_ptr->v->x));
    ASSERT_TRUE(ptr->ind_addr1 == &(v1.v->x));
    ASSERT_DOUBLE_EQ(ptr->mult1, (static_cast<double>(i) + 0.5) * std::pow(static_cast<double>(i), static_cast<double>(i) + 0.5 - 1.0));
    ASSERT_TRUE(ptr->ind_addr2 == NULL);
    ASSERT_DOUBLE_EQ(ptr->mult2, 0.0);
    count += 2;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    ASSERT_DOUBLE_EQ(value(result), std::pow(static_cast<double>(i), static_cast<double>(i) + 0.5));
    if (i == 70)
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
    else
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][i]);
  }
}
TEST_F(test_gradient_structure, return_arrays_fabs_positive)
{
  gradient_structure gs;

  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  dvariable v1;
  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  ASSERT_EQ(gradient_structure::get()->RETURN_ARRAYS_PTR, 0);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
  ASSERT_TRUE(gradient_structure::get()->MAX_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][69]);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == gradient_structure::get()->RETURN_PTR);

  int count = 0;
  for (int i = 1; i <= gradient_structure::get()->RETURN_ARRAYS_SIZE; ++i)
  {
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    v1 = i;
    count += 1;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    grad_stack_entry* ptr = gradient_structure::get()->GRAD_STACK1->ptr;
    dvariable result = fabs(v1);
    ASSERT_TRUE(ptr->func == default_evaluation);
    dvariable* return_ptr = gradient_structure::get()->RETURN_PTR;
    ASSERT_TRUE(ptr->dep_addr == &(return_ptr->v->x));
    ASSERT_TRUE(ptr->ind_addr1 == &(v1.v->x));
    ASSERT_DOUBLE_EQ(ptr->mult1, 1.0);
    ASSERT_TRUE(ptr->ind_addr2 == NULL);
    ASSERT_DOUBLE_EQ(ptr->mult2, 0.0);
    count += 2;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    ASSERT_DOUBLE_EQ(value(result), i);
    if (i == 70)
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
    else
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][i]);
  }
}
TEST_F(test_gradient_structure, return_arrays_fabs_negative)
{
  gradient_structure gs;

  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  dvariable v1;
  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  ASSERT_EQ(gradient_structure::get()->RETURN_ARRAYS_PTR, 0);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
  ASSERT_TRUE(gradient_structure::get()->MAX_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][69]);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == gradient_structure::get()->RETURN_PTR);

  int count = 0;
  for (int i = 1; i <= gradient_structure::get()->RETURN_ARRAYS_SIZE; ++i)
  {
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    v1 = -1.0 * i;
    count += 1;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    grad_stack_entry* ptr = gradient_structure::get()->GRAD_STACK1->ptr;
    dvariable result = fabs(v1);
    ASSERT_TRUE(ptr->func == default_evaluation);
    dvariable* return_ptr = gradient_structure::get()->RETURN_PTR;
    ASSERT_TRUE(ptr->dep_addr == &(return_ptr->v->x));
    ASSERT_TRUE(ptr->ind_addr1 == &(v1.v->x));
    ASSERT_DOUBLE_EQ(ptr->mult1, -1.0);
    ASSERT_TRUE(ptr->ind_addr2 == NULL);
    ASSERT_DOUBLE_EQ(ptr->mult2, 0.0);
    count += 2;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    ASSERT_DOUBLE_EQ(value(result), i);
    if (i == 70)
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
    else
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][i]);
  }
}
TEST_F(test_gradient_structure, return_arrays_sfabs_negative_greater_than_cutoff)
{
  constexpr double cutoff = 0.001; //  h

  gradient_structure gs;

  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  dvariable v1;
  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  ASSERT_EQ(gradient_structure::get()->RETURN_ARRAYS_PTR, 0);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
  ASSERT_TRUE(gradient_structure::get()->MAX_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][69]);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == gradient_structure::get()->RETURN_PTR);

  int count = 0;
  for (int i = 1; i <= gradient_structure::get()->RETURN_ARRAYS_SIZE; ++i)
  {
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    v1 = -1.0 * i;
    ASSERT_TRUE(std::fabs(-1.0 * i) > cutoff);
    count += 1;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    grad_stack_entry* ptr = gradient_structure::get()->GRAD_STACK1->ptr;
    dvariable result = sfabs(v1);
    ASSERT_TRUE(ptr->func == default_evaluation);
    dvariable* return_ptr = gradient_structure::get()->RETURN_PTR;
    ASSERT_TRUE(ptr->dep_addr == &(return_ptr->v->x));
    ASSERT_TRUE(ptr->ind_addr1 == &(v1.v->x));
    ASSERT_DOUBLE_EQ(ptr->mult1, -1.0);
    ASSERT_TRUE(ptr->ind_addr2 == NULL);
    ASSERT_DOUBLE_EQ(ptr->mult2, 0.0);
    count += 2;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    ASSERT_DOUBLE_EQ(value(result), i);
    if (i == 70)
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
    else
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][i]);
  }
}
TEST_F(test_gradient_structure, return_arrays_sfabs_positive_greater_than_cutoff)
{
  constexpr double cutoff = 0.001; //  h

  gradient_structure gs;

  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  dvariable v1;
  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  ASSERT_EQ(gradient_structure::get()->RETURN_ARRAYS_PTR, 0);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
  ASSERT_TRUE(gradient_structure::get()->MAX_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][69]);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == gradient_structure::get()->RETURN_PTR);

  int count = 0;
  for (int i = 1; i <= gradient_structure::get()->RETURN_ARRAYS_SIZE; ++i)
  {
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    v1 = i;
    ASSERT_TRUE(std::fabs(i) > cutoff);
    count += 1;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    grad_stack_entry* ptr = gradient_structure::get()->GRAD_STACK1->ptr;
    dvariable result = sfabs(v1);
    ASSERT_TRUE(ptr->func == default_evaluation);
    dvariable* return_ptr = gradient_structure::get()->RETURN_PTR;
    ASSERT_TRUE(ptr->dep_addr == &(return_ptr->v->x));
    ASSERT_TRUE(ptr->ind_addr1 == &(v1.v->x));
    ASSERT_DOUBLE_EQ(ptr->mult1, 1.0);
    ASSERT_TRUE(ptr->ind_addr2 == NULL);
    ASSERT_DOUBLE_EQ(ptr->mult2, 0.0);
    count += 2;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    ASSERT_DOUBLE_EQ(value(result), i);
    if (i == 70)
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
    else
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][i]);
  }
}
TEST_F(test_gradient_structure, return_arrays_sfabs_positive_less_than_cutoff)
{
  double cutoff = 0.001; //  h
  double cutoff2 = 0.000001; //  h
  double a = 2.0 / cutoff; // 2.0/h
  double b = 1.0 / cutoff2; // 1.0/(h*h)

  gradient_structure gs;

  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  dvariable v1;
  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  ASSERT_EQ(gradient_structure::get()->RETURN_ARRAYS_PTR, 0);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
  ASSERT_TRUE(gradient_structure::get()->MAX_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][69]);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == gradient_structure::get()->RETURN_PTR);

  int count = 0;
  for (int i = 1; i <= gradient_structure::get()->RETURN_ARRAYS_SIZE; ++i)
  {
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    v1 = 0.00001 * i;
    ASSERT_TRUE(std::fabs(0.00001 * i) <= cutoff);
    count += 1;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    grad_stack_entry* ptr = gradient_structure::get()->GRAD_STACK1->ptr;
    dvariable result = sfabs(v1);
    ASSERT_TRUE(ptr->func == default_evaluation);
    dvariable* return_ptr = gradient_structure::get()->RETURN_PTR;
    ASSERT_TRUE(ptr->dep_addr == &(return_ptr->v->x));
    ASSERT_TRUE(ptr->ind_addr1 == &(v1.v->x));
    //tmp*(2*a-3*b*tmp1
    ASSERT_DOUBLE_EQ(ptr->mult1, (0.00001 * i) * (2.0 * a - 3.0 * b * 0.00001 * static_cast<double>(i)));
    ASSERT_TRUE(ptr->ind_addr2 == NULL);
    ASSERT_DOUBLE_EQ(ptr->mult2, 0.0);
    count += 2;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    //t2*(a-b*tmp1)
    ASSERT_DOUBLE_EQ(value(result), std::fabs(0.00001 * i) * std::fabs(0.00001 * i) * (a - b * 0.00001 * i));
    if (i == 70)
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
    else
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][i]);
  }
}
TEST_F(test_gradient_structure, return_arrays_sfabs_negative_less_than_cutoff)
{
  double cutoff = 0.001; //  h
  double cutoff2 = 0.000001; //  h
  double a = 2.0 / cutoff; // 2.0/h
  double b = 1.0 / cutoff2; // 1.0/(h*h)

  gradient_structure gs;

  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  dvariable v1;
  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  ASSERT_EQ(gradient_structure::get()->RETURN_ARRAYS_PTR, 0);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
  ASSERT_TRUE(gradient_structure::get()->MAX_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][69]);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == gradient_structure::get()->RETURN_PTR);

  int count = 0;
  for (int i = 1; i <= gradient_structure::get()->RETURN_ARRAYS_SIZE; ++i)
  {
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    v1 = -0.00001 * i;
    ASSERT_TRUE(std::fabs(-0.00001 * i) <= cutoff);
    count += 1;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    grad_stack_entry* ptr = gradient_structure::get()->GRAD_STACK1->ptr;
    dvariable result = sfabs(v1);
    ASSERT_TRUE(ptr->func == default_evaluation);
    dvariable* return_ptr = gradient_structure::get()->RETURN_PTR;
    ASSERT_TRUE(ptr->dep_addr == &(return_ptr->v->x));
    ASSERT_TRUE(ptr->ind_addr1 == &(v1.v->x));
    //tmp*(2*a-3*b*tmp1
    ASSERT_DOUBLE_EQ(ptr->mult1, (-0.00001 * i) * (2.0 * a - 3.0 * b * 0.00001 * static_cast<double>(i)));
    ASSERT_TRUE(ptr->ind_addr2 == NULL);
    ASSERT_DOUBLE_EQ(ptr->mult2, 0.0);
    count += 2;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    //t2*(a-b*tmp1)
    ASSERT_FALSE(-0.00001 * i >= 0);
    ASSERT_DOUBLE_EQ(value(result), std::fabs(-0.00001 * i) * std::fabs(-0.00001 * i) * (a + b * -0.00001 * i));
    if (i == 70)
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
    else
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][i]);
  }
}
TEST_F(test_gradient_structure, return_arrays_exp_positive)
{
  gradient_structure gs;

  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  dvariable v1;
  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  ASSERT_EQ(gradient_structure::get()->RETURN_ARRAYS_PTR, 0);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
  ASSERT_TRUE(gradient_structure::get()->MAX_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][69]);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == gradient_structure::get()->RETURN_PTR);

  int count = 0;
  for (int i = 1; i <= gradient_structure::get()->RETURN_ARRAYS_SIZE; ++i)
  {
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    v1 = i;
    count += 1;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    grad_stack_entry* ptr = gradient_structure::get()->GRAD_STACK1->ptr;
    dvariable result = exp(v1);
    ASSERT_TRUE(ptr->func == default_evaluation);
    dvariable* return_ptr = gradient_structure::get()->RETURN_PTR;
    ASSERT_TRUE(ptr->dep_addr == &(return_ptr->v->x));
    ASSERT_TRUE(ptr->ind_addr1 == &(v1.v->x));
    ASSERT_DOUBLE_EQ(ptr->mult1, std::exp(static_cast<double>(i)));
    ASSERT_TRUE(ptr->ind_addr2 == NULL);
    ASSERT_DOUBLE_EQ(ptr->mult2, 0.0);
    count += 2;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    ASSERT_DOUBLE_EQ(value(result), std::exp(static_cast<double>(i)));
    if (i == 70)
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
    else
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][i]);
  }
}
TEST_F(test_gradient_structure, return_arrays_exp_negative)
{
  gradient_structure gs;

  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  dvariable v1;
  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  ASSERT_EQ(gradient_structure::get()->RETURN_ARRAYS_PTR, 0);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
  ASSERT_TRUE(gradient_structure::get()->MAX_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][69]);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == gradient_structure::get()->RETURN_PTR);

  int count = 0;
  for (int i = 1; i <= gradient_structure::get()->RETURN_ARRAYS_SIZE; ++i)
  {
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    v1 = -i;
    count += 1;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    grad_stack_entry* ptr = gradient_structure::get()->GRAD_STACK1->ptr;
    dvariable result = exp(v1);
    ASSERT_TRUE(ptr->func == default_evaluation);
    dvariable* return_ptr = gradient_structure::get()->RETURN_PTR;
    ASSERT_TRUE(ptr->dep_addr == &(return_ptr->v->x));
    ASSERT_TRUE(ptr->ind_addr1 == &(v1.v->x));
    ASSERT_DOUBLE_EQ(ptr->mult1, std::exp(static_cast<double>(-i)));
    ASSERT_TRUE(ptr->ind_addr2 == NULL);
    ASSERT_DOUBLE_EQ(ptr->mult2, 0.0);
    count += 2;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    ASSERT_DOUBLE_EQ(value(result), std::exp(static_cast<double>(-i)));
    if (i == 70)
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
    else
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][i]);
  }
}
TEST_F(test_gradient_structure, return_arrays_pow_double_to_variable)
{
  gradient_structure gs;

  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  dvariable v1;
  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  ASSERT_EQ(gradient_structure::get()->RETURN_ARRAYS_PTR, 0);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
  ASSERT_TRUE(gradient_structure::get()->MAX_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][69]);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == gradient_structure::get()->RETURN_PTR);

  int count = 0;
  for (int i = 1; i <= gradient_structure::get()->RETURN_ARRAYS_SIZE; ++i)
  {
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    v1 = i;
    count += 1;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    grad_stack_entry* ptr = gradient_structure::get()->GRAD_STACK1->ptr;
    dvariable result = pow(static_cast<double>(i) + 0.5, v1);
    ASSERT_TRUE(ptr->func == default_evaluation);
    dvariable* return_ptr = gradient_structure::get()->RETURN_PTR;
    ASSERT_TRUE(ptr->dep_addr == &(return_ptr->v->x));
    ASSERT_TRUE(ptr->ind_addr1 == &(v1.v->x));
    ASSERT_DOUBLE_EQ(ptr->mult1, std::pow(static_cast<double>(i) + 0.5, static_cast<double>(i)) * std::log(static_cast<double>(i) + 0.5));
    ASSERT_TRUE(ptr->ind_addr2 == NULL);
    ASSERT_DOUBLE_EQ(ptr->mult2, 0.0);
    count += 2;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    ASSERT_DOUBLE_EQ(value(result), std::pow(static_cast<double>(i) + 0.5, static_cast<double>(i)));
    if (i == 70)
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
    else
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][i]);
  }
}
TEST_F(test_gradient_structure, return_arrays_pow_double_to_negvariable)
{
  gradient_structure gs;

  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  dvariable v1;
  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  ASSERT_EQ(gradient_structure::get()->RETURN_ARRAYS_PTR, 0);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
  ASSERT_TRUE(gradient_structure::get()->MAX_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][69]);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == gradient_structure::get()->RETURN_PTR);

  int count = 0;
  for (int i = 1; i <= gradient_structure::get()->RETURN_ARRAYS_SIZE; ++i)
  {
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    v1 = -i;
    count += 1;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    grad_stack_entry* ptr = gradient_structure::get()->GRAD_STACK1->ptr;
    dvariable result = pow(static_cast<double>(i) + 0.5, v1);
    ASSERT_TRUE(ptr->func == default_evaluation);
    dvariable* return_ptr = gradient_structure::get()->RETURN_PTR;
    ASSERT_TRUE(ptr->dep_addr == &(return_ptr->v->x));
    ASSERT_TRUE(ptr->ind_addr1 == &(v1.v->x));
    ASSERT_DOUBLE_EQ(ptr->mult1, std::pow(static_cast<double>(i) + 0.5, -1.0 * static_cast<double>(i)) * std::log(static_cast<double>(i) + 0.5));
    ASSERT_TRUE(ptr->ind_addr2 == NULL);
    ASSERT_DOUBLE_EQ(ptr->mult2, 0.0);
    count += 2;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    ASSERT_DOUBLE_EQ(value(result), std::pow(static_cast<double>(i) + 0.5, -1.0 * static_cast<double>(i)));
    if (i == 70)
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
    else
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][i]);
  }
}
TEST_F(test_gradient_structure, return_arrays_pow_prevariable_prevariable)
{
  gradient_structure gs;

  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  dvariable v1;
  dvariable v2;
  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  ASSERT_EQ(gradient_structure::get()->RETURN_ARRAYS_PTR, 0);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
  ASSERT_TRUE(gradient_structure::get()->MAX_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][69]);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == gradient_structure::get()->RETURN_PTR);

  int count = 0;
  for (int i = 1; i <= gradient_structure::get()->RETURN_ARRAYS_SIZE; ++i)
  {
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    v1 = static_cast<double>(i) + 0.5;
    v2 = i;
    count += 2;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    grad_stack_entry* ptr = gradient_structure::get()->GRAD_STACK1->ptr;
    dvariable result = pow(v1, v2);
    ASSERT_TRUE(ptr->func == default_evaluation);
    dvariable* return_ptr = gradient_structure::get()->RETURN_PTR;
    ASSERT_TRUE(ptr->dep_addr == &(return_ptr->v->x));
    ASSERT_TRUE(ptr->ind_addr1 == &(v1.v->x));
    ASSERT_DOUBLE_EQ(ptr->mult1, v2.v->x * std::pow(static_cast<double>(i) + 0.5, static_cast<double>(i) - 1.0));
    ASSERT_TRUE(ptr->ind_addr2 == &(v2.v->x));
    ASSERT_DOUBLE_EQ(ptr->mult2, std::pow(static_cast<double>(i) + 0.5, static_cast<double>(i)) * std::log(static_cast<double>(i) + 0.5));
    count += 2;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    ASSERT_DOUBLE_EQ(value(result), std::pow(static_cast<double>(i) + 0.5, static_cast<double>(i)));
    if (i == 70)
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
    else
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][i]);
  }
}
TEST_F(test_gradient_structure, return_arrays_cosh_positive)
{
  gradient_structure gs;

  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  dvariable v1;
  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  ASSERT_EQ(gradient_structure::get()->RETURN_ARRAYS_PTR, 0);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
  ASSERT_TRUE(gradient_structure::get()->MAX_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][69]);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == gradient_structure::get()->RETURN_PTR);

  int count = 0;
  for (int i = 1; i <= gradient_structure::get()->RETURN_ARRAYS_SIZE; ++i)
  {
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    v1 = i + 1;
    count += 1;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    grad_stack_entry* ptr = gradient_structure::get()->GRAD_STACK1->ptr;
    dvariable result = cosh(v1);
    ASSERT_TRUE(ptr->func == default_evaluation);
    dvariable* return_ptr = gradient_structure::get()->RETURN_PTR;
    ASSERT_TRUE(ptr->dep_addr == &(return_ptr->v->x));
    ASSERT_TRUE(ptr->ind_addr1 == &(v1.v->x));
    ASSERT_DOUBLE_EQ(ptr->mult1, std::sinh(static_cast<double>(i + 1)));
    ASSERT_TRUE(ptr->ind_addr2 == NULL);
    ASSERT_DOUBLE_EQ(ptr->mult2, 0.0);
    count += 2;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    ASSERT_DOUBLE_EQ(value(result), std::cosh(static_cast<double>(i + 1)));
    if (i == 70)
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
    else
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][i]);
  }
}
TEST_F(test_gradient_structure, return_arrays_cosh_negative)
{
  gradient_structure gs;

  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  dvariable v1;
  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  ASSERT_EQ(gradient_structure::get()->RETURN_ARRAYS_PTR, 0);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
  ASSERT_TRUE(gradient_structure::get()->MAX_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][69]);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == gradient_structure::get()->RETURN_PTR);

  int count = 0;
  for (int i = 1; i <= gradient_structure::get()->RETURN_ARRAYS_SIZE; ++i)
  {
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    v1 = -i - 1;
    count += 1;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    grad_stack_entry* ptr = gradient_structure::get()->GRAD_STACK1->ptr;
    dvariable result = cosh(v1);
    ASSERT_TRUE(ptr->func == default_evaluation);
    dvariable* return_ptr = gradient_structure::get()->RETURN_PTR;
    ASSERT_TRUE(ptr->dep_addr == &(return_ptr->v->x));
    ASSERT_TRUE(ptr->ind_addr1 == &(v1.v->x));
    ASSERT_DOUBLE_EQ(ptr->mult1, std::sinh(static_cast<double>(-i - 1)));
    ASSERT_TRUE(ptr->ind_addr2 == NULL);
    ASSERT_DOUBLE_EQ(ptr->mult2, 0.0);
    count += 2;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    ASSERT_DOUBLE_EQ(value(result), std::cosh(static_cast<double>(-i - 1)));
    if (i == 70)
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
    else
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][i]);
  }
}
TEST_F(test_gradient_structure, return_arrays_sinh_positive)
{
  gradient_structure gs;

  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  dvariable v1;
  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  ASSERT_EQ(gradient_structure::get()->RETURN_ARRAYS_PTR, 0);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
  ASSERT_TRUE(gradient_structure::get()->MAX_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][69]);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == gradient_structure::get()->RETURN_PTR);

  int count = 0;
  for (int i = 1; i <= gradient_structure::get()->RETURN_ARRAYS_SIZE; ++i)
  {
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    v1 = i + 1;
    count += 1;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    grad_stack_entry* ptr = gradient_structure::get()->GRAD_STACK1->ptr;
    dvariable result = sinh(v1);
    ASSERT_TRUE(ptr->func == default_evaluation);
    dvariable* return_ptr = gradient_structure::get()->RETURN_PTR;
    ASSERT_TRUE(ptr->dep_addr == &(return_ptr->v->x));
    ASSERT_TRUE(ptr->ind_addr1 == &(v1.v->x));
    ASSERT_DOUBLE_EQ(ptr->mult1, std::cosh(static_cast<double>(i + 1)));
    ASSERT_TRUE(ptr->ind_addr2 == NULL);
    ASSERT_DOUBLE_EQ(ptr->mult2, 0.0);
    count += 2;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    ASSERT_DOUBLE_EQ(value(result), std::sinh(static_cast<double>(i + 1)));
    if (i == 70)
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
    else
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][i]);
  }
}
TEST_F(test_gradient_structure, return_arrays_sinh_negative)
{
  gradient_structure gs;

  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  dvariable v1;
  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  ASSERT_EQ(gradient_structure::get()->RETURN_ARRAYS_PTR, 0);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
  ASSERT_TRUE(gradient_structure::get()->MAX_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][69]);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == gradient_structure::get()->RETURN_PTR);

  int count = 0;
  for (int i = 1; i <= gradient_structure::get()->RETURN_ARRAYS_SIZE; ++i)
  {
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    v1 = -i - 1;
    count += 1;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    grad_stack_entry* ptr = gradient_structure::get()->GRAD_STACK1->ptr;
    dvariable result = sinh(v1);
    ASSERT_TRUE(ptr->func == default_evaluation);
    dvariable* return_ptr = gradient_structure::get()->RETURN_PTR;
    ASSERT_TRUE(ptr->dep_addr == &(return_ptr->v->x));
    ASSERT_TRUE(ptr->ind_addr1 == &(v1.v->x));
    ASSERT_DOUBLE_EQ(ptr->mult1, std::cosh(static_cast<double>(-i - 1)));
    ASSERT_TRUE(ptr->ind_addr2 == NULL);
    ASSERT_DOUBLE_EQ(ptr->mult2, 0.0);
    count += 2;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    ASSERT_DOUBLE_EQ(value(result), std::sinh(static_cast<double>(-i - 1)));
    if (i == 70)
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
    else
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][i]);
  }
}
TEST_F(test_gradient_structure, return_arrays_atan_positive)
{
  gradient_structure gs;

  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  dvariable v1;
  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  ASSERT_EQ(gradient_structure::get()->RETURN_ARRAYS_PTR, 0);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
  ASSERT_TRUE(gradient_structure::get()->MAX_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][69]);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == gradient_structure::get()->RETURN_PTR);

  int count = 0;
  for (int i = 1; i <= gradient_structure::get()->RETURN_ARRAYS_SIZE; ++i)
  {
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    v1 = i + 1;
    count += 1;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    grad_stack_entry* ptr = gradient_structure::get()->GRAD_STACK1->ptr;
    dvariable result = atan(v1);
    ASSERT_TRUE(ptr->func == default_evaluation);
    dvariable* return_ptr = gradient_structure::get()->RETURN_PTR;
    ASSERT_TRUE(ptr->dep_addr == &(return_ptr->v->x));
    ASSERT_TRUE(ptr->ind_addr1 == &(v1.v->x));
    ASSERT_DOUBLE_EQ(ptr->mult1, 1.0 / (1.0 + static_cast<double>(i + 1) * static_cast<double>(i + 1)));
    ASSERT_TRUE(ptr->ind_addr2 == NULL);
    ASSERT_DOUBLE_EQ(ptr->mult2, 0.0);
    count += 2;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    ASSERT_DOUBLE_EQ(value(result), std::atan(static_cast<double>(i + 1)));
    if (i == 70)
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
    else
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][i]);
  }
}
TEST_F(test_gradient_structure, return_arrays_atan_negative)
{
  gradient_structure gs;

  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  dvariable v1;
  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  ASSERT_EQ(gradient_structure::get()->RETURN_ARRAYS_PTR, 0);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
  ASSERT_TRUE(gradient_structure::get()->MAX_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][69]);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == gradient_structure::get()->RETURN_PTR);

  int count = 0;
  for (int i = 1; i <= gradient_structure::get()->RETURN_ARRAYS_SIZE; ++i)
  {
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    v1 = -i - 1;
    count += 1;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    grad_stack_entry* ptr = gradient_structure::get()->GRAD_STACK1->ptr;
    dvariable result = atan(v1);
    ASSERT_TRUE(ptr->func == default_evaluation);
    dvariable* return_ptr = gradient_structure::get()->RETURN_PTR;
    ASSERT_TRUE(ptr->dep_addr == &(return_ptr->v->x));
    ASSERT_TRUE(ptr->ind_addr1 == &(v1.v->x));
    ASSERT_DOUBLE_EQ(ptr->mult1, 1.0 / (1.0 + static_cast<double>(-i - 1) * static_cast<double>(-i - 1)));
    ASSERT_TRUE(ptr->ind_addr2 == NULL);
    ASSERT_DOUBLE_EQ(ptr->mult2, 0.0);
    count += 2;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    ASSERT_DOUBLE_EQ(value(result), std::atan(static_cast<double>(-i - 1)));
    if (i == 70)
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
    else
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][i]);
  }
}
TEST_F(test_gradient_structure, return_arrays_ldexp_positive)
{
  gradient_structure gs;

  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  dvariable v1;
  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  ASSERT_EQ(gradient_structure::get()->RETURN_ARRAYS_PTR, 0);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
  ASSERT_TRUE(gradient_structure::get()->MAX_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][69]);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == gradient_structure::get()->RETURN_PTR);

  int count = 0;
  for (int i = 1; i <= gradient_structure::get()->RETURN_ARRAYS_SIZE; ++i)
  {
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    v1 = i + 1;
    count += 1;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    grad_stack_entry* ptr = gradient_structure::get()->GRAD_STACK1->ptr;
    dvariable result = ldexp(v1, i);
    ASSERT_TRUE(ptr->func == default_evaluation);
    dvariable* return_ptr = gradient_structure::get()->RETURN_PTR;
    ASSERT_TRUE(ptr->dep_addr == &(return_ptr->v->x));
    ASSERT_TRUE(ptr->ind_addr1 == &(v1.v->x));
    ASSERT_DOUBLE_EQ(ptr->mult1, std::pow(2.0, static_cast<double>(i)));
    ASSERT_TRUE(ptr->ind_addr2 == NULL);
    ASSERT_DOUBLE_EQ(ptr->mult2, 0.0);
    count += 2;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    ASSERT_DOUBLE_EQ(value(result), std::ldexp(static_cast<double>(i + 1), i));
    if (i == 70)
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
    else
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][i]);
  }
}
TEST_F(test_gradient_structure, return_arrays_ldexp_negative)
{
  gradient_structure gs;

  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  dvariable v1;
  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  ASSERT_EQ(gradient_structure::get()->RETURN_ARRAYS_PTR, 0);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
  ASSERT_TRUE(gradient_structure::get()->MAX_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][69]);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == gradient_structure::get()->RETURN_PTR);

  int count = 0;
  for (int i = 1; i <= gradient_structure::get()->RETURN_ARRAYS_SIZE; ++i)
  {
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    v1 = -i - 1;
    count += 1;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    grad_stack_entry* ptr = gradient_structure::get()->GRAD_STACK1->ptr;
    dvariable result = ldexp(v1, -i);
    ASSERT_TRUE(ptr->func == default_evaluation);
    dvariable* return_ptr = gradient_structure::get()->RETURN_PTR;
    ASSERT_TRUE(ptr->dep_addr == &(return_ptr->v->x));
    ASSERT_TRUE(ptr->ind_addr1 == &(v1.v->x));
    ASSERT_DOUBLE_EQ(ptr->mult1, std::pow(2.0, static_cast<double>(-i)));
    ASSERT_TRUE(ptr->ind_addr2 == NULL);
    ASSERT_DOUBLE_EQ(ptr->mult2, 0.0);
    count += 2;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    ASSERT_DOUBLE_EQ(value(result), std::ldexp(static_cast<double>(-i - 1), -i));
    if (i == 70)
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
    else
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][i]);
  }
}
TEST_F(test_gradient_structure, return_arrays_tan_positive)
{
  gradient_structure gs;

  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  dvariable v1;
  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  ASSERT_EQ(gradient_structure::get()->RETURN_ARRAYS_PTR, 0);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
  ASSERT_TRUE(gradient_structure::get()->MAX_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][69]);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == gradient_structure::get()->RETURN_PTR);

  int count = 0;
  for (int i = 1; i <= gradient_structure::get()->RETURN_ARRAYS_SIZE; ++i)
  {
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    double arg = 0.01 * (i + 1);
    v1 = arg;
    count += 1;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    grad_stack_entry* ptr = gradient_structure::get()->GRAD_STACK1->ptr;
    dvariable result = tan(v1);
    ASSERT_TRUE(ptr->func == default_evaluation);
    dvariable* return_ptr = gradient_structure::get()->RETURN_PTR;
    ASSERT_TRUE(ptr->dep_addr == &(return_ptr->v->x));
    ASSERT_TRUE(ptr->ind_addr1 == &(v1.v->x));
    ASSERT_DOUBLE_EQ(ptr->mult1, 1.0 + std::tan(arg) * std::tan(arg));
    ASSERT_TRUE(ptr->ind_addr2 == NULL);
    ASSERT_DOUBLE_EQ(ptr->mult2, 0.0);
    count += 2;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    ASSERT_DOUBLE_EQ(value(result), std::tan(arg));
    if (i == 70)
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
    else
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][i]);
  }
}
TEST_F(test_gradient_structure, return_arrays_tan_negative)
{
  gradient_structure gs;

  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  dvariable v1;
  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  ASSERT_EQ(gradient_structure::get()->RETURN_ARRAYS_PTR, 0);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
  ASSERT_TRUE(gradient_structure::get()->MAX_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][69]);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == gradient_structure::get()->RETURN_PTR);

  int count = 0;
  for (int i = 1; i <= gradient_structure::get()->RETURN_ARRAYS_SIZE; ++i)
  {
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    double arg = -0.01 * (i + 1);
    v1 = arg;
    count += 1;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    grad_stack_entry* ptr = gradient_structure::get()->GRAD_STACK1->ptr;
    dvariable result = tan(v1);
    ASSERT_TRUE(ptr->func == default_evaluation);
    dvariable* return_ptr = gradient_structure::get()->RETURN_PTR;
    ASSERT_TRUE(ptr->dep_addr == &(return_ptr->v->x));
    ASSERT_TRUE(ptr->ind_addr1 == &(v1.v->x));
    ASSERT_DOUBLE_EQ(ptr->mult1, 1.0 + std::tan(arg) * std::tan(arg));
    ASSERT_TRUE(ptr->ind_addr2 == NULL);
    ASSERT_DOUBLE_EQ(ptr->mult2, 0.0);
    count += 2;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    ASSERT_DOUBLE_EQ(value(result), std::tan(arg));
    if (i == 70)
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
    else
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][i]);
  }
}
TEST_F(test_gradient_structure, return_arrays_tanh_positive)
{
  gradient_structure gs;

  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  dvariable v1;
  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  ASSERT_EQ(gradient_structure::get()->RETURN_ARRAYS_PTR, 0);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
  ASSERT_TRUE(gradient_structure::get()->MAX_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][69]);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == gradient_structure::get()->RETURN_PTR);

  int count = 0;
  for (int i = 1; i <= gradient_structure::get()->RETURN_ARRAYS_SIZE; ++i)
  {
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    double arg = static_cast<double>(i + 1);
    v1 = arg;
    count += 1;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    grad_stack_entry* ptr = gradient_structure::get()->GRAD_STACK1->ptr;
    dvariable result = tanh(v1);
    ASSERT_TRUE(ptr->func == default_evaluation);
    dvariable* return_ptr = gradient_structure::get()->RETURN_PTR;
    ASSERT_TRUE(ptr->dep_addr == &(return_ptr->v->x));
    ASSERT_TRUE(ptr->ind_addr1 == &(v1.v->x));
    ASSERT_DOUBLE_EQ(ptr->mult1, 1.0 - std::tanh(arg) * std::tanh(arg));
    ASSERT_TRUE(ptr->ind_addr2 == NULL);
    ASSERT_DOUBLE_EQ(ptr->mult2, 0.0);
    count += 2;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    ASSERT_DOUBLE_EQ(value(result), std::tanh(arg));
    if (i == 70)
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
    else
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][i]);
  }
}
TEST_F(test_gradient_structure, return_arrays_tanh_negative)
{
  gradient_structure gs;

  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  dvariable v1;
  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  ASSERT_EQ(gradient_structure::get()->RETURN_ARRAYS_PTR, 0);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
  ASSERT_TRUE(gradient_structure::get()->MAX_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][69]);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == gradient_structure::get()->RETURN_PTR);

  int count = 0;
  for (int i = 1; i <= gradient_structure::get()->RETURN_ARRAYS_SIZE; ++i)
  {
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    double arg = -1.0 * static_cast<double>(i + 1);
    v1 = arg;
    count += 1;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    grad_stack_entry* ptr = gradient_structure::get()->GRAD_STACK1->ptr;
    dvariable result = tanh(v1);
    ASSERT_TRUE(ptr->func == default_evaluation);
    dvariable* return_ptr = gradient_structure::get()->RETURN_PTR;
    ASSERT_TRUE(ptr->dep_addr == &(return_ptr->v->x));
    ASSERT_TRUE(ptr->ind_addr1 == &(v1.v->x));
    ASSERT_DOUBLE_EQ(ptr->mult1, 1.0 - std::tanh(arg) * std::tanh(arg));
    ASSERT_TRUE(ptr->ind_addr2 == NULL);
    ASSERT_DOUBLE_EQ(ptr->mult2, 0.0);
    count += 2;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    ASSERT_DOUBLE_EQ(value(result), std::tanh(arg));
    if (i == 70)
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
    else
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][i]);
  }
}
TEST_F(test_gradient_structure, return_arrays_acos_positive)
{
  gradient_structure gs;

  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  dvariable v1;
  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  ASSERT_EQ(gradient_structure::get()->RETURN_ARRAYS_PTR, 0);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
  ASSERT_TRUE(gradient_structure::get()->MAX_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][69]);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == gradient_structure::get()->RETURN_PTR);

  int count = 0;
  for (int i = 1; i <= gradient_structure::get()->RETURN_ARRAYS_SIZE; ++i)
  {
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    double arg = 0.001 * static_cast<double>(i + 1);
    v1 = arg;
    count += 1;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    grad_stack_entry* ptr = gradient_structure::get()->GRAD_STACK1->ptr;
    dvariable result = acos(v1);
    ASSERT_TRUE(ptr->func == default_evaluation);
    dvariable* return_ptr = gradient_structure::get()->RETURN_PTR;
    ASSERT_TRUE(ptr->dep_addr == &(return_ptr->v->x));
    ASSERT_TRUE(ptr->ind_addr1 == &(v1.v->x));
    ASSERT_DOUBLE_EQ(ptr->mult1, -1.0 / std::sqrt(1.0 - arg * arg));
    ASSERT_TRUE(ptr->ind_addr2 == NULL);
    ASSERT_DOUBLE_EQ(ptr->mult2, 0.0);
    count += 2;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    ASSERT_DOUBLE_EQ(value(result), std::acos(arg));
    if (i == 70)
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
    else
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][i]);
  }
}
TEST_F(test_gradient_structure, return_arrays_acos_negative)
{
  gradient_structure gs;

  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  dvariable v1;
  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  ASSERT_EQ(gradient_structure::get()->RETURN_ARRAYS_PTR, 0);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
  ASSERT_TRUE(gradient_structure::get()->MAX_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][69]);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == gradient_structure::get()->RETURN_PTR);

  int count = 0;
  for (int i = 1; i <= gradient_structure::get()->RETURN_ARRAYS_SIZE; ++i)
  {
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    double arg = -0.001 * static_cast<double>(i + 1);
    v1 = arg;
    count += 1;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    grad_stack_entry* ptr = gradient_structure::get()->GRAD_STACK1->ptr;
    dvariable result = acos(v1);
    ASSERT_TRUE(ptr->func == default_evaluation);
    dvariable* return_ptr = gradient_structure::get()->RETURN_PTR;
    ASSERT_TRUE(ptr->dep_addr == &(return_ptr->v->x));
    ASSERT_TRUE(ptr->ind_addr1 == &(v1.v->x));
    ASSERT_DOUBLE_EQ(ptr->mult1, -1.0 / std::sqrt(1.0 - arg * arg));
    ASSERT_TRUE(ptr->ind_addr2 == NULL);
    ASSERT_DOUBLE_EQ(ptr->mult2, 0.0);
    count += 2;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    ASSERT_DOUBLE_EQ(value(result), std::acos(arg));
    if (i == 70)
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
    else
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][i]);
  }
}
TEST_F(test_gradient_structure, return_arrays_asin_positive)
{
  gradient_structure gs;

  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  dvariable v1;
  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  ASSERT_EQ(gradient_structure::get()->RETURN_ARRAYS_PTR, 0);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
  ASSERT_TRUE(gradient_structure::get()->MAX_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][69]);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == gradient_structure::get()->RETURN_PTR);

  int count = 0;
  for (int i = 1; i <= gradient_structure::get()->RETURN_ARRAYS_SIZE; ++i)
  {
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    double arg = 0.001 * static_cast<double>(i + 1);
    v1 = arg;
    count += 1;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    grad_stack_entry* ptr = gradient_structure::get()->GRAD_STACK1->ptr;
    dvariable result = asin(v1);
    ASSERT_TRUE(ptr->func == default_evaluation);
    dvariable* return_ptr = gradient_structure::get()->RETURN_PTR;
    ASSERT_TRUE(ptr->dep_addr == &(return_ptr->v->x));
    ASSERT_TRUE(ptr->ind_addr1 == &(v1.v->x));
    ASSERT_DOUBLE_EQ(ptr->mult1, 1.0 / std::sqrt(1.0 - arg * arg));
    ASSERT_TRUE(ptr->ind_addr2 == NULL);
    ASSERT_DOUBLE_EQ(ptr->mult2, 0.0);
    count += 2;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    ASSERT_DOUBLE_EQ(value(result), std::asin(arg));
    if (i == 70)
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
    else
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][i]);
  }
}
TEST_F(test_gradient_structure, return_arrays_asin_negative)
{
  gradient_structure gs;

  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  dvariable v1;
  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  ASSERT_EQ(gradient_structure::get()->RETURN_ARRAYS_PTR, 0);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
  ASSERT_TRUE(gradient_structure::get()->MAX_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][69]);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == gradient_structure::get()->RETURN_PTR);

  int count = 0;
  for (int i = 1; i <= gradient_structure::get()->RETURN_ARRAYS_SIZE; ++i)
  {
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    double arg = -0.001 * static_cast<double>(i + 1);
    v1 = arg;
    count += 1;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    grad_stack_entry* ptr = gradient_structure::get()->GRAD_STACK1->ptr;
    dvariable result = asin(v1);
    ASSERT_TRUE(ptr->func == default_evaluation);
    dvariable* return_ptr = gradient_structure::get()->RETURN_PTR;
    ASSERT_TRUE(ptr->dep_addr == &(return_ptr->v->x));
    ASSERT_TRUE(ptr->ind_addr1 == &(v1.v->x));
    ASSERT_DOUBLE_EQ(ptr->mult1, 1.0 / std::sqrt(1.0 - arg * arg));
    ASSERT_TRUE(ptr->ind_addr2 == NULL);
    ASSERT_DOUBLE_EQ(ptr->mult2, 0.0);
    count += 2;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    ASSERT_DOUBLE_EQ(value(result), std::asin(arg));
    if (i == 70)
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
    else
      ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][i]);
  }
}
TEST_F(test_gradient_structure, return_arrays_cumd_norm)
{
  gradient_structure gs;

  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  dvariable v1;
  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  ASSERT_EQ(gradient_structure::get()->RETURN_ARRAYS_PTR, 0);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
  ASSERT_TRUE(gradient_structure::get()->MAX_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][69]);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == gradient_structure::get()->RETURN_PTR);

  int count = 0;
  int i = 2;
  {
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    double arg = static_cast<double>(i + 1);
    v1 = arg;
    count += 1;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    grad_stack_entry* ptr = gradient_structure::get()->GRAD_STACK1->ptr;
    dvariable result = cumd_norm(v1);
    ASSERT_TRUE(ptr->func == default_evaluation);
    dvariable* return_ptr = gradient_structure::get()->RETURN_PTR;
    ASSERT_TRUE(ptr->dep_addr == &(return_ptr->v->x));
    ASSERT_TRUE(ptr->ind_addr1 == &(v1.v->x));
    ASSERT_DOUBLE_EQ(ptr->mult1, 0.0044318437651152988);
    ASSERT_TRUE(ptr->ind_addr2 == NULL);
    ASSERT_DOUBLE_EQ(ptr->mult2, 0.0);
    count += 2;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    ASSERT_DOUBLE_EQ(value(result), 0.99865003277776965);
    ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][1]);
  }
}
TEST_F(test_gradient_structure, return_arrays_cumd_norm_negative)
{
  gradient_structure gs;

  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  dvariable v1;
  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  ASSERT_EQ(gradient_structure::get()->RETURN_ARRAYS_PTR, 0);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
  ASSERT_TRUE(gradient_structure::get()->MAX_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][69]);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == gradient_structure::get()->RETURN_PTR);

  int count = 0;
  int i = 2;
  {
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    double arg = -1.0 * static_cast<double>(i + 1);
    v1 = arg;
    count += 1;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    grad_stack_entry* ptr = gradient_structure::get()->GRAD_STACK1->ptr;
    dvariable result = cumd_norm(v1);
    ASSERT_TRUE(ptr->func == default_evaluation);
    dvariable* return_ptr = gradient_structure::get()->RETURN_PTR;
    ASSERT_TRUE(ptr->dep_addr == &(return_ptr->v->x));
    ASSERT_TRUE(ptr->ind_addr1 == &(v1.v->x));
    ASSERT_DOUBLE_EQ(ptr->mult1, 0.0044318437651152988);
    ASSERT_TRUE(ptr->ind_addr2 == NULL);
    ASSERT_DOUBLE_EQ(ptr->mult2, 0.0);
    count += 2;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    ASSERT_DOUBLE_EQ(value(result), 0.0013499672222303427);
    ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][1]);
  }
}
TEST_F(test_gradient_structure, return_arrays_bounded_cumd_norm)
{
  gradient_structure gs;

  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  dvariable v1;
  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  ASSERT_EQ(gradient_structure::get()->RETURN_ARRAYS_PTR, 0);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
  ASSERT_TRUE(gradient_structure::get()->MAX_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][69]);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == gradient_structure::get()->RETURN_PTR);

  int count = 0;
  int i = 2;
  {
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    double arg = static_cast<double>(i + 1);
    v1 = arg;
    count += 1;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    grad_stack_entry* ptr = gradient_structure::get()->GRAD_STACK1->ptr;
    dvariable result = bounded_cumd_norm(v1, 0.5);
    ASSERT_TRUE(ptr->func == default_evaluation);
    dvariable* return_ptr = gradient_structure::get()->RETURN_PTR;
    ASSERT_TRUE(ptr->dep_addr == &(return_ptr->v->x));
    ASSERT_TRUE(ptr->ind_addr1 == &(v1.v->x));
    ASSERT_DOUBLE_EQ(ptr->mult1, 0.0022159218825576494);
    ASSERT_TRUE(ptr->ind_addr2 == NULL);
    ASSERT_DOUBLE_EQ(ptr->mult2, 0.0);
    count += 2;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    ASSERT_DOUBLE_EQ(value(result), 0.74932501638888482);
    ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][1]);
  }
}
TEST_F(test_gradient_structure, return_arrays_bounded_cumd_norm_negative)
{
  gradient_structure gs;

  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  dvariable v1;
  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  ASSERT_EQ(gradient_structure::get()->RETURN_ARRAYS_PTR, 0);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
  ASSERT_TRUE(gradient_structure::get()->MAX_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][69]);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == gradient_structure::get()->RETURN_PTR);

  int count = 0;
  int i = 2;
  {
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    double arg = -1.0 * static_cast<double>(i + 1);
    v1 = arg;
    count += 1;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    grad_stack_entry* ptr = gradient_structure::get()->GRAD_STACK1->ptr;
    dvariable result = bounded_cumd_norm(v1, 0.5);
    ASSERT_TRUE(ptr->func == default_evaluation);
    dvariable* return_ptr = gradient_structure::get()->RETURN_PTR;
    ASSERT_TRUE(ptr->dep_addr == &(return_ptr->v->x));
    ASSERT_TRUE(ptr->ind_addr1 == &(v1.v->x));
    ASSERT_DOUBLE_EQ(ptr->mult1, 0.0022159218825576494);
    ASSERT_TRUE(ptr->ind_addr2 == NULL);
    ASSERT_DOUBLE_EQ(ptr->mult2, 0.0);
    count += 2;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    ASSERT_DOUBLE_EQ(value(result), 0.25067498361111518);
    ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][1]);
  }
}
TEST_F(test_gradient_structure, return_arrays_inv_cumd_norm_inner_0)
{
  gradient_structure gs;

  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  dvariable v1;
  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  ASSERT_EQ(gradient_structure::get()->RETURN_ARRAYS_PTR, 0);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
  ASSERT_TRUE(gradient_structure::get()->MAX_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][69]);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == gradient_structure::get()->RETURN_PTR);

  int count = 0;
  int i = 2;
  {
    dvariable inv_cumd_norm_inner(const prevariable& x);

    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    double arg = 0.0;
    v1 = arg;
    count += 1;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    grad_stack_entry* ptr = gradient_structure::get()->GRAD_STACK1->ptr;
    dvariable result = inv_cumd_norm_inner(v1);
    ASSERT_DOUBLE_EQ(value(result), 0.0);
    //ASSERT_TRUE(ptr->func == NULL);
    //dvariable* return_ptr = gradient_structure::RETURN_PTR;
    //ASSERT_TRUE(ptr->dep_addr == NULL);
    //ASSERT_TRUE(ptr->ind_addr1 == NULL);
    //ASSERT_DOUBLE_EQ(ptr->mult1, 0.0);
    //ASSERT_TRUE(ptr->ind_addr2 == NULL);
    //ASSERT_DOUBLE_EQ(ptr->mult2, 0.0);
    count += 1;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][1]);
  }
}
TEST_F(test_gradient_structure, return_arrays_inv_cumd_norm_inner_1)
{
  gradient_structure gs;

  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  dvariable v1;
  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  ASSERT_EQ(gradient_structure::get()->RETURN_ARRAYS_PTR, 0);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
  ASSERT_TRUE(gradient_structure::get()->MAX_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][69]);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == gradient_structure::get()->RETURN_PTR);

  int count = 0;
  int i = 2;
  {
    dvariable inv_cumd_norm_inner(const prevariable& x);

    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    double arg = 1.0;
    v1 = arg;
    count += 1;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    grad_stack_entry* ptr = gradient_structure::get()->GRAD_STACK1->ptr;
    dvariable result = inv_cumd_norm_inner(v1);
    ASSERT_DOUBLE_EQ(value(result), 0.0);
    //ASSERT_TRUE(ptr->func == NULL);
    //dvariable* return_ptr = gradient_structure::RETURN_PTR;
    //ASSERT_TRUE(ptr->dep_addr == NULL);
    //ASSERT_TRUE(ptr->ind_addr1 == NULL);
    //ASSERT_DOUBLE_EQ(ptr->mult1, 0.0);
    //ASSERT_TRUE(ptr->ind_addr2 == NULL);
    //ASSERT_DOUBLE_EQ(ptr->mult2, 0.0);
    count += 1;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][1]);
  }
}
TEST_F(test_gradient_structure, return_arrays_inv_cumd_norm_inner_05)
{
  gradient_structure gs;

  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  dvariable v1;
  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  ASSERT_EQ(gradient_structure::get()->RETURN_ARRAYS_PTR, 0);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
  ASSERT_TRUE(gradient_structure::get()->MAX_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][69]);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == gradient_structure::get()->RETURN_PTR);

  int count = 0;
  int i = 2;
  {
    dvariable inv_cumd_norm_inner(const prevariable& x);

    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    double arg = 0.5;
    v1 = arg;
    count += 1;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    grad_stack_entry* ptr = gradient_structure::get()->GRAD_STACK1->ptr;
    dvariable result = inv_cumd_norm_inner(v1);
    ASSERT_DOUBLE_EQ(value(result), 1.0100667569012955e-07);
    ASSERT_TRUE(ptr->func == default_evaluation);
    dvariable* return_ptr = gradient_structure::get()->RETURN_PTR;
    ASSERT_TRUE(ptr->dep_addr == &(return_ptr->v->x));
    ASSERT_TRUE(ptr->ind_addr1 == &(v1.v->x));
    ASSERT_DOUBLE_EQ(ptr->mult1, 2.4991770754639897);
    ASSERT_TRUE(ptr->ind_addr2 == NULL);
    ASSERT_DOUBLE_EQ(ptr->mult2, 0.0);
    count += 2;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][1]);
  }
}
TEST_F(test_gradient_structure, return_arrays_inv_cumd_norm_inner_07)
{
  gradient_structure gs;

  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  dvariable v1;
  ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), 0);
  ASSERT_EQ(gradient_structure::get()->RETURN_ARRAYS_PTR, 0);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][0]);
  ASSERT_TRUE(gradient_structure::get()->MAX_RETURN == &gradient_structure::get()->RETURN_ARRAYS[0][69]);
  ASSERT_TRUE(gradient_structure::get()->MIN_RETURN == gradient_structure::get()->RETURN_PTR);

  int count = 0;
  int i = 2;
  {
    dvariable inv_cumd_norm_inner(const prevariable& x);

    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    double arg = 0.7;
    v1 = arg;
    count += 1;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    grad_stack_entry* ptr = gradient_structure::get()->GRAD_STACK1->ptr;
    dvariable result = inv_cumd_norm_inner(v1);
    ASSERT_DOUBLE_EQ(value(result), 0.52400187038267987);
    ASSERT_TRUE(ptr->func == default_evaluation);
    dvariable* return_ptr = gradient_structure::get()->RETURN_PTR;
    ASSERT_TRUE(ptr->dep_addr == &(return_ptr->v->x));
    ASSERT_TRUE(ptr->ind_addr1 == &(v1.v->x));
    ASSERT_DOUBLE_EQ(ptr->mult1, 2.8775901861557482);
    ASSERT_TRUE(ptr->ind_addr2 == NULL);
    ASSERT_DOUBLE_EQ(ptr->mult2, 0.0);
    count += 2;
    ASSERT_EQ(gradient_structure::get()->GRAD_STACK1->total(), count);
    ASSERT_TRUE(gradient_structure::get()->RETURN_PTR == &gradient_structure::get()->RETURN_ARRAYS[0][1]);
  }
}
