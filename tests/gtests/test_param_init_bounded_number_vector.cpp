#include <gtest/gtest.h>
#include <admodel.h>

class test_param_init_bounded_number_vector: public ::testing::Test {};

TEST_F(test_param_init_bounded_number_vector, default_constructor)
{
  param_init_bounded_number_vector p;
  EXPECT_EQ(0, p.allocated());
  EXPECT_EQ(1, p.indexmin());
  EXPECT_EQ(0, p.indexmax());
}
TEST_F(test_param_init_bounded_number_vector, set_initial_value)
{
  param_init_bounded_number_vector p;
  p.set_initial_value(0.5);
  EXPECT_EQ(0, p.allocated());
  EXPECT_EQ(1, p.indexmin());
  EXPECT_EQ(0, p.indexmax());
}
TEST_F(test_param_init_bounded_number_vector, allocate)
{
  ad_comm::argc = 0;
  ad_comm::argv = nullptr;

  gradient_structure gs;

  param_init_bounded_number_vector p;
  p.allocate(1, 4, 0.5, 1.0, "param_init_bounded_number_vecotor");
  EXPECT_TRUE(p.allocated());
  EXPECT_EQ(1, p.indexmin());
  EXPECT_EQ(4, p.indexmax());
}
TEST_F(test_param_init_bounded_number_vector, nonmatching)
{
  gradient_structure gs;

  param_init_bounded_number_vector p;
  p.allocate(1, 4, 0.5, 1.0, "param_init_bounded_number_vecotor");
cout << __FILE__ << ':' << __LINE__ << endl;
  p.deallocate();
cout << __FILE__ << ':' << __LINE__ << endl;

/*
  ASSERT_ANY_THROW({
    dvector scalefactor;
    p.set_scalefactor(scalefactor);
  });
  ASSERT_ANY_THROW({
    dvector scalefactor(0, 4);
    p.set_scalefactor(scalefactor);
  });
  ASSERT_ANY_THROW({
    dvector scalefactor(1, 5);
    p.set_scalefactor(scalefactor);
  });
*/
}
TEST_F(test_param_init_bounded_number_vector, allocateset_initial_value)
{
  gradient_structure gs;

  param_init_bounded_number_vector p;
  p.allocate(1, 4, 0.5, 1.0, "param_init_bounded_number_vecotor");
  p.set_initial_value(2.5);
  EXPECT_TRUE(p.allocated());
  EXPECT_EQ(1, p.indexmin());
  EXPECT_EQ(4, p.indexmax());
  EXPECT_DOUBLE_EQ(2.5, value(p(1)));
  EXPECT_DOUBLE_EQ(2.5, value(p(2)));
  EXPECT_DOUBLE_EQ(2.5, value(p(3)));
  EXPECT_DOUBLE_EQ(2.5, value(p(4)));
  p.set_initial_value(2.5);
  EXPECT_DOUBLE_EQ(2.5, value(p(1)));
  EXPECT_DOUBLE_EQ(2.5, value(p(2)));
  EXPECT_DOUBLE_EQ(2.5, value(p(3)));
  EXPECT_DOUBLE_EQ(2.5, value(p(4)));

  dvector scalefactors = p.get_scalefactor();
  EXPECT_EQ(1, scalefactors.indexmin());
  EXPECT_EQ(4, scalefactors.indexmax());
  EXPECT_DOUBLE_EQ(0, scalefactors(1));
  EXPECT_DOUBLE_EQ(0, scalefactors(2));
  EXPECT_DOUBLE_EQ(0, scalefactors(3));
  EXPECT_DOUBLE_EQ(0, scalefactors(4));
  p.set_scalefactor(2.5);
  scalefactors = p.get_scalefactor();
  EXPECT_DOUBLE_EQ(2.5, scalefactors(1));
  EXPECT_DOUBLE_EQ(2.5, scalefactors(2));
  EXPECT_DOUBLE_EQ(2.5, scalefactors(3));
  EXPECT_DOUBLE_EQ(2.5, scalefactors(4));
  scalefactors(1) = 1.5;
  scalefactors(2) = 2.5;
  scalefactors(3) = 3.5;
  scalefactors(4) = 4.5;
  p.set_scalefactor(scalefactors);
  scalefactors = p.get_scalefactor();
  EXPECT_DOUBLE_EQ(1.5, scalefactors(1));
  EXPECT_DOUBLE_EQ(2.5, scalefactors(2));
  EXPECT_DOUBLE_EQ(3.5, scalefactors(3));
  EXPECT_DOUBLE_EQ(4.5, scalefactors(4));
}
TEST_F(test_param_init_bounded_number_vector, set_initial_valueallocate)
{
  gradient_structure gs;

  param_init_bounded_number_vector p;
  p.set_initial_value(0.5);
  p.allocate(1, 4, 0.5, 1.0, "param_init_bounded_number_vecotor");
  EXPECT_TRUE(p.allocated());
  EXPECT_EQ(1, p.indexmin());
  EXPECT_EQ(4, p.indexmax());
}
#ifndef OPT_LIB
TEST_F(test_param_init_bounded_number_vector, set_initial_value_only)
{
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
TEST_F(test_param_init_bounded_number_vector, set_initial_value_only_paren)
{
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
/*
TEST_F(test_param_init_bounded_number_vector, allocated_set_initial_value_only_paren)
{
  gradient_structure* gs = new gradient_structure();

  const int min = 1;
  const int max = 3;
  dvector v(min, max); 
  v.initialize();

  param_init_bounded_number_vector p;
  p.allocate(1, 3, -10, 10, "kdjfkdj");
  p.set_initial_value(v);
  try
  {
    p(min);
  }
  catch (const std::out_of_range&)
  {   
    delete gs;
    return;
  }
  FAIL();
}
*/
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
