#include <gtest/gtest.h>
#include <fvar.hpp>

extern "C"
{
  void test_ad_exit(const int exit_code);
}

class test_math: public ::testing::Test {};

TEST_F(test_math, outer_product)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;

  independent_variables independents(1, 3);
  independents(1) = 28.2;
  independents(2) = -24.2;
  independents(3) = 10.2;

  dvar_vector a(independents);

  dvector b(1, 3);
  b(1) = 2.0;
  b(2) = 3.0;
  b(3) = 4.0;

  dvar_matrix results(1, 3, 1, 3);

  results = outer_prod(b, a);

  ASSERT_DOUBLE_EQ(value(results(1, 1)), b(1) * independents(1));
  ASSERT_DOUBLE_EQ(value(results(1, 2)), b(1) * independents(2));
  ASSERT_DOUBLE_EQ(value(results(1, 3)), b(1) * independents(3));
  ASSERT_DOUBLE_EQ(value(results(2, 1)), b(2) * independents(1));
  ASSERT_DOUBLE_EQ(value(results(2, 2)), b(2) * independents(2));
  ASSERT_DOUBLE_EQ(value(results(2, 3)), b(2) * independents(3));
  ASSERT_DOUBLE_EQ(value(results(3, 1)), b(3) * independents(1));
  ASSERT_DOUBLE_EQ(value(results(3, 2)), b(3) * independents(2));
  ASSERT_DOUBLE_EQ(value(results(3, 3)), b(3) * independents(3));

  dvariable total =
    results(1, 1)
    + results(1, 2)
    + results(1, 3)
    + results(2, 1)
    + results(2, 2)
    + results(2, 3)
    + results(3, 1)
    + results(3, 2)
    + results(3, 3);

  double v = value(total);
  double expected_v =
    b(1) * independents(1)
    + b(1) * independents(2)
    + b(1) * independents(3)
    + b(2) * independents(1)
    + b(2) * independents(2)
    + b(2) * independents(3)
    + b(3) * independents(1)
    + b(3) * independents(2)
    + b(3) * independents(3);
  ASSERT_DOUBLE_EQ(v, expected_v);

  dvector gradients(1, 3);

  gradcalc(3, gradients);

  ASSERT_DOUBLE_EQ(gradients(1), b(1) + b(2) + b(3));
  ASSERT_DOUBLE_EQ(gradients(2), b(1) + b(2) + b(3));
  ASSERT_DOUBLE_EQ(gradients(3), b(1) + b(2) + b(3));
}
TEST_F(test_math, outer_product2)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;

  independent_variables independents(1, 3);
  independents(1) = 28.2;
  independents(2) = -24.2;
  independents(3) = 10.2;

  dvar_vector a(independents);

  dvector b(1, 3);
  b(1) = 2.0;
  b(2) = 3.0;
  b(3) = 4.0;

  dvar_matrix results(1, 3, 1, 3);

  results = outer_prod(a, b);

  ASSERT_DOUBLE_EQ(value(results(1, 1)), b(1) * independents(1));
  ASSERT_DOUBLE_EQ(value(results(1, 2)), b(2) * independents(1));
  ASSERT_DOUBLE_EQ(value(results(1, 3)), b(3) * independents(1));
  ASSERT_DOUBLE_EQ(value(results(2, 1)), b(1) * independents(2));
  ASSERT_DOUBLE_EQ(value(results(2, 2)), b(2) * independents(2));
  ASSERT_DOUBLE_EQ(value(results(2, 3)), b(3) * independents(2));
  ASSERT_DOUBLE_EQ(value(results(3, 1)), b(1) * independents(3));
  ASSERT_DOUBLE_EQ(value(results(3, 2)), b(2) * independents(3));
  ASSERT_DOUBLE_EQ(value(results(3, 3)), b(3) * independents(3));

  dvariable total =
    results(1, 1)
    + results(1, 2)
    + results(1, 3)
    + results(2, 1)
    + results(2, 2)
    + results(2, 3)
    + results(3, 1)
    + results(3, 2)
    + results(3, 3);

  double v = value(total);
  double expected_v =
    b(1) * independents(1)
    + b(1) * independents(2)
    + b(1) * independents(3)
    + b(2) * independents(1)
    + b(2) * independents(2)
    + b(2) * independents(3)
    + b(3) * independents(1)
    + b(3) * independents(2)
    + b(3) * independents(3);
  ASSERT_DOUBLE_EQ(v, expected_v);

  dvector gradients(1, 3);

  gradcalc(3, gradients);

  ASSERT_DOUBLE_EQ(gradients(1), b(1) + b(2) + b(3));
  ASSERT_DOUBLE_EQ(gradients(2), b(1) + b(2) + b(3));
  ASSERT_DOUBLE_EQ(gradients(3), b(1) + b(2) + b(3));
}
