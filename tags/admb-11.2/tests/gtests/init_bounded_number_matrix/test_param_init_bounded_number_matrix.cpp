#include <gtest/gtest.h>

#include <fvar.hpp>
#include "param_init_bounded_number_matrix.h"
#include "admb_messages.h"

extern "C"
{
  void test_ad_exit(const int exit_code)
  {
    throw exit_code;
  }
}

class test_param_init_bounded_number_matrix: public ::testing::Test {};

gradient_structure gs(1500000L);
/**
 * Test for param_init_bounded_number_matrix.
 */
TEST_F(test_param_init_bounded_number_matrix, param_init_bounded_number_matrix_01)
{
  param_init_bounded_number_matrix v;
//#define TEST_UNDEFINED_COPY_CONSTRUCTOR
#ifdef TEST_UNDEFINED_COPY_CONSTRUCTOR
  param_init_bounded_number_matrix v2(v);
#endif
  if (v.allocated() == false
      && v.indexmin() == 0
      && v.indexmax() == 0)
  {
    SUCCEED();
    return;
  }
  FAIL();
}
/**
 * Test for param_init_bounded_number_matrix.
 */
TEST_F(test_param_init_bounded_number_matrix, param_init_bounded_number_matrix_02)
{
  dmatrix b(1, 5, 1, 5);
  imatrix m(1, 5, 1, 5);
  param_init_bounded_number_matrix v;
  v.allocate(1, 5, 
             1, 5,
             b, b,
             m,
             "test");

  if (v.allocated() == true 
      && v.indexmin() == 1
      && v.indexmax() == 5)
  {
    SUCCEED();
    return;
  }
  FAIL();
}
/**
 * Test for param_init_bounded_number_matrix.
 */
TEST_F(test_param_init_bounded_number_matrix, param_init_bounded_number_matrix_03)
{
  dmatrix b(1, 5, 1, 5);
  imatrix m(1, 5, 1, 5);
  param_init_bounded_number_matrix v;
  v.allocate(1, 5, 
             1, 5,
             b, b,
             m,
             "test");

  v.set_scalefactor(1);
  dmatrix dm = v.get_scalefactor();
  if (dm.rowmin() != 1 && dm.rowmax() != 5)
  {
    FAIL();
    return;
  }
  for (int i = dm.rowmin(); i <= dm.rowmax(); i++)
  {
    dvector& dv = dm(i);
    int indexmin = dv.indexmin();
    int indexmax = dv.indexmax();
    if (indexmin != 1 && indexmax != 5)
    {
      FAIL();
      return;
    }
    for (int j = indexmin; j <= indexmax; j++)
    {
      double value = dv(j);
      if (!(0.9999 < value && value < 1.00001))
      {
        FAIL();
        return;
      }
    }
  } 
  SUCCEED();
}
/**
 * Test for param_init_bounded_number_matrix.
 */
TEST_F(test_param_init_bounded_number_matrix, param_init_bounded_number_matrix_04)
{
  dmatrix b(1, 5, 1, 5);
  imatrix m(1, 5, 1, 5);
  param_init_bounded_number_matrix v;
  v.allocate(1, 5, 
             1, 5,
             b, b,
             m,
             "test");

  dmatrix scalefactor(1, 5, 1, 5);
  scalefactor = 2;
  v.set_scalefactor(scalefactor);
  dmatrix dm = v.get_scalefactor();
  if (dm.rowmin() != 1 && dm.rowmax() != 5)
  {
    FAIL();
    return;
  }
  for (int i = dm.rowmin(); i <= dm.rowmax(); i++)
  {
    dvector& dv = dm(i);
    int indexmin = dv.indexmin();
    int indexmax = dv.indexmax();
    if (indexmin != 1 && indexmax != 5)
    {
      FAIL();
      return;
    }
    for (int j = indexmin; j <= indexmax; j++)
    {
      double value = dv(j);
      if (!(1.9999 < value && value < 2.00001))
      {
        FAIL();
        return;
      }
    }
  } 
  SUCCEED();
}
/**
 * Test for param_init_bounded_number_matrix.
 */
TEST_F(test_param_init_bounded_number_matrix, param_init_bounded_number_matrix_05)
{
  dmatrix b(1, 5, 1, 5);
  imatrix m(1, 5, 1, 5);
  param_init_bounded_number_matrix v;
  v.allocate(1, 5, 
             1, 5,
             b, b,
             m,
             "test");
  try
  {
    param_init_bounded_number_vector& pibnv1 = v(1);
    param_init_bounded_number_vector& pibnv0 = v(0);
  }
  catch (const int exit_code)
  {
    const int expected_exit_code = admb::ARRAY_BOUNDS_ERROR;
    if (exit_code == expected_exit_code)
    {
      SUCCEED();
      return;
    }
  }
  FAIL();
}
/**
 * Test for param_init_bounded_number_matrix.
 */
TEST_F(test_param_init_bounded_number_matrix, param_init_bounded_number_matrix_06)
{
  dmatrix b(1, 5, 1, 5);
  imatrix m(1, 5, 1, 5);
  param_init_bounded_number_matrix v;
  v.allocate(1, 5, 
             1, 5,
             b, b,
             m,
             "test");
  try
  {
    param_init_bounded_number_vector& pibnv1 = v[5];
    param_init_bounded_number_vector& pibnv0 = v[6];
  }
  catch (const int exit_code)
  {
    const int expected_exit_code = admb::ARRAY_BOUNDS_ERROR;
    if (exit_code == expected_exit_code)
    {
      SUCCEED();
      return;
    }
  }
  FAIL();
}
/**
 * Test for param_init_bounded_number_matrix.
 */
TEST_F(test_param_init_bounded_number_matrix, param_init_bounded_number_matrix_07)
{
  dmatrix b(1, 5, 1, 5);
  imatrix m(1, 5, 1, 5);
  param_init_bounded_number_matrix v;
  v.allocate(1, 5, 
             1, 5,
             b, b,
             m,
             "test");
  try
  {
    param_init_bounded_number& pibnv11 = v(1, 1);
    param_init_bounded_number_vector& pibnv1 = v(5);
    param_init_bounded_number_vector& pibnv0 = v(6);
  }
  catch (const int exit_code)
  {
    const int expected_exit_code = admb::ARRAY_BOUNDS_ERROR;
    if (exit_code == expected_exit_code)
    {
      SUCCEED();
      return;
    }
  }
  FAIL();
}
int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  ad_exit=&test_ad_exit;
  return RUN_ALL_TESTS();
}
