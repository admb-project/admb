#include <gtest/gtest.h>
#include "admodel.h"

extern "C"
{
  void test_ad_exit(const int exit_code);
}

class test_param_init_bounded_number_matrix: public ::testing::Test
{
};

TEST_F(test_param_init_bounded_number_matrix, constructor)
{
  gradient_structure gs;

  param_init_bounded_number_matrix n;
  ASSERT_FALSE(n.allocated());
  ASSERT_EQ(0, n.indexmin());
  ASSERT_EQ(-1, n.indexmax());
}
TEST_F(test_param_init_bounded_number_matrix, allocate)
{
  gradient_structure gs;

  param_init_bounded_number_matrix n;

  dmatrix bmin(1, 3, 2, 4);
  dmatrix bmax(1, 3, 2, 4);
  n.allocate(1, 3, 2, 4, bmin, bmax, "id");

  ASSERT_TRUE(n.allocated());
  ASSERT_EQ(1, n.indexmin());
  ASSERT_EQ(3, n.indexmax());
  ASSERT_EQ(2, n[1].indexmin());
  ASSERT_EQ(4, n[1].indexmax());
  ASSERT_EQ(2, n[2].indexmin());
  ASSERT_EQ(4, n[2].indexmax());
  ASSERT_EQ(2, n[3].indexmin());
  ASSERT_EQ(4, n[3].indexmax());

  n.set_scalefactor(1.4);

  dmatrix scalefactor(1, 3, 2, 4);
  scalefactor = n.get_scalefactor();

  for (int i = 1; i <= 3; ++i)
  {
    for (int j = 2; j <= 4; ++j)
    {
      ASSERT_DOUBLE_EQ(1.4, scalefactor(i, j));
      ASSERT_DOUBLE_EQ(1.4, n(i, j).get_scalefactor());
    }
  }
  scalefactor.initialize();
  n.set_scalefactor(scalefactor);
  for (int i = 1; i <= 3; ++i)
  {
    for (int j = 2; j <= 4; ++j)
    {
      ASSERT_DOUBLE_EQ(0, n(i, j).get_scalefactor());
    }
  }
  ad_exit=&test_ad_exit;

  ASSERT_ANY_THROW({
    n[0];
  });
  ASSERT_ANY_THROW({
    n[10];
  });
  ASSERT_ANY_THROW({
    n(0);
  });
  ASSERT_ANY_THROW({
    n(10);
  });
}
TEST_F(test_param_init_bounded_number_matrix, param_init_bounded_number_matrix_01)
{
  gradient_structure gs;
  param_init_bounded_number_matrix v;
//#define TEST_UNDEFINED_COPY_CONSTRUCTOR
#ifdef TEST_UNDEFINED_COPY_CONSTRUCTOR
  param_init_bounded_number_matrix v2(v);
#endif
  ASSERT_FALSE(v.allocated());
  ASSERT_EQ(v.indexmin(), 0);
  ASSERT_EQ(v.indexmax(), -1);
}
/**
 * Test for param_init_bounded_number_matrix.
 */
TEST_F(test_param_init_bounded_number_matrix, param_init_bounded_number_matrix_02)
{
  gradient_structure gs;
  dmatrix b(1, 5, 1, 5);
  imatrix m(1, 5, 1, 5);
  param_init_bounded_number_matrix v;
  v.allocate(1, 5, 
             1, 5,
             b, b,
             m,
             "test");

  ASSERT_TRUE(v.allocated());
  ASSERT_EQ(v.indexmin(), 1);
  ASSERT_EQ(v.indexmax(), 5);
}
/**
 * Test for param_init_bounded_number_matrix.
 */
TEST_F(test_param_init_bounded_number_matrix, param_init_bounded_number_matrix_03)
{
  gradient_structure gs;
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
  gradient_structure gs;
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
  ad_exit=&test_ad_exit;

  gradient_structure gs;
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
    //v.deallocate();
    SUCCEED();
    return;
  }
  FAIL();
}
/**
 * Test for param_init_bounded_number_matrix.
 */
TEST_F(test_param_init_bounded_number_matrix, param_init_bounded_number_matrix_06)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;
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
    //v.deallocate();
    SUCCEED();
    return;
  }
  FAIL();
}
/**
 * Test for param_init_bounded_number_matrix.
 */
TEST_F(test_param_init_bounded_number_matrix, param_init_bounded_number_matrix_07)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;
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
    //v.deallocate();
    SUCCEED();
    return;
  }
  FAIL();
}
