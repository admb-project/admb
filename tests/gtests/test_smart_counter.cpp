#include <gtest/gtest.h>
#include <fvar.hpp>

class test_smart_counter: public ::testing::Test {};

TEST_F(test_smart_counter, default_constructor)
{
  smart_counter c;
  int* p = c.get_ncopies();
  ASSERT_TRUE(p);
  ASSERT_EQ(*p, 0);
}
TEST_F(test_smart_counter, copy_constructor)
{
  smart_counter c;
  int* p = c.get_ncopies();
  ASSERT_TRUE(p);
  ASSERT_EQ(*p, 0);
  {
    smart_counter c2(c);
    int* p2 = c2.get_ncopies();
    ASSERT_TRUE(p2);
    ASSERT_EQ(*p2, 1);
    ASSERT_EQ(*p, 1);
    p2 = NULL;
  }
  ASSERT_EQ(*p, 0);
}
