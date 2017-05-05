#include <gtest/gtest.h>
#include <fvar.hpp>

class test_size_count: public ::testing::Test {};

TEST_F(test_size_count, dvar_vector_null)
{
  gradient_structure gs;
  dvar_vector varvec;

  ASSERT_EQ(0, size_count(varvec));
}
TEST_F(test_size_count, dvar_vector_neg5to5)
{
  gradient_structure gs;
  dvar_vector varvec(-5, 5);

  ASSERT_EQ(11, size_count(varvec));
}
