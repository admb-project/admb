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
TEST_F(test_size_count, dvar_matrix_null)
{
  gradient_structure gs;
  dvar_matrix varmat;

  ASSERT_EQ(0, size_count(varmat));
}
TEST_F(test_size_count, dvar_matrix_allocated)
{
  gradient_structure gs;
  dvar_matrix varmat(-5, 5, 2, 3);

  ASSERT_EQ(22, size_count(varmat));
}
TEST_F(test_size_count, dvar3_array_null)
{
  gradient_structure gs;
  dvar3_array var3arr;

  ASSERT_EQ(0, size_count(var3arr));
}
TEST_F(test_size_count, dvar3_array_allocated)
{
  gradient_structure gs;
  dvar3_array var3arr(1, 2, -5, 5, 2, 3);

  ASSERT_EQ(44, size_count(var3arr));
}
TEST_F(test_size_count, dvar4_array_null)
{
  gradient_structure gs;
  dvar4_array var4arr;

  ASSERT_EQ(0, size_count(var4arr));
}
TEST_F(test_size_count, dvar4_array_allocated)
{
  gradient_structure gs;
  dvar4_array var4arr(0, 3, 1, 2, -5, 5, 2, 3);

  ASSERT_EQ(176, size_count(var4arr));
}
TEST_F(test_size_count, d4_array_null)
{
  gradient_structure gs;
  d4_array d4arr;

  ASSERT_EQ(0, size_count(d4arr));
}
TEST_F(test_size_count, d4_array_allocated)
{
  gradient_structure gs;
  d4_array d4arr(0, 3, 1, 2, -5, 5, 2, 3);

  ASSERT_EQ(176, size_count(d4arr));
}
