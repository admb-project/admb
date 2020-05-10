#include <gtest/gtest.h>
#include "fvar.hpp"

extern "C"
{
  void test_ad_exit(const int exit_code);
}

class test_arr_link: public ::testing::Test {};

/*
TEST_F(test_arr_link, arr_remove_null)
{
  void arr_remove(arr_link** pptr);
  arr_list alist;
  ASSERT_DEATH(alist.arr_free(NULL), "Assertion");
}
TEST_F(test_arr_link, arr_remove)
{
  ad_exit=&test_ad_exit;
  arr_list alist;
  arr_link** pptr = new arr_link*[1];
  pptr[0] = NULL;
  try
  {
    alist.arr_free(pptr);
  }
  catch (const int exit_code)
  {
    delete [] pptr;
    pptr = NULL;

    const int expected_exit_code = 23;
    if (exit_code == expected_exit_code)
    {
      return;
    }
  }
  FAIL();
}
*/
TEST_F(test_arr_link, dvar_vector1to4)
{
  gradient_structure gs;

  dvar_vector v(1, 4);

  arr_link* last = gradient_structure::GRAD_STACK1->ARR_LIST1->get_last();

  ASSERT_TRUE(last->get_prev() == NULL);
  ASSERT_TRUE(last->get_next() == NULL);
  ASSERT_EQ(last->get_size(), sizeof(double_and_int) * 4);
  ASSERT_EQ(last->get_offset(), 0);
  ASSERT_EQ(last->get_status(), 1);
}
/*
TEST_F(test_arr_link, initial_state_xpool)
{
  ASSERT_TRUE(arr_link::get_xpool() == NULL);

  gradient_structure gs;

  vector_shape_pool* xpool = arr_link::get_xpool();
  ASSERT_TRUE(xpool != NULL);
  ASSERT_EQ(xpool->nvar, 0);
  ASSERT_TRUE(xpool->last_chunk == NULL);
  ASSERT_EQ(xpool->num_allocated, 0);
  ASSERT_EQ(xpool->num_chunks, 0);
  ASSERT_EQ(xpool->nelem, 0);
  ASSERT_EQ(xpool->size, sizeof(arr_link));
  ASSERT_TRUE(xpool->head == NULL);
  ASSERT_TRUE(xpool->first == NULL);

  dvar_vector v(1, 4);

  ASSERT_EQ(xpool->nvar, 0);
  ASSERT_EQ(xpool->num_allocated, 1);
  ASSERT_EQ(xpool->num_chunks, 1);
  ASSERT_EQ(xpool->size, sizeof(arr_link));
  const size_t overhead = 12 + sizeof(char*);
  const size_t chunk_size = 65000 - overhead;
  size_t expected = chunk_size / xpool->size;
  ASSERT_EQ(xpool->nelem, expected);
  ASSERT_TRUE(static_cast<void*>(xpool->last_chunk + sizeof(char*)) == static_cast<void*>(xpool->first));
  void* ptr = static_cast<void*>(xpool->last_chunk + sizeof(char*));
  dfpool::link* k = static_cast<dfpool::link*>(ptr);
  cout << k << ' ' << xpool->head << endl;
  cout << k->next << ' ' << xpool->head << endl;
  ASSERT_TRUE(k->next == xpool->head);
}
*/
