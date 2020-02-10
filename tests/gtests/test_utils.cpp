#include <gtest/gtest.h>
#include <fvar.hpp>

class test_utils: public ::testing::Test {};

TEST_F(test_utils, ranfill)
{
  double auto_rand(long int& idum, int reset);

  long idum = 5;

  double value = auto_rand(idum, -1);
  ASSERT_DOUBLE_EQ(value, 0.5);

  double value2 = auto_rand(idum, 1);
  ASSERT_DOUBLE_EQ(value2, 0.6659108996391296);

  void reinitialize_auto_rand();
  reinitialize_auto_rand();
}
TEST_F(test_utils, check_datafile_pointer)
{
  void check_datafile_pointer(void* p);

  ASSERT_THROW(check_datafile_pointer(NULL),int);
}
TEST_F(test_utils, variance)
{
  dvector data(1, 5);
  data(1) = 600;
  data(2) = 470;
  data(3) = 170;
  data(4) = 430;
  data(5) = 300;

  ASSERT_DOUBLE_EQ(21704, var(data));
}
TEST_F(test_utils, std_dev)
{
  dvector data(1, 5);
  data(1) = 600;
  data(2) = 470;
  data(3) = 170;
  data(4) = 430;
  data(5) = 300;

  ASSERT_DOUBLE_EQ(std::sqrt(21704), std_dev(data));
}
TEST_F(test_utils, dvector_times_dmatrix)
{
  dvector vec(1, 3);
  vec(1) = 1;
  vec(2) = 2;
  vec(3) = 3;
  dmatrix mat(1, 3, 1, 2);
  mat(1, 1) = 1;
  mat(1, 2) = 1;
  mat(2, 1) = 2;
  mat(2, 2) = 2;
  mat(3, 1) = 3;
  mat(3, 2) = 3;

  dvector ret = vec * mat;

  ASSERT_EQ(1, ret.indexmin());
  ASSERT_EQ(2, ret.indexmax());
  ASSERT_DOUBLE_EQ(14, ret(1));
  ASSERT_DOUBLE_EQ(14, ret(2));
}
TEST_F(test_utils, dvector_times_dmatrix_error)
{
  dvector vec(1, 3);
  dmatrix mat(2, 3, 1, 2);

  ASSERT_ANY_THROW({
    vec * mat;
  });
}
TEST_F(test_utils, dvector_times_dmatrix_error2)
{
  dvector vec(1, 3);
  dmatrix mat(1, 4, 1, 2);

  ASSERT_ANY_THROW({
    vec * mat;
  });
}
TEST_F(test_utils, dmatrix_times_dvector)
{
  dmatrix mat(1, 3, 1, 2);
  mat(1, 1) = 1;
  mat(1, 2) = 2;
  mat(2, 1) = 1;
  mat(2, 2) = 2;
  mat(3, 1) = 1;
  mat(3, 2) = 2;
  dvector vec(1, 2);
  vec(1) = 1;
  vec(2) = 2;

  dvector ret = mat * vec;

  ASSERT_EQ(1, ret.indexmin());
  ASSERT_EQ(3, ret.indexmax());
  ASSERT_DOUBLE_EQ(5, ret(1));
  ASSERT_DOUBLE_EQ(5, ret(2));
  ASSERT_DOUBLE_EQ(5, ret(3));
}
TEST_F(test_utils, dmatrix_times_dvector_error)
{
  dmatrix mat(1, 3, 1, 2);
  dvector vec(1, 3);

  ASSERT_ANY_THROW({
    mat * vec;
  });
}
TEST_F(test_utils, dmatrix_times_dvector_error2)
{
  dmatrix mat(1, 3, 2, 2);
  dvector vec(1, 2);

  ASSERT_ANY_THROW({
    mat * vec;
  });
}
TEST_F(test_utils, dmatrix_times_dmatrix)
{
  dmatrix mat(1, 2, 1, 2);
  mat(1, 1) = 1;
  mat(1, 2) = 2;
  mat(2, 1) = 1;
  mat(2, 2) = 2;
  dmatrix mat2(1, 2, 1, 2);
  mat2(1, 1) = 1;
  mat2(1, 2) = 2;
  mat2(2, 1) = 1;
  mat2(2, 2) = 2;

  dmatrix ret = mat * mat2;

  ASSERT_EQ(1, ret.rowmin());
  ASSERT_EQ(2, ret.rowmax());
  ASSERT_EQ(1, ret(1).indexmin());
  ASSERT_EQ(2, ret(1).indexmax());
  ASSERT_EQ(1, ret(2).indexmin());
  ASSERT_EQ(2, ret(2).indexmax());

  ASSERT_DOUBLE_EQ(3, ret(1, 1));
  ASSERT_DOUBLE_EQ(6, ret(1, 2));
  ASSERT_DOUBLE_EQ(3, ret(2, 1));
  ASSERT_DOUBLE_EQ(6, ret(2, 2));
}
TEST_F(test_utils, dmatrix_times_dmatrix_error)
{
  dmatrix A(1, 3, 1, 2);
  dmatrix B(1, 3, 1, 3);

  ASSERT_ANY_THROW({
    A * B;
  });
}
TEST_F(test_utils, dmatrix_times_dmatrix_error2)
{
  dmatrix A(1, 3, 2, 3);
  dmatrix B(1, 3, 1, 3);

  ASSERT_ANY_THROW({
    A * B;
  });
}
TEST_F(test_utils, allocated_arr6)
{
  d6_array arr6;

  ASSERT_EQ(0, allocated(arr6));
 
  arr6.allocate(1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2);

  ASSERT_EQ(1, allocated(arr6));
}
TEST_F(test_utils, allocated_varr6)
{
  gradient_structure gs;

  dvar6_array arr6;

  ASSERT_EQ(0, allocated(arr6));
 
  arr6.allocate(1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2);

  ASSERT_EQ(1, allocated(arr6));
}
TEST_F(test_utils, allocated_arr7)
{
  d7_array arr7;

  ASSERT_EQ(0, allocated(arr7));
 
  arr7.allocate(1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2);

  ASSERT_EQ(1, allocated(arr7));
}
TEST_F(test_utils, allocated_varr7)
{
  gradient_structure gs;

  dvar7_array arr7;

  ASSERT_EQ(0, allocated(arr7));
 
  arr7.allocate(1, 2, 1, 2, 1, 1, 2, 2, 1, 2, 1, 2, 1, 2);

  ASSERT_EQ(1, allocated(arr7));
}
TEST_F(test_utils, is_defined_m_pi)
{
#ifndef M_PI
  FAIL();
#endif
  ASSERT_DOUBLE_EQ(PI, 3.14159265358979323846);
  ASSERT_DOUBLE_EQ(M_PI, 3.14159265358979323846);
}
