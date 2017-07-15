#include <gtest/gtest.h>
#include <fvar.hpp>
#include <admodel.h>
#include <climits>

extern "C"
{
  void test_ad_exit(const int exit_code);
}

class test_dvector: public ::testing::Test {};

TEST_F(test_dvector, constructor)
{
  ad_exit=&test_ad_exit;

  try
  {
    dvector v(1, 10);
    dvector w(0, 1000);
    v(0, 1000) = w;
  }
  catch (const int exit_code)
  {
    const int expected_exit_code = 1;
    if (exit_code == expected_exit_code)
    {
      return;
    }
  }
  FAIL();
}
TEST_F(test_dvector, sqr)
{
  char array[] = "{0, -1.5, 2, -3, 4, 5.1}";
  dvector v(array);

  dvector results = sqr(v);

  ASSERT_DOUBLE_EQ(0, results(1));
  ASSERT_DOUBLE_EQ(std::pow(-1.5, 2), results(2));
  ASSERT_DOUBLE_EQ(4, results(3));
  ASSERT_DOUBLE_EQ(9, results(4));
  ASSERT_DOUBLE_EQ(16, results(5));
  ASSERT_DOUBLE_EQ(std::pow(5.1, 2), results(6));
}
TEST_F(test_dvector, log10)
{
  char array[] = "{0.5, 1.5, 2, 3, 4, 5.1}";
  dvector v(array);

  dvector results = log10(v);

  ASSERT_DOUBLE_EQ(std::log10(v[1]), results(1));
  ASSERT_DOUBLE_EQ(std::log10(v[2]), results(2));
  ASSERT_DOUBLE_EQ(std::log10(v[3]), results(3));
  ASSERT_DOUBLE_EQ(std::log10(v[4]), results(4));
  ASSERT_DOUBLE_EQ(std::log10(v[5]), results(5));
  ASSERT_DOUBLE_EQ(std::log10(v[6]), results(6));
}
TEST_F(test_dvector, atan)
{
  char array[] = "{0.5, 1.5, 2, 3, 4, 5.1}";
  dvector v(array);

  dvector results = atan(v);

  ASSERT_DOUBLE_EQ(std::atan(v[1]), results(1));
  ASSERT_DOUBLE_EQ(std::atan(v[2]), results(2));
  ASSERT_DOUBLE_EQ(std::atan(v[3]), results(3));
  ASSERT_DOUBLE_EQ(std::atan(v[4]), results(4));
  ASSERT_DOUBLE_EQ(std::atan(v[5]), results(5));
  ASSERT_DOUBLE_EQ(std::atan(v[6]), results(6));
}
TEST_F(test_dvector, tan)
{
  char array[] = "{0.5, 1.5, 2, 3, 4, 5.1}";
  dvector v(array);

  dvector results = tan(v);

  ASSERT_DOUBLE_EQ(std::tan(v[1]), results(1));
  ASSERT_DOUBLE_EQ(std::tan(v[2]), results(2));
  ASSERT_DOUBLE_EQ(std::tan(v[3]), results(3));
  ASSERT_DOUBLE_EQ(std::tan(v[4]), results(4));
  ASSERT_DOUBLE_EQ(std::tan(v[5]), results(5));
  ASSERT_DOUBLE_EQ(std::tan(v[6]), results(6));
}
TEST_F(test_dvector, acos)
{
  char array[] = "{0.5, -0.5, 0, 0.75, -0.75, 1, -1}";
  dvector v(array);

  dvector results = acos(v);

  ASSERT_DOUBLE_EQ(std::acos(v[1]), results(1));
  ASSERT_DOUBLE_EQ(std::acos(v[2]), results(2));
  ASSERT_DOUBLE_EQ(std::acos(v[3]), results(3));
  ASSERT_DOUBLE_EQ(std::acos(v[4]), results(4));
  ASSERT_DOUBLE_EQ(std::acos(v[5]), results(5));
  ASSERT_DOUBLE_EQ(std::acos(v[6]), results(6));
  ASSERT_DOUBLE_EQ(std::acos(v[7]), results(7));
}
TEST_F(test_dvector, tanh)
{
  char array[] = "{0.5, -0.5, 0, 0.75, -0.75, 1, -1}";
  dvector v(array);

  dvector results = tanh(v);

  ASSERT_DOUBLE_EQ(std::tanh(v[1]), results(1));
  ASSERT_DOUBLE_EQ(std::tanh(v[2]), results(2));
  ASSERT_DOUBLE_EQ(std::tanh(v[3]), results(3));
  ASSERT_DOUBLE_EQ(std::tanh(v[4]), results(4));
  ASSERT_DOUBLE_EQ(std::tanh(v[5]), results(5));
  ASSERT_DOUBLE_EQ(std::tanh(v[6]), results(6));
  ASSERT_DOUBLE_EQ(std::tanh(v[7]), results(7));
}
TEST_F(test_dvector, cosh)
{
  char array[] = "{0.5, -0.5, 0, 0.75, -0.75, 1, -1}";
  dvector v(array);

  dvector results = cosh(v);

  ASSERT_DOUBLE_EQ(std::cosh(v[1]), results(1));
  ASSERT_DOUBLE_EQ(std::cosh(v[2]), results(2));
  ASSERT_DOUBLE_EQ(std::cosh(v[3]), results(3));
  ASSERT_DOUBLE_EQ(std::cosh(v[4]), results(4));
  ASSERT_DOUBLE_EQ(std::cosh(v[5]), results(5));
  ASSERT_DOUBLE_EQ(std::cosh(v[6]), results(6));
  ASSERT_DOUBLE_EQ(std::cosh(v[7]), results(7));
}
TEST_F(test_dvector, sinh)
{
  char array[] = "{0.5, -0.5, 0, 0.75, -0.75, 1, -1}";
  dvector v(array);

  dvector results = sinh(v);

  ASSERT_DOUBLE_EQ(std::sinh(v[1]), results(1));
  ASSERT_DOUBLE_EQ(std::sinh(v[2]), results(2));
  ASSERT_DOUBLE_EQ(std::sinh(v[3]), results(3));
  ASSERT_DOUBLE_EQ(std::sinh(v[4]), results(4));
  ASSERT_DOUBLE_EQ(std::sinh(v[5]), results(5));
  ASSERT_DOUBLE_EQ(std::sinh(v[6]), results(6));
  ASSERT_DOUBLE_EQ(std::sinh(v[7]), results(7));
}
TEST_F(test_dvector, pows)
{
  char array[] = "{0.5, 1.5, 2, 3, 4, 5.1}";
  dvector v(array);

  dvector bases(1, 6);
  bases = 2.0;
  dvector results = pow(bases, v);

  ASSERT_DOUBLE_EQ(std::pow(bases(1), v[1]), results(1));
  ASSERT_DOUBLE_EQ(std::pow(bases(2), v[2]), results(2));
  ASSERT_DOUBLE_EQ(std::pow(bases(3), v[3]), results(3));
  ASSERT_DOUBLE_EQ(std::pow(bases(4), v[4]), results(4));
  ASSERT_DOUBLE_EQ(std::pow(bases(5), v[5]), results(5));
  ASSERT_DOUBLE_EQ(std::pow(bases(6), v[6]), results(6));
}
TEST_F(test_dvector, pows2)
{
  char array[] = "{0.5, 1.5, 2, 3, 4, 5.1}";
  dvector v(array);

  double base = 2.0;
  dvector results = pow(base, v);

  ASSERT_DOUBLE_EQ(std::pow(base, v[1]), results(1));
  ASSERT_DOUBLE_EQ(std::pow(base, v[2]), results(2));
  ASSERT_DOUBLE_EQ(std::pow(base, v[3]), results(3));
  ASSERT_DOUBLE_EQ(std::pow(base, v[4]), results(4));
  ASSERT_DOUBLE_EQ(std::pow(base, v[5]), results(5));
  ASSERT_DOUBLE_EQ(std::pow(base, v[6]), results(6));
}
TEST_F(test_dvector, powbasesexponent)
{
  char array[] = "{0.5, 1.5, 2, 3, 4, 5.1}";
  dvector bases(array);

  double exponent = 2.5;
  dvector results = pow(bases, exponent);

  ASSERT_DOUBLE_EQ(std::pow(bases(1), exponent), results(1));
  ASSERT_DOUBLE_EQ(std::pow(bases(2), exponent), results(2));
  ASSERT_DOUBLE_EQ(std::pow(bases(3), exponent), results(3));
  ASSERT_DOUBLE_EQ(std::pow(bases(4), exponent), results(4));
  ASSERT_DOUBLE_EQ(std::pow(bases(5), exponent), results(5));
  ASSERT_DOUBLE_EQ(std::pow(bases(6), exponent), results(6));
}
TEST_F(test_dvector, powbasesintegerexponent)
{
  char array[] = "{0.5, 1.5, 2, 3, 4, 5.1}";
  dvector bases(array);

  int exponent = 2;
  dvector results = pow(bases, exponent);

  ASSERT_DOUBLE_EQ(std::pow(bases(1), exponent), results(1));
  ASSERT_DOUBLE_EQ(std::pow(bases(2), exponent), results(2));
  ASSERT_DOUBLE_EQ(std::pow(bases(3), exponent), results(3));
  ASSERT_DOUBLE_EQ(std::pow(bases(4), exponent), results(4));
  ASSERT_DOUBLE_EQ(std::pow(bases(5), exponent), results(5));
  ASSERT_DOUBLE_EQ(std::pow(bases(6), exponent), results(6));
}
TEST_F(test_dvector, fill)
{
  dvector v(1, 6);
  v.initialize();

  char array[] = "{0, 1, 2, 3, 4, 5}";

  v.fill(array);

  ASSERT_DOUBLE_EQ(0, v(1));
  ASSERT_DOUBLE_EQ(1, v(2));
  ASSERT_DOUBLE_EQ(2, v(3));
  ASSERT_DOUBLE_EQ(3, v(4));
  ASSERT_DOUBLE_EQ(4, v(5));
  ASSERT_DOUBLE_EQ(5, v(6));
}
TEST_F(test_dvector, reallocate)
{
  dvector v(1, 4);
  v(1) = 0.5;
  v(2) = 1.5;
  v(3) = 2.5;
  v(4) = -4.5;
  EXPECT_DOUBLE_EQ(1, v.indexmin());
  EXPECT_DOUBLE_EQ(4, v.indexmax());
  EXPECT_DOUBLE_EQ(4, v.size());
  v.reallocate(2.5);
  EXPECT_DOUBLE_EQ(1, v.indexmin());
  EXPECT_DOUBLE_EQ(10, v.indexmax());
  EXPECT_DOUBLE_EQ(10, v.size());
  EXPECT_DOUBLE_EQ(0.5, v(1));
  EXPECT_DOUBLE_EQ(1.5, v(2));
  EXPECT_DOUBLE_EQ(2.5, v(3));
  EXPECT_DOUBLE_EQ(-4.5, v(4));
  EXPECT_DOUBLE_EQ(0, v(5));
  EXPECT_DOUBLE_EQ(0, v(6));
  EXPECT_DOUBLE_EQ(0, v(7));
  EXPECT_DOUBLE_EQ(0, v(8));
  EXPECT_DOUBLE_EQ(0, v(9));
  EXPECT_DOUBLE_EQ(0, v(10));
  v.reallocate(0.2);
  EXPECT_DOUBLE_EQ(1, v.indexmin());
  EXPECT_DOUBLE_EQ(2, v.indexmax());
  EXPECT_DOUBLE_EQ(2, v.size());
  EXPECT_DOUBLE_EQ(0.5, v(1));
  EXPECT_DOUBLE_EQ(1.5, v(2));
}
TEST_F(test_dvector, reallocate_empty)
{
  dvector empty;
  empty.reallocate(1.5);
  EXPECT_EQ(1, empty.indexmin());
  EXPECT_EQ(0, empty.indexmax());
  EXPECT_EQ(0, empty.size());
}
TEST_F(test_dvector, cast_lvector)
{
  dvector dv(1, 4);
  dv(1) = LONG_MIN;
  dv(2) = LONG_MIN/2;
  dv(3) = LONG_MAX/2;
  dv(4) = LONG_MAX;

  lvector lv(1, 2);
  lv(1) = 3;
  lv(2) = 1;

  dvector ret = dv(lv);
  EXPECT_EQ(lv.indexmin(), ret.indexmin());
  EXPECT_EQ(lv.indexmax(), ret.indexmax());
  EXPECT_DOUBLE_EQ(dv((int)lv(1)), ret(1));
  EXPECT_DOUBLE_EQ(dv((int)lv(2)), ret(2));
}
TEST_F(test_dvector, cast_ivector)
{
  dvector dv(1, 4);
  dv(1) = INT_MIN;
  dv(2) = INT_MIN/2;
  dv(3) = INT_MAX/2;
  dv(4) = INT_MAX;

  ivector iv(1, 2);
  iv(1) = 3;
  iv(2) = 1;

  dvector ret = dv(iv);
  EXPECT_EQ(iv.indexmin(), ret.indexmin());
  EXPECT_EQ(iv.indexmax(), ret.indexmax());
  EXPECT_DOUBLE_EQ(dv((int)iv(1)), ret(1));
  EXPECT_DOUBLE_EQ(dv((int)iv(2)), ret(2));
}
TEST_F(test_dvector, with_lvector)
{
  lvector lv(1, 4);
  lv(1) = LONG_MIN;
  lv(2) = INT_MIN;
  lv(3) = INT_MAX;
  lv(4) = LONG_MAX;

  dvector actual(lv);
  EXPECT_DOUBLE_EQ(double(LONG_MIN), actual(1));
  EXPECT_DOUBLE_EQ(double(INT_MIN), actual(2));
  EXPECT_DOUBLE_EQ(double(INT_MAX), actual(3));
  EXPECT_DOUBLE_EQ(double(LONG_MAX), actual(4));
}
TEST_F(test_dvector, safe_deallocate)
{
  ad_exit=&test_ad_exit;

  dvector dv(1, 4);
  unsigned int dv_ncopies = dv.get_ncopies();
  ASSERT_EQ(dv_ncopies, 0);

  bool has_exception = false;
  {
    dvector copy = dv;
    dv_ncopies = dv.get_ncopies();
    ASSERT_EQ(dv_ncopies, 1);
    unsigned int copy_ncopies = copy.get_ncopies();
    ASSERT_EQ(dv_ncopies, copy_ncopies);

    try
    {
      dv.safe_deallocate();
    }
    catch (const int exit_code)
    {
      const int expected_exit_code = 1;
      if (exit_code == expected_exit_code)
      {
        has_exception = true;
      }
    }
  }

  ASSERT_EQ(has_exception, true);

  dv_ncopies = dv.get_ncopies();
  ASSERT_EQ(dv_ncopies, 0);

  try
  {
    dv.safe_deallocate();
  }
  catch (const int exit_code)
  {
    FAIL();
  }
}
TEST_F(test_dvector, allocate)
{
  ad_exit=&test_ad_exit;

  dvector dv;
  ASSERT_EQ(dv.indexmin(), 1);
  ASSERT_EQ(dv.indexmax(), 0);

  dv.allocate(5, 2);
  ASSERT_EQ(dv.indexmin(), 1);
  ASSERT_EQ(dv.indexmax(), 0);

  dv.allocate(2, 5);
  ASSERT_EQ(dv.indexmin(), 2);
  ASSERT_EQ(dv.indexmax(), 5);

#ifndef OPT_LIB
  for (int i = 2; i <= 5; ++i)
  {
    ASSERT_DOUBLE_EQ(0, dv(i));
  }
#endif
}
TEST_F(test_dvector, save_dvector_derivatives_not_matching)
{
  dvar_vector_position pos;
  dvector dv(1, 4);
  ASSERT_DEATH(dv.save_dvector_derivatives(pos), "Assertion");
}
TEST_F(test_dvector, save_dvector_derivatives)
{
  gradient_structure gs;
  dvar_vector dvar(1, 4);
  dvar.initialize();
  dvar_vector_position pos(dvar);
  dvector dv(1, 4);
  dv(1) = 1.5;
  dv(2) = -2.5;
  dv(3) = 3.5;
  dv(4) = -4.5;
  dv.save_dvector_derivatives(pos);
  for (int i = 1; i <= 4; ++i)
  {
    ASSERT_DOUBLE_EQ(value(dvar(i)), dv(i));
  }
}
TEST_F(test_dvector, is_valid_index)
{
  dvector dv(1, 4);
  ASSERT_EQ(false, dv.is_valid_index(0));
  ASSERT_EQ(true, dv.is_valid_index(1));
  ASSERT_EQ(true, dv.is_valid_index(2));
  ASSERT_EQ(true, dv.is_valid_index(3));
  ASSERT_EQ(true, dv.is_valid_index(4));
  ASSERT_EQ(false, dv.is_valid_index(5));
  ASSERT_EQ(false, false || dv.is_valid_index(0));
  ASSERT_EQ(true, false || dv.is_valid_index(1));
  ASSERT_EQ(true, false || dv.is_valid_index(4));
  ASSERT_EQ(false, false || dv.is_valid_index(5));
  ASSERT_DEATH(dv(0), "Assertion");
  ASSERT_DEATH(dv(5), "Assertion");
}
TEST_F(test_dvector, dll_data_int)
{
  int min = 1;
  int max = 4;
  dvector dv;

  dll_data_int begin;
  begin.allocate(&min, "begin");
  dll_data_int end;
  end.allocate(&max, "end");

  dv.allocate(begin, end);

  ASSERT_EQ(dv.indexmin(), min);
  ASSERT_EQ(dv.indexmax(), max);
}
TEST_F(test_dvector, fill_lbraces_zero)
{
  dvector v(1, 6);
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
TEST_F(test_dvector, fill_lbraces_greater_than_one)
{
  dvector v(1, 6);
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
TEST_F(test_dvector, fill_lbraces_not_equal_rbraces)
{
  dvector v(1, 6);
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
TEST_F(test_dvector, fill_lbraces1_not_equal_rbraces)
{
  dvector v(1, 6);
  v.initialize();

  char array[] = "{0, 1, 2, 3, 4, 5}}}";

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
TEST_F(test_dvector, filename_goodcolumn)
{
  ofstream ofs("test_dvector.txt");
  ofs << "1 2 3\n";
  ofs << "4 5 6\n";
  ofs << "7 8 9\n";
  ofs.close();

  dvector v("test_dvector.txt", 2);
  ASSERT_EQ(1, v.indexmin());
  ASSERT_EQ(3, v.indexmax());
  ASSERT_EQ(3, v.size());
  ASSERT_DOUBLE_EQ(2, v(1));
  ASSERT_DOUBLE_EQ(5, v(2));
  ASSERT_DOUBLE_EQ(8, v(3));
}
TEST_F(test_dvector, filename_badcolumn)
{
  ofstream ofs("test_dvector.txt");
  ofs << "1 2 3\n";
  ofs << "4 5 6\n";
  ofs << "7 8 9\n";
  ofs.close();
  try
  {
    dvector v("test_dvector.txt", 4);
  }
  catch (const int exit_code)
  {
    return;
  }
  FAIL();
}
TEST_F(test_dvector, filename_negativebadcolumn)
{
  ofstream ofs("test_dvector.txt");
  ofs << "1 2 3\n";
  ofs << "4 5 6\n";
  ofs << "7 8 9\n";
  ofs.close();
  try
  {
    dvector v("test_dvector.txt", -1);
  }
  catch (const int exit_code)
  {
    return;
  }
  FAIL();
}
TEST_F(test_dvector, filename_zerobadcolumn)
{
  ofstream ofs("test_dvector.txt");
  ofs << "1 2 3\n";
  ofs << "4 5 6\n";
  ofs << "7 8 9\n";
  ofs.close();
  try
  {
    dvector v("test_dvector.txt", 0);
  }
  catch (const int exit_code)
  {
    return;
  }
  FAIL();
}
TEST_F(test_dvector, filename_raggedcolumn)
{
  ofstream ofs("test_dvector.txt");
  ofs << "1 2 3\n";
  ofs << "4\n";
  ofs << "7 8 9\n";
  ofs.close();
  try
  {
    dvector v("test_dvector.txt", 2);
  }
  catch (const int exit_code)
  {
    return;
  }
  FAIL();
}
TEST_F(test_dvector, sgn)
{
  dvector d(1, 5);
  d(1) = -1;
  d(2) = 0.1;
  d(3) = 3;
  d(4) = -0.1;
  d(5) = 5;

  ivector v = sgn(d);
  ASSERT_EQ(-1, v(1));
  ASSERT_EQ(1, v(2));
  ASSERT_EQ(1, v(3));
  ASSERT_EQ(-1, v(4));
  ASSERT_EQ(1, v(5));
}
TEST_F(test_dvector, append)
{
  dvector a(1, 5);
  a(1) = 1;
  a(2) = 2;
  a(3) = 3;
  a(4) = 4;
  a(5) = 5;
  dvector b(1, 5);
  b(1) = 6;
  b(2) = 7;
  b(3) = 8;
  b(4) = 9;
  b(5) = 10;
  dvector ab = a & b;
  ASSERT_EQ(10, ab.size());
  ASSERT_EQ(1, ab(1));
  ASSERT_EQ(2, ab(2));
  ASSERT_EQ(3, ab(3));
  ASSERT_EQ(4, ab(4));
  ASSERT_EQ(5, ab(5));
  ASSERT_EQ(6, ab(6));
  ASSERT_EQ(7, ab(7));
  ASSERT_EQ(8, ab(8));
  ASSERT_EQ(9, ab(9));
  ASSERT_EQ(10, ab(10));
}
TEST_F(test_dvector, sort)
{
  dvector d(1, 5);
  d(1) = -1;
  d(2) = 0.1;
  d(3) = 3;
  d(4) = -0.25;
  d(5) = 0;

  dvector v = sort(d, 0);
  ASSERT_DOUBLE_EQ(-1, v(1));
  ASSERT_DOUBLE_EQ(-0.25, v(2));
  ASSERT_DOUBLE_EQ(0, v(3));
  ASSERT_DOUBLE_EQ(0.1, v(4));
  ASSERT_DOUBLE_EQ(3, v(5));
}
TEST_F(test_dvector, sort_with_index)
{
  dvector dvec(1, 5);
  dvec(1) = -1;
  dvec(2) = 0.1;
  dvec(3) = 3;
  dvec(4) = -0.25;
  dvec(5) = 0;
  ivector ivec(1, 5);
  ivec.initialize();

  dvector v = sort(dvec, ivec);

  ASSERT_DOUBLE_EQ(-1, dvec(1));
  ASSERT_DOUBLE_EQ(0.1, dvec(2));
  ASSERT_DOUBLE_EQ(3, dvec(3));
  ASSERT_DOUBLE_EQ(-0.25, dvec(4));
  ASSERT_DOUBLE_EQ(0, dvec(5));

  ASSERT_DOUBLE_EQ(-1, v(1));
  ASSERT_DOUBLE_EQ(-0.25, v(2));
  ASSERT_DOUBLE_EQ(0, v(3));
  ASSERT_DOUBLE_EQ(0.1, v(4));
  ASSERT_DOUBLE_EQ(3, v(5));

  ASSERT_EQ(1, ivec(1));
  ASSERT_EQ(4, ivec(2));
  ASSERT_EQ(5, ivec(3));
  ASSERT_EQ(2, ivec(4));
  ASSERT_EQ(3, ivec(5));
}
namespace admb_deprecated
{
  dvector sort(const dvector& v, int NSTACK);
  dvector sort(const dvector& v, const ivector& index, int NSTACK);
}
TEST_F(test_dvector, deprecated_sort)
{
  dvector d(1, 5);
  d(1) = -1;
  d(2) = 0.1;
  d(3) = 3;
  d(4) = -0.25;
  d(5) = 0;

  dvector v = admb_deprecated::sort(d, 60);
  ASSERT_DOUBLE_EQ(-1, v(1));
  ASSERT_DOUBLE_EQ(-0.25, v(2));
  ASSERT_DOUBLE_EQ(0, v(3));
  ASSERT_DOUBLE_EQ(0.1, v(4));
  ASSERT_DOUBLE_EQ(3, v(5));
}
TEST_F(test_dvector, deprecated_sort_with_index)
{
  dvector dvec(1, 5);
  dvec(1) = -1;
  dvec(2) = 0.1;
  dvec(3) = 3;
  dvec(4) = -0.25;
  dvec(5) = 0;

  ivector ivec(1, 5);
  ivec.initialize();

  dvector v = admb_deprecated::sort(dvec, ivec, 60);

  ASSERT_DOUBLE_EQ(-1, dvec(1));
  ASSERT_DOUBLE_EQ(0.1, dvec(2));
  ASSERT_DOUBLE_EQ(3, dvec(3));
  ASSERT_DOUBLE_EQ(-0.25, dvec(4));
  ASSERT_DOUBLE_EQ(0, dvec(5));

  ASSERT_DOUBLE_EQ(-1, v(1));
  ASSERT_DOUBLE_EQ(-0.25, v(2));
  ASSERT_DOUBLE_EQ(0, v(3));
  ASSERT_DOUBLE_EQ(0.1, v(4));
  ASSERT_DOUBLE_EQ(3, v(5));

  ASSERT_EQ(1, ivec(1));
  ASSERT_EQ(4, ivec(2));
  ASSERT_EQ(5, ivec(3));
  ASSERT_EQ(2, ivec(4));
  ASSERT_EQ(3, ivec(5));
}
TEST_F(test_dvector, nobraces)
{
  ofstream ofs("test_dvector.txt");
  ofs << "0 1 2 3 4 5\n";
  ofs.close();

  dvector v("test_dvector.txt");

  ASSERT_DOUBLE_EQ(0, v(1));
  ASSERT_DOUBLE_EQ(1, v(2));
  ASSERT_DOUBLE_EQ(2, v(3));
  ASSERT_DOUBLE_EQ(3, v(4));
  ASSERT_DOUBLE_EQ(4, v(5));
  ASSERT_DOUBLE_EQ(5, v(6));
}
TEST_F(test_dvector, allocatenobraces)
{
  ofstream ofs("test_dvector.txt");
  ofs << "0 1 2 3 4 5\n";
  ofs.close();

  dvector v(1, 6);
  v.allocate("test_dvector.txt");

  ASSERT_DOUBLE_EQ(0, v(1));
  ASSERT_DOUBLE_EQ(1, v(2));
  ASSERT_DOUBLE_EQ(2, v(3));
  ASSERT_DOUBLE_EQ(3, v(4));
  ASSERT_DOUBLE_EQ(4, v(5));
  ASSERT_DOUBLE_EQ(5, v(6));
}
TEST_F(test_dvector, filedoesnotexist)
{
  ad_exit=&test_ad_exit;

  ASSERT_ANY_THROW({
    dvector v("filedoesnotexist");
  });
  ASSERT_ANY_THROW({
    dvector v;
    v.allocate("filedoesnotexist");
  });
}
TEST_F(test_dvector, unmatchedbraces)
{
  ad_exit=&test_ad_exit;

  char array[] = "{0, 1, 2, 3, 4, 5";

  ASSERT_ANY_THROW({
    dvector v(array);
  });
}
TEST_F(test_dvector, allocateunmatchedbraces)
{
  ad_exit=&test_ad_exit;

  char array[] = "{0, 1, 2, 3, 4, 5";

  ASSERT_ANY_THROW({
    dvector v;
    v.allocate(array);
  });
}
TEST_F(test_dvector, t0omanybraces)
{
  ad_exit=&test_ad_exit;

  char array[] = "{{0, 1, 2, 3, 4, 5}}";

  ASSERT_ANY_THROW({
    dvector v(array);
  });
}
TEST_F(test_dvector, allocatet0omanybraces)
{
  ad_exit=&test_ad_exit;

  char array[] = "{{0, 1, 2, 3, 4, 5}}";

  ASSERT_ANY_THROW({
    dvector v;
    v.allocate(array);
  });
}
TEST_F(test_dvector, dvector_position)
{
  dvector_position pos;
  ASSERT_EQ(0, pos.indexmin());
  ASSERT_EQ(-1, pos.indexmax());
}
TEST_F(test_dvector, mean)
{
  char array[] = "{0, 1, 2, 3, 4, 5}";

  dvector v(array);
  ASSERT_DOUBLE_EQ(2.5, mean(v));
}

TEST_F(test_dvector, dvector_position_vec)
{
  dvector vec(1, 3);
  dvector_position pos(vec);
  ASSERT_EQ(1, pos.indexmin());
  ASSERT_EQ(3, pos.indexmax());
}
TEST_F(test_dvector, substracterror)
{
  ad_exit=&test_ad_exit;

  dvector a(1, 3);

  ASSERT_ANY_THROW({
    dvector b(2, 3);
    a - b;
  });
  ASSERT_ANY_THROW({
    dvector b(1, 4);
    a - b;
  });
}
TEST_F(test_dvector, adderror)
{
  ad_exit=&test_ad_exit;

  dvector a(1, 3);

  ASSERT_ANY_THROW({
    dvector b(2, 3);
    a + b;
  });
  ASSERT_ANY_THROW({
    dvector b(1, 4);
    a + b;
  });
}
TEST_F(test_dvector, timeserror)
{
  ad_exit=&test_ad_exit;

  dvector a(1, 3);

  ASSERT_ANY_THROW({
    dvector b(2, 3);
    a * b;
  });
  ASSERT_ANY_THROW({
    dvector b(1, 4);
    a * b;
  });
}
TEST_F(test_dvector, equalserror)
{
  ad_exit=&test_ad_exit;

  dvector a(1, 3);

  ASSERT_ANY_THROW({
    dvector b(2, 3);
    a = b;
  });
  ASSERT_ANY_THROW({
    dvector b(1, 4);
    a = b;
  });
}
TEST_F(test_dvector, elemproderror)
{
  ad_exit=&test_ad_exit;

  dvector a(1, 3);

  ASSERT_ANY_THROW({
    dvector b(2, 3);
    elem_prod(a, b);
  });
  ASSERT_ANY_THROW({
    dvector b(1, 4);
    elem_prod(a, b);
  });
}
TEST_F(test_dvector, elemdiverror)
{
  ad_exit=&test_ad_exit;

  dvector a(1, 3);

  ASSERT_ANY_THROW({
    dvector b(2, 3);
    elem_div(a, b);
  });
  ASSERT_ANY_THROW({
    dvector b(1, 4);
    elem_div(a, b);
  });
}
TEST_F(test_dvector, plusequalerror)
{
  ad_exit=&test_ad_exit;

  dvector a(1, 3);

  ASSERT_ANY_THROW({
    dvector b(2, 3);
    a += b;
  });
  ASSERT_ANY_THROW({
    dvector b(1, 4);
    a += b;
  });
}
TEST_F(test_dvector, minusequalerror)
{
  ad_exit=&test_ad_exit;

  dvector a(1, 3);

  ASSERT_ANY_THROW({
    dvector b(2, 3);
    a -= b;
  });
  ASSERT_ANY_THROW({
    dvector b(1, 4);
    a -= b;
  });
}
TEST_F(test_dvector, plusequalvalue)
{
  ad_exit=&test_ad_exit;

  dvector a(1, 3);
  a.initialize();
  a(1) = 1;
  a(2) = 2;
  a(3) = 3;

  double value = -2.5;

  a += value;

  ASSERT_DOUBLE_EQ(-1.5, a(1));
  ASSERT_DOUBLE_EQ(-0.5, a(2));
  ASSERT_DOUBLE_EQ(0.5, a(3));
}
TEST_F(test_dvector, minusequalvalue)
{
  ad_exit=&test_ad_exit;

  dvector a(1, 3);
  a.initialize();
  a(1) = 1;
  a(2) = 2;
  a(3) = 3;

  double value = -2.5;

  a -= value;

  ASSERT_DOUBLE_EQ(3.5, a(1));
  ASSERT_DOUBLE_EQ(4.5, a(2));
  ASSERT_DOUBLE_EQ(5.5, a(3));
}
TEST_F(test_dvector, shape_check)
{
  ad_exit=&test_ad_exit;

  dvector a(1, 3);

  void shape_check(
    const dvector& v1,
    const dvector& v2,
    const char* function_name);

  ASSERT_ANY_THROW({
    dvector b(2, 3);
    shape_check(a, b, "shapecheck");
  });
  ASSERT_ANY_THROW({
    dvector b(1, 4);
    shape_check(a, b, "shapecheck");
  });
}
TEST_F(test_dvector, first_difference_error)
{
  ad_exit=&test_ad_exit;

  dvector a(1, 1);

  ASSERT_ANY_THROW({
    first_difference(a);
  });
}
TEST_F(test_dvector, first_difference)
{
  ad_exit=&test_ad_exit;

  dvector a(1, 3);
  a(1) = -1;
  a(2) = 2;
  a(3) = 4;

  dvector ret = first_difference(a);

  ASSERT_EQ(1, ret.indexmin());
  ASSERT_EQ(2, ret.indexmax());
  ASSERT_DOUBLE_EQ(3, ret(1));
  ASSERT_DOUBLE_EQ(2, ret(2));
}
TEST_F(test_dvector, sum)
{
  ad_exit=&test_ad_exit;

  dvector a(1, 3);
  a(1) = -1;
  a(2) = 2;
  a(3) = 4;

  double ret = sum(a);

  ASSERT_DOUBLE_EQ(5, ret);
}
TEST_F(test_dvector, VEC)
{
  ad_exit=&test_ad_exit;

  dmatrix matrix(1, 2, 1, 2);
  matrix(1, 1) = 4;
  matrix(1, 2) = -3;
  matrix(2, 1) = 2;
  matrix(2, 2) = -9;
  dvector ret = VEC(matrix);

  ASSERT_EQ(1, ret.indexmin());
  ASSERT_EQ(4, ret.indexmax());
  ASSERT_DOUBLE_EQ(matrix(1, 1), ret(1));
  ASSERT_DOUBLE_EQ(matrix(1, 2), ret(2));
  ASSERT_DOUBLE_EQ(matrix(2, 1), ret(3));
  ASSERT_DOUBLE_EQ(matrix(2, 2), ret(4));

  dmatrix ret2 = MAT(ret, 2, 2);
  ASSERT_EQ(1, ret2.rowmin());
  ASSERT_EQ(2, ret2.rowmax());
  ASSERT_EQ(1, ret2.colmin());
  ASSERT_EQ(2, ret2.colmax());
  ASSERT_DOUBLE_EQ(matrix(1, 1), ret2(1, 1));
  ASSERT_DOUBLE_EQ(matrix(1, 2), ret2(1, 2));
  ASSERT_DOUBLE_EQ(matrix(2, 1), ret2(2, 1));
  ASSERT_DOUBLE_EQ(matrix(2, 2), ret2(2, 2));
}
