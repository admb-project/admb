#include <gtest/gtest.h>
#include <fvar.hpp>

class test_sub_unallocated: public ::testing::Test {};

TEST_F(test_sub_unallocated, dvar_vector)
{
  gradient_structure gs;

  dvar_vector varvec;
  ASSERT_TRUE(sub_unallocated(varvec));
  varvec.allocate(1, 4);
  ASSERT_FALSE(sub_unallocated(varvec));
}
TEST_F(test_sub_unallocated, dvector)
{
  gradient_structure gs;

  dvector v;
  ASSERT_TRUE(sub_unallocated(v));
  v.allocate(1, 4);
  ASSERT_FALSE(sub_unallocated(v));
}
TEST_F(test_sub_unallocated, ivector)
{
  gradient_structure gs;

  ivector v;
  ASSERT_TRUE(sub_unallocated(v));
  v.allocate(1, 4);
  ASSERT_FALSE(sub_unallocated(v));
}
TEST_F(test_sub_unallocated, dvar_matrix)
{
  gradient_structure gs;

  dvar_matrix varmat;
  ASSERT_TRUE(sub_unallocated(varmat));
  varmat.allocate(1, 4, 1, 4);
  ASSERT_FALSE(sub_unallocated(varmat));
}
TEST_F(test_sub_unallocated, dmatrix)
{
  gradient_structure gs;

  dmatrix m;
  ASSERT_TRUE(sub_unallocated(m));
  m.allocate(1, 4, 1, 4);
  ASSERT_FALSE(sub_unallocated(m));
}
TEST_F(test_sub_unallocated, imatrix)
{
  gradient_structure gs;

  imatrix m;
  ASSERT_TRUE(sub_unallocated(m));
  m.allocate(1, 4, 1, 4);
  ASSERT_FALSE(sub_unallocated(m));
}
TEST_F(test_sub_unallocated, dvar_matrix1)
{
  gradient_structure gs;

  dvar_matrix varmat;
  ASSERT_TRUE(sub_unallocated(varmat));
  varmat.allocate(1, 4);
  ASSERT_TRUE(sub_unallocated(varmat));
  varmat(2).allocate(1, 4);
  varmat(3).allocate(1, 4);
  varmat(4).allocate(1, 4);
  ASSERT_TRUE(sub_unallocated(varmat));
  varmat(1).allocate(1, 4);
  ASSERT_FALSE(sub_unallocated(varmat));
}
TEST_F(test_sub_unallocated, dvar_matrix2)
{
  gradient_structure gs;

  dvar_matrix varmat;
  ASSERT_TRUE(sub_unallocated(varmat));
  varmat.allocate(1, 4);
  ASSERT_TRUE(sub_unallocated(varmat));
  varmat(1).allocate(1, 4);
  varmat(3).allocate(1, 4);
  varmat(4).allocate(1, 4);
  ASSERT_TRUE(sub_unallocated(varmat));
  varmat(2).allocate(1, 4);
  ASSERT_FALSE(sub_unallocated(varmat));
}
TEST_F(test_sub_unallocated, dvar_matrix3)
{
  gradient_structure gs;

  dvar_matrix varmat;
  ASSERT_TRUE(sub_unallocated(varmat));
  varmat.allocate(1, 4);
  ASSERT_TRUE(sub_unallocated(varmat));
  varmat(1).allocate(1, 4);
  varmat(2).allocate(1, 4);
  varmat(4).allocate(1, 4);
  ASSERT_TRUE(sub_unallocated(varmat));
  varmat(3).allocate(1, 4);
  ASSERT_FALSE(sub_unallocated(varmat));
}
TEST_F(test_sub_unallocated, dvar_matrix4)
{
  gradient_structure gs;

  dvar_matrix varmat;
  ASSERT_TRUE(sub_unallocated(varmat));
  varmat.allocate(1, 4);
  ASSERT_TRUE(sub_unallocated(varmat));
  varmat(1).allocate(1, 4);
  varmat(2).allocate(1, 4);
  varmat(3).allocate(1, 4);
  ASSERT_TRUE(sub_unallocated(varmat));
  varmat(4).allocate(1, 4);
  ASSERT_FALSE(sub_unallocated(varmat));
}
TEST_F(test_sub_unallocated, dvar3_array)
{
  gradient_structure gs;

  dvar3_array arr3;
  ASSERT_TRUE(sub_unallocated(arr3));
  arr3.allocate(1, 4);
  ASSERT_TRUE(sub_unallocated(arr3));
  arr3(1).allocate(1, 4);
  ASSERT_TRUE(sub_unallocated(arr3));
  arr3(2).allocate(1, 4);
  ASSERT_TRUE(sub_unallocated(arr3));
  arr3(3).allocate(1, 4);
  ASSERT_TRUE(sub_unallocated(arr3));
  arr3(4).allocate(1, 4);
  ASSERT_TRUE(sub_unallocated(arr3));
  arr3(1, 1).allocate(1, 4);
  arr3(1, 2).allocate(1, 4);
  arr3(1, 3).allocate(1, 4);
  arr3(1, 4).allocate(1, 4);
  ASSERT_TRUE(sub_unallocated(arr3));
  arr3(2, 1).allocate(1, 4);
  arr3(2, 2).allocate(1, 4);
  arr3(2, 3).allocate(1, 4);
  arr3(2, 4).allocate(1, 4);
  ASSERT_TRUE(sub_unallocated(arr3));
  arr3(3, 1).allocate(1, 4);
  arr3(3, 2).allocate(1, 4);
  arr3(3, 3).allocate(1, 4);
  arr3(3, 4).allocate(1, 4);
  ASSERT_TRUE(sub_unallocated(arr3));
  arr3(4, 1).allocate(1, 4);
  arr3(4, 2).allocate(1, 4);
  arr3(4, 3).allocate(1, 4);
  arr3(4, 4).allocate(1, 4);
  ASSERT_FALSE(sub_unallocated(arr3));

  dvar3_array arr3b(1, 4, 1, 4, 1, 4);
  ASSERT_FALSE(sub_unallocated(arr3b));
}
TEST_F(test_sub_unallocated, d3_array)
{
  gradient_structure gs;

  d3_array arr3;
  ASSERT_TRUE(sub_unallocated(arr3));
  arr3.allocate(1, 4);
  ASSERT_TRUE(sub_unallocated(arr3));
  arr3(1).allocate(1, 4);
  ASSERT_TRUE(sub_unallocated(arr3));
  arr3(2).allocate(1, 4);
  ASSERT_TRUE(sub_unallocated(arr3));
  arr3(3).allocate(1, 4);
  ASSERT_TRUE(sub_unallocated(arr3));
  arr3(4).allocate(1, 4);
  ASSERT_TRUE(sub_unallocated(arr3));
  arr3(1, 1).allocate(1, 4);
  arr3(1, 2).allocate(1, 4);
  arr3(1, 3).allocate(1, 4);
  arr3(1, 4).allocate(1, 4);
  ASSERT_TRUE(sub_unallocated(arr3));
  arr3(2, 1).allocate(1, 4);
  arr3(2, 2).allocate(1, 4);
  arr3(2, 3).allocate(1, 4);
  arr3(2, 4).allocate(1, 4);
  ASSERT_TRUE(sub_unallocated(arr3));
  arr3(3, 1).allocate(1, 4);
  arr3(3, 2).allocate(1, 4);
  arr3(3, 3).allocate(1, 4);
  arr3(3, 4).allocate(1, 4);
  ASSERT_TRUE(sub_unallocated(arr3));
  arr3(4, 1).allocate(1, 4);
  arr3(4, 2).allocate(1, 4);
  arr3(4, 3).allocate(1, 4);
  arr3(4, 4).allocate(1, 4);
  ASSERT_FALSE(sub_unallocated(arr3));

  d3_array arr3b(1, 4, 1, 4, 1, 4);
  ASSERT_FALSE(sub_unallocated(arr3b));
}
TEST_F(test_sub_unallocated, i3_array)
{
  gradient_structure gs;

  i3_array arr3;
  ASSERT_TRUE(sub_unallocated(arr3));
  arr3.allocate(1, 4);
  ASSERT_TRUE(sub_unallocated(arr3));
  arr3(1).allocate(1, 4);
  ASSERT_TRUE(sub_unallocated(arr3));
  arr3(2).allocate(1, 4);
  ASSERT_TRUE(sub_unallocated(arr3));
  arr3(3).allocate(1, 4);
  ASSERT_TRUE(sub_unallocated(arr3));
  arr3(4).allocate(1, 4);
  ASSERT_TRUE(sub_unallocated(arr3));
  arr3(1, 1).allocate(1, 4);
  arr3(1, 2).allocate(1, 4);
  arr3(1, 3).allocate(1, 4);
  arr3(1, 4).allocate(1, 4);
  ASSERT_TRUE(sub_unallocated(arr3));
  arr3(2, 1).allocate(1, 4);
  arr3(2, 2).allocate(1, 4);
  arr3(2, 3).allocate(1, 4);
  arr3(2, 4).allocate(1, 4);
  ASSERT_TRUE(sub_unallocated(arr3));
  arr3(3, 1).allocate(1, 4);
  arr3(3, 2).allocate(1, 4);
  arr3(3, 3).allocate(1, 4);
  arr3(3, 4).allocate(1, 4);
  ASSERT_TRUE(sub_unallocated(arr3));
  arr3(4, 1).allocate(1, 4);
  arr3(4, 2).allocate(1, 4);
  arr3(4, 3).allocate(1, 4);
  arr3(4, 4).allocate(1, 4);
  ASSERT_FALSE(sub_unallocated(arr3));

  i3_array arr3b(1, 4, 1, 4, 1, 4);
  ASSERT_FALSE(sub_unallocated(arr3b));
}
TEST_F(test_sub_unallocated, dvar4_array)
{
  gradient_structure gs;

  dvar4_array arr4;
  ASSERT_TRUE(sub_unallocated(arr4));
  arr4.allocate(1, 4, 1, 4, 1, 4, 1, 4);
  ASSERT_FALSE(sub_unallocated(arr4));
}
TEST_F(test_sub_unallocated, d4_array)
{
  gradient_structure gs;

  d4_array arr4;
  ASSERT_TRUE(sub_unallocated(arr4));
  arr4.allocate(1, 4, 1, 4, 1, 4, 1, 4);
  ASSERT_FALSE(sub_unallocated(arr4));
}
TEST_F(test_sub_unallocated, dvar5_array)
{
  gradient_structure gs;

  dvar5_array arr5;
  ASSERT_TRUE(sub_unallocated(arr5));
  arr5.allocate(1, 4, 1, 4, 1, 4, 1, 4, 1, 4);
  ASSERT_FALSE(sub_unallocated(arr5));
}
TEST_F(test_sub_unallocated, d5_array)
{
  gradient_structure gs;

  d5_array arr5;
  ASSERT_TRUE(sub_unallocated(arr5));
  arr5.allocate(1, 4, 1, 4, 1, 4, 1, 4, 1, 4);
  ASSERT_FALSE(sub_unallocated(arr5));
}
TEST_F(test_sub_unallocated, i4_array)
{
  gradient_structure gs;

  i4_array arr4;
  ASSERT_TRUE(sub_unallocated(arr4));
  arr4.allocate(1, 4, 1, 4, 1, 4, 1, 4);
  ASSERT_FALSE(sub_unallocated(arr4));
}
/*
TEST_F(test_sub_unallocated, i5_array)
{
  gradient_structure gs;

  i5_array arr5;
  ASSERT_TRUE(sub_unallocated(arr5));
  arr5.allocate(1, 4, 1, 4, 1, 4, 1, 4);
  ASSERT_FALSE(sub_unallocated(arr5));
}
*/
