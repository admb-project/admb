#include <cfenv>
#include <cmath>
#include <climits>
#include <gtest/gtest.h>

#include <fvar.hpp>

void test_ad_exit(const int exit_code);

class test_cfenv: public ::testing::Test {};

TEST_F(test_cfenv, check_none)
{
  std::feclearexcept(FE_ALL_EXCEPT);  
  ASSERT_FALSE(std::fetestexcept(FE_DIVBYZERO));
  ASSERT_FALSE(std::fetestexcept(FE_INEXACT));
  ASSERT_FALSE(std::fetestexcept(FE_INVALID));
  ASSERT_FALSE(std::fetestexcept(FE_OVERFLOW));
  ASSERT_FALSE(std::fetestexcept(FE_UNDERFLOW));
}
TEST_F(test_cfenv, exp_overflow)
{
  std::feclearexcept(FE_ALL_EXCEPT);  
  std::exp(DBL_MAX); 
  ASSERT_FALSE(std::fetestexcept(FE_DIVBYZERO));
  ASSERT_FALSE(std::fetestexcept(FE_INEXACT));
  ASSERT_FALSE(std::fetestexcept(FE_INVALID));
  ASSERT_FALSE(std::fetestexcept(FE_OVERFLOW));
  ASSERT_FALSE(std::fetestexcept(FE_UNDERFLOW));
}
TEST_F(test_cfenv, divbyzero)
{
  std::feclearexcept(FE_ALL_EXCEPT);  
  std::log(0.0);
  ASSERT_FALSE(std::fetestexcept(FE_DIVBYZERO));
  ASSERT_FALSE(std::fetestexcept(FE_INEXACT));
  ASSERT_FALSE(std::fetestexcept(FE_INVALID));
  ASSERT_FALSE(std::fetestexcept(FE_OVERFLOW));
  ASSERT_FALSE(std::fetestexcept(FE_UNDERFLOW));
}
TEST_F(test_cfenv, invalid)
{
  std::feclearexcept(FE_ALL_EXCEPT);  
  std::acos(2.0);
  ASSERT_FALSE(std::fetestexcept(FE_DIVBYZERO));
  ASSERT_FALSE(std::fetestexcept(FE_INEXACT));
  ASSERT_FALSE(std::fetestexcept(FE_INVALID));
  ASSERT_FALSE(std::fetestexcept(FE_OVERFLOW));
  ASSERT_FALSE(std::fetestexcept(FE_UNDERFLOW));
}
TEST_F(test_cfenv, mfexp_overflow)
{
  std::feclearexcept(FE_ALL_EXCEPT);  
  mfexp(DBL_MAX); 
  ASSERT_FALSE(std::fetestexcept(FE_DIVBYZERO));
  ASSERT_TRUE(std::fetestexcept(FE_INEXACT));
  ASSERT_FALSE(std::fetestexcept(FE_INVALID));
  ASSERT_TRUE(std::fetestexcept(FE_OVERFLOW));
  ASSERT_FALSE(std::fetestexcept(FE_UNDERFLOW));
}
TEST_F(test_cfenv, dvariable_mfexp_overflow)
{
  std::feclearexcept(FE_ALL_EXCEPT);  
  gradient_structure gs;
  dvariable d(DBL_MAX);
  mfexp(d); 
  ASSERT_FALSE(std::fetestexcept(FE_DIVBYZERO));
  ASSERT_TRUE(std::fetestexcept(FE_INEXACT));
  ASSERT_FALSE(std::fetestexcept(FE_INVALID));
  ASSERT_TRUE(std::fetestexcept(FE_OVERFLOW));
  ASSERT_TRUE(std::fetestexcept(FE_UNDERFLOW));
}
