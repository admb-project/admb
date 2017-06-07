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
TEST_F(test_dvar3_array, division)
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

  dvariable d;
  d = 1;
  dvar3_array result = d / a;
  ASSERT_DOUBLE_EQ(1.0 / 1, value(result(1, 1, 1)));
  ASSERT_DOUBLE_EQ(1.0 / 2, value(result(1, 1, 2)));
  ASSERT_DOUBLE_EQ(1.0 / 3, value(result(1, 2, 1)));
  ASSERT_DOUBLE_EQ(1.0 / 4, value(result(1, 2, 2)));
  ASSERT_DOUBLE_EQ(1.0 / 5, value(result(2, 1, 1)));
  ASSERT_DOUBLE_EQ(1.0 / 6, value(result(2, 1, 2)));
  ASSERT_DOUBLE_EQ(1.0 / 7, value(result(2, 2, 1)));
  ASSERT_DOUBLE_EQ(1.0 / 8, value(result(2, 2, 2)));
}
TEST_F(test_dvar3_array, division2)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;
  d3_array a(1, 2, 1, 2, 1, 2);

  a(1, 1, 1) = 1;
  a(1, 1, 2) = 2;
  a(1, 2, 1) = 3;
  a(1, 2, 2) = 4;
  a(2, 1, 1) = 5;
  a(2, 1, 2) = 6;
  a(2, 2, 1) = 7;
  a(2, 2, 2) = 8;

  dvariable d;
  d = 1;
  dvar3_array result = d / a;
  ASSERT_DOUBLE_EQ(1.0 / 1, value(result(1, 1, 1)));
  ASSERT_DOUBLE_EQ(1.0 / 2, value(result(1, 1, 2)));
  ASSERT_DOUBLE_EQ(1.0 / 3, value(result(1, 2, 1)));
  ASSERT_DOUBLE_EQ(1.0 / 4, value(result(1, 2, 2)));
  ASSERT_DOUBLE_EQ(1.0 / 5, value(result(2, 1, 1)));
  ASSERT_DOUBLE_EQ(1.0 / 6, value(result(2, 1, 2)));
  ASSERT_DOUBLE_EQ(1.0 / 7, value(result(2, 2, 1)));
  ASSERT_DOUBLE_EQ(1.0 / 8, value(result(2, 2, 2)));
}
TEST_F(test_dvar3_array, division3)
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

  double d;
  d = 1;
  dvar3_array result = d / a;
  ASSERT_DOUBLE_EQ(1.0 / 1, value(result(1, 1, 1)));
  ASSERT_DOUBLE_EQ(1.0 / 2, value(result(1, 1, 2)));
  ASSERT_DOUBLE_EQ(1.0 / 3, value(result(1, 2, 1)));
  ASSERT_DOUBLE_EQ(1.0 / 4, value(result(1, 2, 2)));
  ASSERT_DOUBLE_EQ(1.0 / 5, value(result(2, 1, 1)));
  ASSERT_DOUBLE_EQ(1.0 / 6, value(result(2, 1, 2)));
  ASSERT_DOUBLE_EQ(1.0 / 7, value(result(2, 2, 1)));
  ASSERT_DOUBLE_EQ(1.0 / 8, value(result(2, 2, 2)));
}
TEST_F(test_dvar3_array, value)
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

  double d;
  d = 1;
  d3_array result = value(a);
  ASSERT_DOUBLE_EQ(1, result(1, 1, 1));
  ASSERT_DOUBLE_EQ(2, result(1, 1, 2));
  ASSERT_DOUBLE_EQ(3, result(1, 2, 1));
  ASSERT_DOUBLE_EQ(4, result(1, 2, 2));
  ASSERT_DOUBLE_EQ(5, result(2, 1, 1));
  ASSERT_DOUBLE_EQ(6, result(2, 1, 2));
  ASSERT_DOUBLE_EQ(7, result(2, 2, 1));
  ASSERT_DOUBLE_EQ(8, result(2, 2, 2));
}
TEST_F(test_dvar3_array, cube)
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

  dvar3_array result = cube(a);
  ASSERT_DOUBLE_EQ(1 * 1 * 1, value(result(1, 1, 1)));
  ASSERT_DOUBLE_EQ(2 * 2 * 2, value(result(1, 1, 2)));
  ASSERT_DOUBLE_EQ(3 * 3 * 3, value(result(1, 2, 1)));
  ASSERT_DOUBLE_EQ(4 * 4 * 4, value(result(1, 2, 2)));
  ASSERT_DOUBLE_EQ(5 * 5 * 5, value(result(2, 1, 1)));
  ASSERT_DOUBLE_EQ(6 * 6 * 6, value(result(2, 1, 2)));
  ASSERT_DOUBLE_EQ(7 * 7 * 7, value(result(2, 2, 1)));
  ASSERT_DOUBLE_EQ(8 * 8 * 8, value(result(2, 2, 2)));
}
TEST_F(test_dvar3_array, elem_prod)
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

  dvar3_array result = elem_prod(a, a);
  ASSERT_DOUBLE_EQ(1 * 1, value(result(1, 1, 1)));
  ASSERT_DOUBLE_EQ(2 * 2, value(result(1, 1, 2)));
  ASSERT_DOUBLE_EQ(3 * 3, value(result(1, 2, 1)));
  ASSERT_DOUBLE_EQ(4 * 4, value(result(1, 2, 2)));
  ASSERT_DOUBLE_EQ(5 * 5, value(result(2, 1, 1)));
  ASSERT_DOUBLE_EQ(6 * 6, value(result(2, 1, 2)));
  ASSERT_DOUBLE_EQ(7 * 7, value(result(2, 2, 1)));
  ASSERT_DOUBLE_EQ(8 * 8, value(result(2, 2, 2)));
}
TEST_F(test_dvar3_array, elem_div)
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

  dvar3_array result = elem_div(a, a);
  ASSERT_DOUBLE_EQ(1, value(result(1, 1, 1)));
  ASSERT_DOUBLE_EQ(1, value(result(1, 1, 2)));
  ASSERT_DOUBLE_EQ(1, value(result(1, 2, 1)));
  ASSERT_DOUBLE_EQ(1, value(result(1, 2, 2)));
  ASSERT_DOUBLE_EQ(1, value(result(2, 1, 1)));
  ASSERT_DOUBLE_EQ(1, value(result(2, 1, 2)));
  ASSERT_DOUBLE_EQ(1, value(result(2, 2, 1)));
  ASSERT_DOUBLE_EQ(1, value(result(2, 2, 2)));
}
TEST_F(test_dvar3_array, operator_plus)
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

  dvar3_array result = a + a;
  ASSERT_DOUBLE_EQ(1 + 1, value(result(1, 1, 1)));
  ASSERT_DOUBLE_EQ(2 + 2, value(result(1, 1, 2)));
  ASSERT_DOUBLE_EQ(3 + 3, value(result(1, 2, 1)));
  ASSERT_DOUBLE_EQ(4 + 4, value(result(1, 2, 2)));
  ASSERT_DOUBLE_EQ(5 + 5, value(result(2, 1, 1)));
  ASSERT_DOUBLE_EQ(6 + 6, value(result(2, 1, 2)));
  ASSERT_DOUBLE_EQ(7 + 7, value(result(2, 2, 1)));
  ASSERT_DOUBLE_EQ(8 + 8, value(result(2, 2, 2)));
}
TEST_F(test_dvar3_array, operator_minus)
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

  dvar3_array result = a - a;
  ASSERT_DOUBLE_EQ(1 - 1, value(result(1, 1, 1)));
  ASSERT_DOUBLE_EQ(2 - 2, value(result(1, 1, 2)));
  ASSERT_DOUBLE_EQ(3 - 3, value(result(1, 2, 1)));
  ASSERT_DOUBLE_EQ(4 - 4, value(result(1, 2, 2)));
  ASSERT_DOUBLE_EQ(5 - 5, value(result(2, 1, 1)));
  ASSERT_DOUBLE_EQ(6 - 6, value(result(2, 1, 2)));
  ASSERT_DOUBLE_EQ(7 - 7, value(result(2, 2, 1)));
  ASSERT_DOUBLE_EQ(8 - 8, value(result(2, 2, 2)));
}
TEST_F(test_dvar3_array, operator_plus_single)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;
  d3_array a(1, 2, 1, 2, 1, 2);

  a(1, 1, 1) = 1;
  a(1, 1, 2) = 2;
  a(1, 2, 1) = 3;
  a(1, 2, 2) = 4;
  a(2, 1, 1) = 5;
  a(2, 1, 2) = 6;
  a(2, 2, 1) = 7;
  a(2, 2, 2) = 8;

  dvariable d;
  d = 2;

  dvar3_array result = d + a;
  ASSERT_DOUBLE_EQ(2 + 1, value(result(1, 1, 1)));
  ASSERT_DOUBLE_EQ(2 + 2, value(result(1, 1, 2)));
  ASSERT_DOUBLE_EQ(2 + 3, value(result(1, 2, 1)));
  ASSERT_DOUBLE_EQ(2 + 4, value(result(1, 2, 2)));
  ASSERT_DOUBLE_EQ(2 + 5, value(result(2, 1, 1)));
  ASSERT_DOUBLE_EQ(2 + 6, value(result(2, 1, 2)));
  ASSERT_DOUBLE_EQ(2 + 7, value(result(2, 2, 1)));
  ASSERT_DOUBLE_EQ(2 + 8, value(result(2, 2, 2)));
}
TEST_F(test_dvar3_array, operator_minus_single)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;
  d3_array a(1, 2, 1, 2, 1, 2);

  a(1, 1, 1) = 1;
  a(1, 1, 2) = 2;
  a(1, 2, 1) = 3;
  a(1, 2, 2) = 4;
  a(2, 1, 1) = 5;
  a(2, 1, 2) = 6;
  a(2, 2, 1) = 7;
  a(2, 2, 2) = 8;

  dvariable d;
  d = 2;

  dvar3_array result = d - a;
  ASSERT_DOUBLE_EQ(2 - 1, value(result(1, 1, 1)));
  ASSERT_DOUBLE_EQ(2 - 2, value(result(1, 1, 2)));
  ASSERT_DOUBLE_EQ(2 - 3, value(result(1, 2, 1)));
  ASSERT_DOUBLE_EQ(2 - 4, value(result(1, 2, 2)));
  ASSERT_DOUBLE_EQ(2 - 5, value(result(2, 1, 1)));
  ASSERT_DOUBLE_EQ(2 - 6, value(result(2, 1, 2)));
  ASSERT_DOUBLE_EQ(2 - 7, value(result(2, 2, 1)));
  ASSERT_DOUBLE_EQ(2 - 8, value(result(2, 2, 2)));
}
TEST_F(test_dvar3_array, pow)
{
  gradient_structure gs;

  d3_array a(1, 2, 1, 2, 1, 2);

  double d = 2.0;
  for (int i = 1; i <= 2; ++i)
  {
    for (int j = 1; j <= 2; ++j)
    {
      for (int k = 1; k <= 2; ++k)
      {
        a(i, j, k) = d;
        d += 2.0;
      }
    }
  }

  d3_array ret = pow(a, 2.0);

  d = 2.0;
  for (int i = 1; i <= 2; ++i)
  {
    for (int j = 1; j <= 2; ++j)
    {
      for (int k = 1; k <= 2; ++k)
      {
        ASSERT_DOUBLE_EQ(std::pow(d,  2.0), ret(i, j, k));
        d += 2.0;
      }
    }
  }
}
