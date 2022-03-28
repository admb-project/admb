#include <gtest/gtest.h>
#include <fvar.hpp>

class test_ad_double: public ::testing::Test {};

/*
TEST_F(test_ad_double, default_constructor)
{
  // Default should be deleted
  ad_double a;
  
  ASSERT_DOUBLE_EQ(double(a), 0);
}
*/
TEST_F(test_ad_double, constructor_double)
{
  ad_double a(5.65);
  
  ASSERT_DOUBLE_EQ(double(a), 5.65);
}
TEST_F(test_ad_double, copy_constructor)
{
  ad_double a(5.65);
  ad_double b(a);
  
  ASSERT_DOUBLE_EQ(double(b), 5.65);
}
TEST_F(test_ad_double, make_ad_double)
{
  ad_double a = ad_double::make_ad_double(5.65);
  ASSERT_DOUBLE_EQ(double(a), 5.65);
}
