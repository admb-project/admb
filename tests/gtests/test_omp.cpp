#include <gtest/gtest.h>

#ifdef _OPENMP
#include <omp.h>
#include <fvar.hpp>
#include <admodel.h>

class test_omp: public ::testing::Test {};

TEST_F(test_omp, hello_world)
{
  #pragma omp parallel
  printf("hello_world: thread %d, nthreads %d\n", omp_get_thread_num(), omp_get_num_threads());
}
/*
TEST_F(test_omp, dvector)
{
  gradient_structure gs;

  #pragma omp parallel
  {
    dlist list;
    gradient_structure::GRAD_LIST = &list;
    dvector v;
    gradient_structure::GRAD_LIST = NULL;
  }
}
TEST_F(test_omp, objective_function_value)
{
  gradient_structure gs;

  #pragma omp parallel
  {
    dlist list;
    gradient_structure::GRAD_LIST = &list;
    objective_function_value ofv;
    gradient_structure::GRAD_LIST = NULL;
  }
}
TEST_F(test_omp, dvariable)
{
  gradient_structure gs;

  intptr_t addresses[8];
  #pragma omp parallel num_threads(8)
  {
    dlist list;
    gradient_structure::GRAD_LIST = &list;
    #pragma omp for
    for (int i = 0; i < 8; i++)
    {
      dvariable v;
      addresses[i] = (intptr_t)v.v ;
    }
    gradient_structure::GRAD_LIST = NULL;
  }
  for (int i = 0; i < 8; i++)
  {
    intptr_t ai = addresses[i];
    for (int j = i + 1; j < 8; j++)
    {
      intptr_t aj = addresses[j];
      ASSERT_NE(ai, aj);
    }
  }
}
*/
/*
TEST_F(test_omp, memblock_adjust)
{
  gradient_structure::ARRAY_MEMBLOCK_SIZE = 1500;
  void* mem = (void*)malloc(gradient_structure::ARRAY_MEMBLOCK_SIZE);

  ASSERT_TRUE(gradient_structure::ARRAY_MEMBLOCK_BASE == NULL);
  gradient_structure::ARRAY_MEMBLOCK_BASE = mem;
  ASSERT_EQ(gradient_structure::ARRAY_MEMBLOCK_BASE.ptr, mem);

  const size_t adjustment = (8 -((size_t)gradient_structure::ARRAY_MEMBLOCK_BASE.ptr) % 8) % 8;
  ASSERT_EQ(adjustment, 0);
  gradient_structure::ARRAY_MEMBLOCK_BASE.adjust(adjustment);
  ASSERT_EQ(gradient_structure::ARRAY_MEMBLOCK_BASE.ptr, mem);

  free(mem);
  mem = NULL;

  gradient_structure::ARRAY_MEMBLOCK_BASE.ptr = NULL;
  ASSERT_TRUE(gradient_structure::ARRAY_MEMBLOCK_BASE.ptr == NULL);
}
TEST_F(test_omp, arr_new_case3)
{
  gradient_structure::ARRAY_MEMBLOCK_SIZE = 1500;
  void* mem = (void*)malloc(gradient_structure::ARRAY_MEMBLOCK_SIZE);

  ASSERT_TRUE(gradient_structure::ARRAY_MEMBLOCK_BASE == NULL);
  gradient_structure::ARRAY_MEMBLOCK_BASE = mem;
  ASSERT_EQ(gradient_structure::ARRAY_MEMBLOCK_BASE.ptr, mem);

  const size_t adjustment = (8 -((size_t)gradient_structure::ARRAY_MEMBLOCK_BASE.ptr) % 8) % 8;
  ASSERT_EQ(adjustment, 0);
  gradient_structure::ARRAY_MEMBLOCK_BASE.adjust(adjustment);
  ASSERT_EQ(gradient_structure::ARRAY_MEMBLOCK_BASE.ptr, mem);

  unsigned long int offset = 10;
  char* cptr = gradient_structure::ARRAY_MEMBLOCK_BASE + offset;
  ASSERT_EQ(gradient_structure::ARRAY_MEMBLOCK_BASE.ptr + offset, cptr);

  ASSERT_TRUE(gradient_structure::ARR_LIST1 == NULL);

  {
    arr_list local_arr_list;
    gradient_structure::ARR_LIST1 = &local_arr_list;
    ASSERT_TRUE(gradient_structure::ARR_LIST1 != NULL);

    gradient_structure::ARR_LIST1 = NULL;
  }

  free(mem);
  mem = NULL;

  gradient_structure::ARRAY_MEMBLOCK_BASE.ptr = NULL;
  ASSERT_TRUE(gradient_structure::ARRAY_MEMBLOCK_BASE.ptr == NULL);
}
TEST_F(test_omp, arr_new_free)
{
  intptr_t addresses[8];
  intptr_t addresses2[8];

  gradient_structure gs;
  ASSERT_TRUE(gradient_structure::ARRAY_MEMBLOCK_BASE != NULL);
  intptr_t start = (intptr_t)&gradient_structure::ARRAY_MEMBLOCK_BASE;
  #pragma omp parallel num_threads(8)
  {
    double_and_int* p = arr_new(8);
    const int id = omp_get_thread_num();
    addresses[id] = (intptr_t)p;
    addresses2[id] = (intptr_t)&gradient_structure::ARRAY_MEMBLOCK_BASE;
  }
  for (int i = 0; i < 8; i++)
  {
    intptr_t ai = addresses[i];
cout << ai << endl;
    for (int j = i + 1; j < 8; j++)
    {
      intptr_t aj = addresses[j];
      //If equal race condition
      //ASSERT_NE(ai, aj);
    }
  }
  for (int i = 0; i < 8; i++)
  {
    //This should be NE
    ASSERT_EQ(start, addresses2[i]);
  }
}
*/
/*
TEST_F(test_omp, dvar_vector_arr_new)
{
  gradient_structure gs;

  intptr_t addresses[8];
  #pragma omp parallel num_threads(8)
  {
    gradient_structure::ARRAY_MEMBLOCK_BASE = (void*)malloc(ARRAY_MEMBLOCK_SIZE);
    arr_list local_arr_list;
    gradient_structure::ARR_LIST1 = &local_arr_list;
    #pragma omp for
    for (int i = 0; i < 8; i++)
    {
      double_and_int* p = arr_new(8);
      addresses[i] = (intptr_t)p;
    }
    gradient_structure::ARR_LIST1 = NULL;
    gradient_structure::ARRAY_MEMBLOCK_BASE.free();
  }
  for (int i = 0; i < 8; i++)
  {
    intptr_t ai = addresses[i];
    for (int j = i + 1; j < 8; j++)
    {
      intptr_t aj = addresses[j];
      ASSERT_NE(ai, aj);
    }
  }
}
*/
#endif
