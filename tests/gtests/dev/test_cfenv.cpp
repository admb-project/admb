#include <cfenv>
#include <cmath>
#include <climits>
#include <gtest/gtest.h>
#include <fvar.hpp>

extern "C"
{
  void test_ad_exit(const int exit_code);
}

class test_cfenv: public ::testing::Test {};

TEST_F(test_cfenv, check_none)
{
  std::feclearexcept(FE_ALL_EXCEPT);  
  ASSERT_EQ(std::fetestexcept(FE_ALL_EXCEPT), 0);
}
TEST_F(test_cfenv, exp_overflow)
{
  std::feclearexcept(FE_ALL_EXCEPT);  
  std::exp(DBL_MAX); 
  ASSERT_EQ(std::fetestexcept(FE_ALL_EXCEPT & ~FE_INEXACT), FE_OVERFLOW);
}
TEST_F(test_cfenv, divbyzero)
{
  std::feclearexcept(FE_ALL_EXCEPT);  
  std::log(0.0);
  ASSERT_EQ(std::fetestexcept(FE_ALL_EXCEPT & ~FE_INEXACT), FE_DIVBYZERO);
}
TEST_F(test_cfenv, invalid)
{
  std::feclearexcept(FE_ALL_EXCEPT);  
  std::acos(2.0);
  ASSERT_EQ(std::fetestexcept(FE_ALL_EXCEPT & ~FE_INEXACT), FE_INVALID);
}
TEST_F(test_cfenv, mfexp_overflow)
{
  std::feclearexcept(FE_ALL_EXCEPT);  
  mfexp(DBL_MAX); 
  ASSERT_EQ(std::fetestexcept(FE_ALL_EXCEPT & ~FE_INEXACT), FE_OVERFLOW);
}
TEST_F(test_cfenv, dvariable_mfexp_overflow)
{
  std::feclearexcept(FE_ALL_EXCEPT);  
  gradient_structure gs;
  dvariable d(DBL_MAX);
  mfexp(d); 
  ASSERT_EQ(std::fetestexcept(FE_OVERFLOW), FE_OVERFLOW);
}
