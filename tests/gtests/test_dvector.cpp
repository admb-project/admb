#include <gtest/gtest.h>
#include <fvar.hpp>
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
