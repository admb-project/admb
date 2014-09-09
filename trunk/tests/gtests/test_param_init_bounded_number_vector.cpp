#include <gtest/gtest.h>
#include <admodel.h>

extern "C"
{
  void test_ad_exit(const int exit_code);
}

class test_param_init_bounded_number_vector: public ::testing::Test {};

TEST_F(test_param_init_bounded_number_vector, default_constructor)
{
  param_init_bounded_number_vector p;
  EXPECT_EQ(0, p.allocated());
  EXPECT_EQ(-1, p.indexmin());
  EXPECT_EQ(-1, p.indexmax());
}
#ifndef OPT_LIB
TEST_F(test_param_init_bounded_number_vector, set_initial_value_only)
{
  ad_exit=&test_ad_exit;

  const int min = 1;
  const int max = 3;
  dvector v(min, max); 
  v.initialize();

  param_init_bounded_number_vector p;
  p.set_initial_value(v);
  try
  {
    p[min];
  }
  catch (const int exit_code)          
  {   
    const int expected_exit_code = 1;
    if (exit_code == expected_exit_code)
    {
      SUCCEED();
    }
      return;
  }
  FAIL();
}
#endif
/*
TEST_F(test_param_init_bounded_number_vector, set_initial_value_first)
{
  gradient_structure gs(1500);

  param_init_bounded_number_vector p;
  const int min = 1;
  const int max = 3;

  dvector v(min, max); 
  v.initialize();
  p.set_initial_value(v);

  dvector mins(min, max);
  mins.initialize();
  dvector maxs(min, max);
  maxs = 5;
  std::string s("AString"); 
  p.allocate(min, max, mins, maxs, s.c_str());
  EXPECT_NE(0, p.allocated());
  EXPECT_EQ(min, p.indexmin());
  EXPECT_EQ(max, p.indexmax());

  for (int i = min; i <= max; i++)
  {
    EXPECT_EQ(0, value(p[i]));
  }

  p.deallocate();
  EXPECT_EQ(0, p.allocated());
  EXPECT_EQ(-1, p.indexmin());
  EXPECT_EQ(-1, p.indexmax());
}
*/
