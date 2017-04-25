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
/*
TEST_F(test_dvector, data_int)
{
  dvector dv;

  data_int begin;
  data_int end;

  dv.allocate(begin, end);

  //ASSERT_EQ(dv.indexmin(), 1);
  //ASSERT_EQ(dv.indexmax(), 4);
}
*/
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
