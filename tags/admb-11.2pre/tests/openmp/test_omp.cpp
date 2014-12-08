#include <gtest/gtest.h>

#ifdef _OPENMP
#include <omp.h>
#endif

class test_omp: public ::testing::Test {};

TEST_F(test_omp, hello_world)
{
  #pragma omp parallel
  printf("hello_world: thread %d, nthreads %d\n", omp_get_thread_num(), omp_get_num_threads());
}
