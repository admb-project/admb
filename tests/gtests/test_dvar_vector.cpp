#include <gtest/gtest.h>
#include <fvar.hpp>

extern "C"
{
  void test_ad_exit(const int exit_code);
}

class test_dvar_vector:public ::testing::Test {};

TEST_F(test_dvar_vector, default_constructor)
{
  dvar_vector v;

  ASSERT_TRUE(v.va == NULL);
  ASSERT_EQ(v.index_min, 0);
  ASSERT_EQ(v.index_max, -1);
  ASSERT_TRUE(v.link_ptr == NULL);
  ASSERT_TRUE(v.shape == NULL);
}
TEST_F(test_dvar_vector, incorrect_range)
{
  dvar_vector v(5, 1);

  ASSERT_TRUE(v.va == NULL);
  ASSERT_EQ(v.index_min, 0);
  ASSERT_EQ(v.index_max, -1);
  ASSERT_TRUE(v.link_ptr == NULL);
  ASSERT_TRUE(v.shape == NULL);
}
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
TEST_F(test_dvar_vector, min)
{
  gradient_structure gs;

  dvar_vector v(1, 6);
  v.initialize();

  char array[] = "{0, -1, 2, -3, 4, 5}";

  v.fill(array);

  ASSERT_DOUBLE_EQ(-3, value(min(v)));
}
TEST_F(test_dvar_vector, max)
{
  gradient_structure gs;

  dvar_vector v(1, 6);
  v.initialize();

  char array[] = "{0, -1, 2, -3, 4, 5}";

  v.fill(array);

  ASSERT_DOUBLE_EQ(5, value(max(v)));
}
TEST_F(test_dvar_vector, sgn)
{
  gradient_structure gs;

  dvar_vector v(1, 6);
  v.initialize();

  char array[] = "{0, -1, 2, -3, 4, 5}";

  v.fill(array);

  ivector sgn(const dvar_vector& v);

  ivector ret = sgn(v);

  ASSERT_EQ(-1, ret(1));
  ASSERT_EQ(-1, ret(2));
  ASSERT_EQ(1, ret(3));
  ASSERT_EQ(-1, ret(4));
  ASSERT_EQ(1, ret(5));
  ASSERT_EQ(1, ret(6));
}
TEST_F(test_dvar_vector, constructor_fill)
{
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
TEST_F(test_dvar_vector, fill_lbraces_zero)
{
  gradient_structure gs;

  dvar_vector v(1, 6);
  v.initialize();

  char array[] = "0, 1, 2, 3, 4, 5}";

  ad_exit=&test_ad_exit;
  try
  {
    v.fill(array);
  }
  catch (const int exit_code)
  {
    return;
  }
  FAIL();
}
TEST_F(test_dvar_vector, fill_lbraces_greater_than_one)
{
  gradient_structure gs;

  dvar_vector v(1, 6);
  v.initialize();

  char array[] = "{{0, 1, 2, 3, 4, 5}}";

  ad_exit=&test_ad_exit;
  try
  {
    v.fill(array);
  }
  catch (const int exit_code)
  {
    return;
  }
  FAIL();
}
TEST_F(test_dvar_vector, fill_lbraces_not_equal_rbraces)
{
  gradient_structure gs;

  dvar_vector v(1, 6);
  v.initialize();

  char array[] = "{{0, 1, 2, 3, 4, 5}}}";

  ad_exit=&test_ad_exit;
  try
  {
    v.fill(array);
  }
  catch (const int exit_code)
  {
    return;
  }
  FAIL();
}
TEST_F(test_dvar_vector, concatenation)
{
  gradient_structure gs;

  dvar_vector a("{0, 1, 2, 3, 4, 5}");
  dvar_vector b("{-1, -2, -3, -4}");

  dvar_vector ab = a & b;

  ASSERT_EQ(ab.indexmin(), 1);
  ASSERT_EQ(ab.indexmax(), 10);
  ASSERT_DOUBLE_EQ(0, value(ab(1)));
  ASSERT_DOUBLE_EQ(1, value(ab(2)));
  ASSERT_DOUBLE_EQ(2, value(ab(3)));
  ASSERT_DOUBLE_EQ(3, value(ab(4)));
  ASSERT_DOUBLE_EQ(4, value(ab(5)));
  ASSERT_DOUBLE_EQ(5, value(ab(6)));
  ASSERT_DOUBLE_EQ(-1, value(ab(7)));
  ASSERT_DOUBLE_EQ(-2, value(ab(8)));
  ASSERT_DOUBLE_EQ(-3, value(ab(9)));
  ASSERT_DOUBLE_EQ(-4, value(ab(10)));
}
TEST_F(test_dvar_vector, deallocatecopies)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;

  dvar_vector a(1, 2);
  ASSERT_EQ(0, a.get_ncopies());
  dvar_vector firstcopy(a);
  ASSERT_EQ(1, a.get_ncopies());
  ASSERT_EQ(1, firstcopy.get_ncopies());
  dvar_vector secondcopy(a);
  ASSERT_EQ(2, a.get_ncopies());
  ASSERT_EQ(2, firstcopy.get_ncopies());
  ASSERT_EQ(2, secondcopy.get_ncopies());

  firstcopy.deallocate();
  ASSERT_EQ(1, a.get_ncopies());
  ASSERT_EQ(0, firstcopy.get_ncopies());
  ASSERT_EQ(1, secondcopy.get_ncopies());

  secondcopy.deallocate();
  ASSERT_EQ(0, a.get_ncopies());
  ASSERT_EQ(0, firstcopy.get_ncopies());
  ASSERT_EQ(0, secondcopy.get_ncopies());
}
TEST_F(test_dvar_vector, division_operator)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;

  independent_variables independents(1, 4);
  independents(1) = -4.2;
  independents(2) = 4.2;
  independents(3) = 10.2;
  independents(4) = -14.2;

  dvar_vector a(independents);

  dvar_vector results(1, 4);

  results = a / 0.5;

  ASSERT_DOUBLE_EQ(value(results(1)), value(a(1)) * 2.0);
  ASSERT_DOUBLE_EQ(value(results(2)), value(a(2)) * 2.0);
  ASSERT_DOUBLE_EQ(value(results(3)), value(a(3)) * 2.0);
  ASSERT_DOUBLE_EQ(value(results(4)), value(a(4)) * 2.0);

  dvariable total = results(1) + results(2) + results(3) + results(4);
  //dvariable total = sum(results);

  double v = value(total);
  ASSERT_DOUBLE_EQ(v, 2.0 * sum(independents));

  dvector gradients(1, 4);

  gradcalc(4, gradients);

  ASSERT_DOUBLE_EQ(gradients(1), 2.0);
  ASSERT_DOUBLE_EQ(gradients(2), 2.0);
  ASSERT_DOUBLE_EQ(gradients(3), 2.0);
  ASSERT_DOUBLE_EQ(gradients(4), 2.0);
}
TEST_F(test_dvar_vector, substract_operator)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;

  independent_variables independents(1, 4);
  independents(1) = -4.2;
  independents(2) = 4.2;
  independents(3) = 10.2;
  independents(4) = -14.2;

  dvar_vector a(independents);

  dvar_vector results(1, 4);

  results = a - 0.5;

  ASSERT_DOUBLE_EQ(value(results(1)), value(a(1)) - 0.5);
  ASSERT_DOUBLE_EQ(value(results(2)), value(a(2)) - 0.5);
  ASSERT_DOUBLE_EQ(value(results(3)), value(a(3)) - 0.5);
  ASSERT_DOUBLE_EQ(value(results(4)), value(a(4)) - 0.5);

  dvariable total = results(1) + results(2) + results(3) + results(4);
  //dvariable total = sum(results);

  double v = value(total);
  ASSERT_DOUBLE_EQ(v, sum(independents) - 2.0);

  dvector gradients(1, 4);

  gradcalc(4, gradients);

  ASSERT_DOUBLE_EQ(gradients(1), 1.0);
  ASSERT_DOUBLE_EQ(gradients(2), 1.0);
  ASSERT_DOUBLE_EQ(gradients(3), 1.0);
  ASSERT_DOUBLE_EQ(gradients(4), 1.0);
}
TEST_F(test_dvar_vector, unary_plus_operator)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;

  independent_variables independents(1, 4);
  independents(1) = -4.2;
  independents(2) = 4.2;
  independents(3) = 10.2;
  independents(4) = -14.2;

  dvar_vector a(independents);

  dvariable d;
  d = a(1);

  a += d;

  ASSERT_DOUBLE_EQ(value(a(1)), independents(1) + independents(1));
  ASSERT_DOUBLE_EQ(value(a(2)), independents(2) + independents(1));
  ASSERT_DOUBLE_EQ(value(a(3)), independents(3) + independents(1));
  ASSERT_DOUBLE_EQ(value(a(4)), independents(4) + independents(1));

  dvariable total = a(1) + a(2) + a(3) + a(4);
  //dvariable total = sum(results);

  double v = value(total);
  ASSERT_DOUBLE_EQ(v, sum(independents) + 4.0 * independents(1));

  dvector gradients(1, 4);

  gradcalc(4, gradients);

  ASSERT_DOUBLE_EQ(gradients(1), 5.0);
  ASSERT_DOUBLE_EQ(gradients(2), 1.0);
  ASSERT_DOUBLE_EQ(gradients(3), 1.0);
  ASSERT_DOUBLE_EQ(gradients(4), 1.0);
}
TEST_F(test_dvar_vector, unary_minus_operator)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;

  independent_variables independents(1, 4);
  independents(1) = -4.2;
  independents(2) = 4.2;
  independents(3) = 10.2;
  independents(4) = -14.2;

  dvar_vector a(independents);

  dvariable d;
  d = a(1);

  a -= d;

  ASSERT_DOUBLE_EQ(value(a(1)), independents(1) - independents(1));
  ASSERT_DOUBLE_EQ(value(a(2)), independents(2) - independents(1));
  ASSERT_DOUBLE_EQ(value(a(3)), independents(3) - independents(1));
  ASSERT_DOUBLE_EQ(value(a(4)), independents(4) - independents(1));

  dvariable total = a(1) + a(2) + a(3) + a(4);
  //dvariable total = sum(results);

  double v = value(total);
  ASSERT_DOUBLE_EQ(v, sum(independents) - 4.0 * independents(1));

  dvector gradients(1, 4);

  gradcalc(4, gradients);

  ASSERT_DOUBLE_EQ(gradients(1), -3.0);
  ASSERT_DOUBLE_EQ(gradients(2), 1.0);
  ASSERT_DOUBLE_EQ(gradients(3), 1.0);
  ASSERT_DOUBLE_EQ(gradients(4), 1.0);
}
TEST_F(test_dvar_vector, unary_double_plus_operator)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;

  independent_variables independents(1, 4);
  independents(1) = -4.2;
  independents(2) = 4.2;
  independents(3) = 10.2;
  independents(4) = -14.2;

  dvar_vector a(independents);

  double d = independents(1);

  a += d;

  ASSERT_DOUBLE_EQ(value(a(1)), independents(1) + independents(1));
  ASSERT_DOUBLE_EQ(value(a(2)), independents(2) + independents(1));
  ASSERT_DOUBLE_EQ(value(a(3)), independents(3) + independents(1));
  ASSERT_DOUBLE_EQ(value(a(4)), independents(4) + independents(1));

  dvariable total = a(1) + a(2) + a(3) + a(4);
  //dvariable total = sum(results);

  double v = value(total);
  ASSERT_DOUBLE_EQ(v, sum(independents) + 4.0 * independents(1));

  dvector gradients(1, 4);

  gradcalc(4, gradients);

  ASSERT_DOUBLE_EQ(gradients(1), 1.0);
  ASSERT_DOUBLE_EQ(gradients(2), 1.0);
  ASSERT_DOUBLE_EQ(gradients(3), 1.0);
  ASSERT_DOUBLE_EQ(gradients(4), 1.0);
}
TEST_F(test_dvar_vector, unary_double_minus_operator)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;

  independent_variables independents(1, 4);
  independents(1) = -4.2;
  independents(2) = 4.2;
  independents(3) = 10.2;
  independents(4) = -14.2;

  dvar_vector a(independents);

  double d = independents(1);

  a -= d;

  ASSERT_DOUBLE_EQ(value(a(1)), independents(1) - independents(1));
  ASSERT_DOUBLE_EQ(value(a(2)), independents(2) - independents(1));
  ASSERT_DOUBLE_EQ(value(a(3)), independents(3) - independents(1));
  ASSERT_DOUBLE_EQ(value(a(4)), independents(4) - independents(1));

  dvariable total = a(1) + a(2) + a(3) + a(4);
  //dvariable total = sum(results);

  double v = value(total);
  ASSERT_DOUBLE_EQ(v, sum(independents) - 4.0 * independents(1));

  dvector gradients(1, 4);

  gradcalc(4, gradients);

  ASSERT_DOUBLE_EQ(gradients(1), 1.0);
  ASSERT_DOUBLE_EQ(gradients(2), 1.0);
  ASSERT_DOUBLE_EQ(gradients(3), 1.0);
  ASSERT_DOUBLE_EQ(gradients(4), 1.0);
}
TEST_F(test_dvar_vector, dvcv_elem_div)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;

  independent_variables independents(1, 4);
  independents(1) = -4.2;
  independents(2) = 4.2;
  independents(3) = 10.2;
  independents(4) = -14.2;

  dvar_vector a(independents);

  dvar_vector results(1, 4);

  results = elem_div(a, independents);

  ASSERT_DOUBLE_EQ(value(results(1)), 1.0);
  ASSERT_DOUBLE_EQ(value(results(2)), 1.0);
  ASSERT_DOUBLE_EQ(value(results(3)), 1.0);
  ASSERT_DOUBLE_EQ(value(results(4)), 1.0);

  dvariable total = results(1) + results(2) + results(3) + results(4);
  //dvariable total = sum(results);

  double v = value(total);
  ASSERT_DOUBLE_EQ(v, 4.0);

  dvector gradients(1, 4);

  gradcalc(4, gradients);

  ASSERT_DOUBLE_EQ(gradients(1), 1.0 / independents(1));
  ASSERT_DOUBLE_EQ(gradients(2), 1.0 / independents(2));
  ASSERT_DOUBLE_EQ(gradients(3), 1.0 / independents(3));
  ASSERT_DOUBLE_EQ(gradients(4), 1.0 / independents(4));
}
TEST_F(test_dvar_vector, sine)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;

  independent_variables independents(1, 4);
  independents(1) = -4.2;
  independents(2) = 4.2;
  independents(3) = 10.2;
  independents(4) = -14.2;

  dvar_vector a(independents);

  dvar_vector results(1, 4);

  dvar_vector sin(const dvar_vector&);

  results = sin(a);

  ASSERT_DOUBLE_EQ(value(results(1)), std::sin(independents(1)));
  ASSERT_DOUBLE_EQ(value(results(2)), std::sin(independents(2)));
  ASSERT_DOUBLE_EQ(value(results(3)), std::sin(independents(3)));
  ASSERT_DOUBLE_EQ(value(results(4)), std::sin(independents(4)));

  dvariable total = results(1) + results(2) + results(3) + results(4);
  //dvariable total = sum(results);

  double v = value(total);
  double expected_v =
    std::sin(independents(1))
    + std::sin(independents(2))
    + std::sin(independents(3))
    + std::sin(independents(4));
  ASSERT_DOUBLE_EQ(v, expected_v);

  dvector gradients(1, 4);

  gradcalc(4, gradients);

  ASSERT_DOUBLE_EQ(gradients(1), cos(independents(1)));
  ASSERT_DOUBLE_EQ(gradients(2), cos(independents(2)));
  ASSERT_DOUBLE_EQ(gradients(3), cos(independents(3)));
  ASSERT_DOUBLE_EQ(gradients(4), cos(independents(4)));
}
TEST_F(test_dvar_vector, tan)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;

  independent_variables independents(1, 4);
  independents(1) = -4.2;
  independents(2) = 4.2;
  independents(3) = 10.2;
  independents(4) = -14.2;

  dvar_vector a(independents);

  dvar_vector results(1, 4);

  dvar_vector tan(const dvar_vector&);

  results = tan(a);

  ASSERT_DOUBLE_EQ(value(results(1)), std::tan(independents(1)));
  ASSERT_DOUBLE_EQ(value(results(2)), std::tan(independents(2)));
  ASSERT_DOUBLE_EQ(value(results(3)), std::tan(independents(3)));
  ASSERT_DOUBLE_EQ(value(results(4)), std::tan(independents(4)));

  dvariable total = results(1) + results(2) + results(3) + results(4);
  //dvariable total = sum(results);

  double v = value(total);
  double expected_v =
    std::tan(independents(1))
    + std::tan(independents(2))
    + std::tan(independents(3))
    + std::tan(independents(4));
  ASSERT_DOUBLE_EQ(v, expected_v);

  dvector gradients(1, 4);

  gradcalc(4, gradients);

  ASSERT_DOUBLE_EQ(gradients(1), std::pow(cos(independents(1)), -2.0));
  ASSERT_DOUBLE_EQ(gradients(2), std::pow(cos(independents(2)), -2.0));
  ASSERT_DOUBLE_EQ(gradients(3), std::pow(cos(independents(3)), -2.0));
  ASSERT_DOUBLE_EQ(gradients(4), std::pow(cos(independents(4)), -2.0));
}
TEST_F(test_dvar_vector, atan)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;

  independent_variables independents(1, 4);
  independents(1) = -4.2;
  independents(2) = 4.2;
  independents(3) = 10.2;
  independents(4) = -14.2;

  dvar_vector a(independents);

  dvar_vector results(1, 4);

  dvar_vector tan(const dvar_vector&);

  results = atan(a);

  ASSERT_DOUBLE_EQ(value(results(1)), std::atan(independents(1)));
  ASSERT_DOUBLE_EQ(value(results(2)), std::atan(independents(2)));
  ASSERT_DOUBLE_EQ(value(results(3)), std::atan(independents(3)));
  ASSERT_DOUBLE_EQ(value(results(4)), std::atan(independents(4)));

  dvariable total = results(1) + results(2) + results(3) + results(4);
  //dvariable total = sum(results);

  double v = value(total);
  double expected_v =
    std::atan(independents(1))
    + std::atan(independents(2))
    + std::atan(independents(3))
    + std::atan(independents(4));
  ASSERT_DOUBLE_EQ(v, expected_v);

  dvector gradients(1, 4);

  gradcalc(4, gradients);

  ASSERT_DOUBLE_EQ(gradients(1), 1.0 / (1.0 + std::pow(independents(1), 2.0)));
  ASSERT_DOUBLE_EQ(gradients(2), 1.0 / (1.0 + std::pow(independents(2), 2.0)));
  ASSERT_DOUBLE_EQ(gradients(3), 1.0 / (1.0 + std::pow(independents(3), 2.0)));
  ASSERT_DOUBLE_EQ(gradients(4), 1.0 / (1.0 + std::pow(independents(4), 2.0)));
}
TEST_F(test_dvar_vector, sqrt)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;

  independent_variables independents(1, 4);
  independents(1) = 40.2;
  independents(2) = 4.2;
  independents(3) = 10.2;
  independents(4) = 14.2;

  dvar_vector a(independents);

  dvar_vector results(1, 4);

  dvar_vector sqrt(const dvar_vector&);

  results = sqrt(a);

  ASSERT_DOUBLE_EQ(value(results(1)), std::sqrt(independents(1)));
  ASSERT_DOUBLE_EQ(value(results(2)), std::sqrt(independents(2)));
  ASSERT_DOUBLE_EQ(value(results(3)), std::sqrt(independents(3)));
  ASSERT_DOUBLE_EQ(value(results(4)), std::sqrt(independents(4)));

  dvariable total = results(1) + results(2) + results(3) + results(4);
  //dvariable total = sum(results);

  double v = value(total);
  double expected_v =
    std::sqrt(independents(1))
    + std::sqrt(independents(2))
    + std::sqrt(independents(3))
    + std::sqrt(independents(4));
  ASSERT_DOUBLE_EQ(v, expected_v);

  dvector gradients(1, 4);

  gradcalc(4, gradients);

  ASSERT_DOUBLE_EQ(gradients(1), 1.0 / (2.0 * std::sqrt(independents(1))));
  ASSERT_DOUBLE_EQ(gradients(2), 1.0 / (2.0 * std::sqrt(independents(2))));
  ASSERT_DOUBLE_EQ(gradients(3), 1.0 / (2.0 * std::sqrt(independents(3))));
  ASSERT_DOUBLE_EQ(gradients(4), 1.0 / (2.0 * std::sqrt(independents(4))));
}
TEST_F(test_dvar_vector, sqrvariable)
{
  ad_exit=&test_ad_exit;

  gradient_structure gs;

  independent_variables independents(1, 4);
  independents(1) = -40.2;
  independents(2) = 4.2;
  independents(3) = 10.2;
  independents(4) = -14.2;

  dvar_vector a(independents);

  dvariable total = sqr(a(1)) + sqr(a(2)) + sqr(a(3)) + sqr(a(4));

  double v = value(total);
  double expected_v =
    std::pow(independents(1), 2.0)
    + std::pow(independents(2), 2.0)
    + std::pow(independents(3), 2.0)
    + std::pow(independents(4), 2.0);
  ASSERT_DOUBLE_EQ(v, expected_v);

  dvector gradients(1, 4);

  gradcalc(4, gradients);

  ASSERT_DOUBLE_EQ(gradients(1), 2.0 * independents(1));
  ASSERT_DOUBLE_EQ(gradients(2), 2.0 * independents(2));
  ASSERT_DOUBLE_EQ(gradients(3), 2.0 * independents(3));
  ASSERT_DOUBLE_EQ(gradients(4), 2.0 * independents(4));
}
