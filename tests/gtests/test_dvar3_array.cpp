#include <gtest/gtest.h>
#include <fvar.hpp>

extern "C"
{
  void test_ad_exit(const int exit_code);
}

class test_dvar3_array: public ::testing::Test {};

TEST_F(test_dvar3_array, mean_null)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;
  dvar3_array a;
  ASSERT_EQ(0, size_count(a));
  ASSERT_ANY_THROW(
    mean(a);
  );
}
TEST_F(test_dvar3_array, mean)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;
  dvar3_array a(1, 2, 1, 2, 1, 2);
  a = 1;
  ASSERT_EQ(8, size_count(a));
  ASSERT_DOUBLE_EQ(8, value(sum(a)));
  dvariable v = mean(a);
  ASSERT_DOUBLE_EQ(1, value(v));
}
TEST_F(test_dvar3_array, mean_double)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;
  dvar3_array a(1, 2, 1, 2, 1, 2);
  a = 0.5;
  ASSERT_EQ(8, size_count(a));
  ASSERT_DOUBLE_EQ(4, value(sum(a)));
  dvariable v = mean(a);
  ASSERT_DOUBLE_EQ(0.5, value(v));
}
TEST_F(test_dvar3_array, square)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;
  dvar3_array a(1, 2, 1, 2, 1, 2);

  a(1, 1, 1) = 1;
  a(1, 1, 2) = 2;
  a(1, 2, 1) = 3;
  a(1, 2, 2) = 4;
  a(2, 1, 1) = 5;
  a(2, 1, 2) = 6;
  a(2, 2, 1) = 7;
  a(2, 2, 2) = 8;

  dvar3_array result = square(a);
  ASSERT_DOUBLE_EQ(1, value(result(1, 1, 1)));
  ASSERT_DOUBLE_EQ(4, value(result(1, 1, 2)));
  ASSERT_DOUBLE_EQ(9, value(result(1, 2, 1)));
  ASSERT_DOUBLE_EQ(16, value(result(1, 2, 2)));
  ASSERT_DOUBLE_EQ(25, value(result(2, 1, 1)));
  ASSERT_DOUBLE_EQ(36, value(result(2, 1, 2)));
  ASSERT_DOUBLE_EQ(49, value(result(2, 2, 1)));
  ASSERT_DOUBLE_EQ(64, value(result(2, 2, 2)));
}
