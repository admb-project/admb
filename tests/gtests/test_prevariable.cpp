#include <gtest/gtest.h>
#include <fvar.hpp>

void test_ad_exit(const int exit_code);

class test_prevariable: public ::testing::Test {};

TEST_F(test_prevariable, copy_constructor)
{
  gradient_structure gs;
  // prevariable p;
  // prevariable p(nullptr);

  dvar_vector v(1, 1);

  const prevariable& a = v(1);

  ASSERT_EQ(0, gradient_structure::get()->GRAD_STACK1->total());
  ASSERT_EQ(1750, gradient_structure::get()->GRAD_LIST->total_addresses());
  prevariable p(a);
  ASSERT_TRUE(p.v == a.v);
  ASSERT_EQ(0, gradient_structure::get()->GRAD_STACK1->total());
  ASSERT_EQ(1750, gradient_structure::get()->GRAD_LIST->total_addresses());

  ASSERT_TRUE(v(1).v == p.v);
}
TEST_F(test_prevariable, dvariable_constructor)
{
  gradient_structure gs;

  dvar_vector v(1, 1);

  const prevariable& a = v(1);

  ASSERT_EQ(0, gradient_structure::get()->GRAD_STACK1->total());
  ASSERT_EQ(1750, gradient_structure::get()->GRAD_LIST->total_addresses());
  dvariable p(a);
  ASSERT_EQ(1, gradient_structure::get()->GRAD_STACK1->total());
  ASSERT_EQ(1751, gradient_structure::get()->GRAD_LIST->total_addresses());

  ASSERT_TRUE(v(1).v != p.v);
}
TEST_F(test_prevariable, dvariable_constructor_dvariable)
{
  gradient_structure gs;

  ASSERT_EQ(1750, gradient_structure::get()->GRAD_LIST->total_addresses());
  const dvariable a;

  ASSERT_EQ(0, gradient_structure::get()->GRAD_STACK1->total());
  ASSERT_EQ(1751, gradient_structure::get()->GRAD_LIST->total_addresses());
  dvariable p(a);
  ASSERT_EQ(1, gradient_structure::get()->GRAD_STACK1->total());
  ASSERT_EQ(1752, gradient_structure::get()->GRAD_LIST->total_addresses());

  ASSERT_TRUE(a.v != p.v);
}
