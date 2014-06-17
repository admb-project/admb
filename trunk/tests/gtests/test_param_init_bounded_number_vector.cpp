#include <gtest/gtest.h>
#include <admodel.h>

class test_param_init_bounded_number_vector: public ::testing::Test {};

TEST_F(test_param_init_bounded_number_vector, default_constructor)
{
  param_init_bounded_number_vector p;
  EXPECT_EQ(0, p.allocated());
  EXPECT_EQ(-1, p.indexmin());
  EXPECT_EQ(-1, p.indexmax());
}
TEST_F(test_param_init_bounded_number_vector, set_initial_value)
{
  gradient_structure gs(1500);

  param_init_bounded_number_vector p;
  const int min = 1;
  const int max = 3;
  dvector mins(min, max);
  mins.initialize();
  dvector maxs(min, max);
  maxs = 5;
  std::string s("AString"); 
  p.allocate(min, max, mins, maxs, s.c_str());
  EXPECT_NE(0, p.allocated());
  EXPECT_EQ(min, p.indexmin());
  EXPECT_EQ(max, p.indexmax());

  dvector v(min, max); 
  v.initialize();

  p.set_initial_value(v);
  for (int i = min; i <= max; i++)
  {
    EXPECT_EQ(0, p[i]);
    v[i] = i;
  }

  p.set_initial_value(v);
  for (int i = min; i <= max; i++)
  {
    EXPECT_EQ(i, p[i]);
  }

  p.deallocate();
  EXPECT_EQ(0, p.allocated());
  EXPECT_EQ(-1, p.indexmin());
  EXPECT_EQ(-1, p.indexmax());
}
