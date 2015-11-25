#include <gtest/gtest.h>
#include <cmath>
#include <limits>
#include <fvar.hpp>

extern "C"
{
  void test_ad_exit(const int exit_code);
}

class test_dvariable: public ::testing::Test {};

TEST_F(test_dvariable, fmax)
{
  gradient_structure gs;

  dvariable fmax(double x,double* y);
  double x = 10;
  double y = 20;
  dvariable d = fmax(x, &y);
  ASSERT_EQ(y, value(d));
  d = fmax(y, &x);
  ASSERT_EQ(y, value(d));
  d = fmax(x, &x);
  ASSERT_EQ(x, value(d));
}
TEST_F(test_dvariable, det)
{
  gradient_structure gs;

  dvar_matrix vm(1, 2, 1, 2);
  vm(1, 1) = 3;
  vm(1, 2) = 8;
  vm(2, 1) = 4;
  vm(2, 2) = 6;

  dvariable vdet = det(vm);
  ASSERT_DOUBLE_EQ(-14, value(vdet));

  dmatrix m(1, 2, 1, 2);
  m(1, 1) = 3;
  m(1, 2) = 8;
  m(2, 1) = 4;
  m(2, 2) = 6;
  double cdet = det(m);
  ASSERT_DOUBLE_EQ(-14, cdet);
}
TEST_F(test_dvariable, exp_1)
{
  gradient_structure gs;
  
  dvariable v = 1;
  try
  {
    double expected = ::exp(1);
    dvariable result = exp(v);
    ASSERT_DOUBLE_EQ(expected, value(result));
  }
  catch (const int exit_code)          
  {   
    const int expected_exit_code = 1;
    if (exit_code == expected_exit_code)
    {
      FAIL();
    }
  }
}
#ifndef OPT_LIB
  ///\todo Must remove macros below once support for MSVC++11 and Solaris Studio 12.3 are removed.
  #if !defined(__SUNPRO_CC) && !(defined(_MSC_VER) && (_MSC_VER <= 1700))
TEST_F(test_dvariable, exp_max)
{
  gradient_structure gs;
  
  dvariable v = std::numeric_limits< double >::max();
  try
  {
    exp(v);
  }
  catch (const int exit_code)          
  {   
    const int expected_exit_code = 1;
    if (exit_code == expected_exit_code)
    {
      SUCCEED();
      return;
    }
  }
  FAIL();
}
  #endif
#endif
TEST_F(test_dvariable, mfexp)
{
  gradient_structure gs;
  
  {
  double input = 100; 
  double result = mfexp(input);

  dvariable vinput = 100; 
  dvariable vresult = mfexp(vinput);

  ASSERT_DOUBLE_EQ(result, value(vresult));
  }
  {
  double input = -100; 
  double result = mfexp(input);

  dvariable vinput = -100; 
  dvariable vresult = mfexp(vinput);

  ASSERT_DOUBLE_EQ(result, value(vresult));
  }
  {
  double input = 60; 
  double result = mfexp(input);

  dvariable vinput = 60; 
  dvariable vresult = mfexp(vinput);

  ASSERT_DOUBLE_EQ(result, value(vresult));
  }
  {
  double input = -60; 
  double result = mfexp(input);

  dvariable vinput = -60; 
  dvariable vresult = mfexp(vinput);

  ASSERT_DOUBLE_EQ(result, value(vresult));
  }
  {
  double input = 61; 
  double result = mfexp(input);

  dvariable vinput = 61; 
  dvariable vresult = mfexp(vinput);

  ASSERT_DOUBLE_EQ(result, value(vresult));
  }
  {
  double input = -61; 
  double result = mfexp(input);

  dvariable vinput = -61; 
  dvariable vresult = mfexp(vinput);

  ASSERT_DOUBLE_EQ(result, value(vresult));
  }
  {
  double input = 10; 
  double result = mfexp(input);

  dvariable vinput = 10; 
  dvariable vresult = mfexp(vinput);

  ASSERT_DOUBLE_EQ(result, value(vresult));
  }
  {
  double input = -10; 
  double result = mfexp(input);

  dvariable vinput = -10; 
  dvariable vresult = mfexp(vinput);

  ASSERT_DOUBLE_EQ(result, value(vresult));
  }
  {
  double input = 0; 
  double result = mfexp(input);

  dvariable vinput = 0; 
  dvariable vresult = mfexp(vinput);

  ASSERT_DOUBLE_EQ(result, value(vresult));
  }
}
