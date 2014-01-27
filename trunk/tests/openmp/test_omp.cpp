#include <gtest/gtest.h>

#ifdef _OPENMP
#include <omp.h>
#endif

class test_omp: public ::testing::Test {};

TEST_F(test_omp, example)
{
}
