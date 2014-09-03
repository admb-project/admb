#include <gtest/gtest.h>
#include <fvar.hpp>
#include <climits>

extern "C"
{
  void test_ad_exit(const int exit_code);
}

class test_imatrix: public ::testing::Test {};

TEST_F(test_imatrix, column)
{
  imatrix m(1, 2, 1, 3);
  m(1, 1) = 0;
  m(1, 2) = 1;
  m(1, 3) = 2;
  m(2, 1) = 3;
  m(2, 2) = 4;
  m(2, 3) = 5;

  ivector v = column(m, 2);

  ASSERT_EQ(1, v(1));
  ASSERT_EQ(4, v(2));
}
TEST_F(test_imatrix, multiply_wrongdimensions)
{
  imatrix m(1, 2, 1, 3);
  try
  {
    imatrix mm = m * m;
  }
  catch (const int exit_code)          
  {   
    const int expected_exit_code = 21;
    if (exit_code == expected_exit_code)
    {
      return;
    }
  }
  FAIL();
}
TEST_F(test_imatrix, multiply)
{
  imatrix m(1, 2, 1, 3);
  m(1, 1) = 0;
  m(1, 2) = 1;
  m(1, 3) = 2;
  m(2, 1) = 3;
  m(2, 2) = 4;
  m(2, 3) = 5;
  imatrix n(1, 3, 1, 2);
  n(1, 1) = 5;
  n(2, 1) = 4;
  n(3, 1) = 3;
  n(1, 2) = 2;
  n(2, 2) = 1;
  n(3, 2) = 0;

  imatrix mn = m * n;
  ASSERT_EQ(10, mn(1, 1));
  ASSERT_EQ(1, mn(1, 2));
  ASSERT_EQ(46, mn(2, 1));
  ASSERT_EQ(10, mn(2, 2));
}
