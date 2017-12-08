#include <gtest/gtest.h>
#include <admodel.h>

extern "C"
{
  void test_ad_exit(const int exit_code);
}

class test_param_init_number_vector: public ::testing::Test {};

#ifndef OPT_LIB
TEST_F(test_param_init_number_vector, set_initial_value_only)
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
  catch (const std::bad_alloc&)          
  {   
    return;
  }
  FAIL();
}
TEST_F(test_param_init_number_vector, set_initial_value_only_paren)
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
    p(min);
  }
  catch (const std::bad_alloc&)          
  {   
    return;
  }
  FAIL();
}
#endif
/*
TEST_F(test_param_init_number_vector, set_initial_value_first)
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
  EXPECT_EQ(0, p.indexmin());
  EXPECT_EQ(0, p.indexmax());
}
*/
TEST_F(test_param_init_number_vector, constructor)
{
  param_init_number_vector p;
  ASSERT_FALSE(p.allocated());
  ASSERT_EQ(0, p.indexmin());
  ASSERT_EQ(0, p.indexmax());
}
TEST_F(test_param_init_number_vector, allocate)
{
  gradient_structure gs;
  param_init_number_vector p;
  p.allocate(1, 4, "allocate");
  ASSERT_TRUE(p.allocated());
  ASSERT_EQ(1, p.indexmin());
  ASSERT_EQ(4, p.indexmax());
}
TEST_F(test_param_init_number_vector, setscalefactorerror)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;

  param_init_number_vector p;
  p.allocate(1, 4, "allocate");

  ASSERT_ANY_THROW({
    dvector v;
    p.set_scalefactor(v);
  });
  ASSERT_ANY_THROW({
    dvector v(0, 4);
    p.set_scalefactor(v);
  });
  ASSERT_ANY_THROW({
    dvector v(1, 5);
    p.set_scalefactor(v);
  });
}
/*
TEST_F(test_param_init_number_vector, setscalefactor)
{
  gradient_structure gs;

  param_init_number_vector p;
  p.allocate(1, 4, "allocate");
  ASSERT_TRUE(p.allocated());
  ASSERT_EQ(1, p.indexmin());
  ASSERT_EQ(4, p.indexmax());

  dvector scalefactors = p.get_scalefactor();

  ASSERT_DOUBLE_EQ(0, value(scalefactors(1)));
  ASSERT_DOUBLE_EQ(0, value(scalefactors(2)));
  ASSERT_DOUBLE_EQ(0, value(scalefactors(3)));
  ASSERT_DOUBLE_EQ(0, value(scalefactors(4)));

  p.set_scalefactor(2.5); //Thows exception
  scalefactors = p.get_scalefactor();

  ASSERT_DOUBLE_EQ(2.5, value(scalefactors(1)));
  ASSERT_DOUBLE_EQ(2.5, value(scalefactors(2)));
  ASSERT_DOUBLE_EQ(2.5, value(scalefactors(3)));
  ASSERT_DOUBLE_EQ(2.5, value(scalefactors(4)));

  scalefactors(1) = 1.5;
  scalefactors(2) = 2.5;
  scalefactors(3) = 3.5;
  scalefactors(4) = 4.5;

  p.set_scalefactor(scalefactors);

  ASSERT_DOUBLE_EQ(1.5, value(scalefactors(1)));
  ASSERT_DOUBLE_EQ(2.5, value(scalefactors(2)));
  ASSERT_DOUBLE_EQ(3.5, value(scalefactors(3)));
  ASSERT_DOUBLE_EQ(4.5, value(scalefactors(4)));
}
*/
TEST_F(test_param_init_number_vector, allocate_error)
{
  param_init_number_vector p;
  p.allocate(1, -4, "allocate");
  ASSERT_FALSE(p.allocated());
  ASSERT_EQ(0, p.indexmin());
  ASSERT_EQ(0, p.indexmax());
}
