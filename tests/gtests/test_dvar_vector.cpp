#include <gtest/gtest.h>
#include <fvar.hpp>

extern "C"
{
  void test_ad_exit(const int exit_code);
}

class test_dvar_vector:public ::testing::Test {};

TEST_F(test_dvar_vector, fill)
{
  gradient_structure gs;

  dvar_vector v(1, 6);
  v.initialize();

  char array[] = "{0, 1, 2, 3, 4, 5}";

  v.fill(array);

  ASSERT_DOUBLE_EQ(0, value(v(1)));
  ASSERT_DOUBLE_EQ(1, value(v(2)));
  ASSERT_DOUBLE_EQ(2, value(v(3)));
  ASSERT_DOUBLE_EQ(3, value(v(4)));
  ASSERT_DOUBLE_EQ(4, value(v(5)));
  ASSERT_DOUBLE_EQ(5, value(v(6)));
}
TEST_F(test_dvar_vector, constructor_fill)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;

  char array[] = "{0, 1, 2, 3, 4, 5}";
  dvar_vector v(array);

  ASSERT_DOUBLE_EQ(0, value(v(1)));
  ASSERT_DOUBLE_EQ(1, value(v(2)));
  ASSERT_DOUBLE_EQ(2, value(v(3)));
  ASSERT_DOUBLE_EQ(3, value(v(4)));
  ASSERT_DOUBLE_EQ(4, value(v(5)));
  ASSERT_DOUBLE_EQ(5, value(v(6)));
}
