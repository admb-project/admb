#include <gtest/gtest.h>
#include <fvar.hpp>
#include <climits>

extern "C"
{
  void test_ad_exit(const int exit_code);
}

class test_ivector: public ::testing::Test {};

TEST_F(test_ivector, constructor)
{
  ivector v;
  EXPECT_EQ(0, v.size());
}
TEST_F(test_ivector, initialize)
{
  ivector v(1, 10);
  EXPECT_EQ(10, v.size());
  for (int i = 1; i <= 10; i++)
  {
    v(i) = i;
  }
  for (int i = 1; i <= 10; i++)
  {
    EXPECT_EQ(i, v(i));
  }
  v.initialize();
  for (int i = 1; i <= 10; i++)
  {
    EXPECT_EQ(0, v(i));
  }
}
TEST_F(test_ivector, initialize_with_long_array)
{
  long int expected[4];
  expected[0] = 0;
  expected[1] = 1;
  expected[2] = 2;
  expected[3] = INT_MAX;
  ivector v(4, expected);
  EXPECT_EQ(expected[0], v(0));
  EXPECT_EQ(expected[1], v(1));
  EXPECT_EQ(expected[2], v(2));
  EXPECT_EQ(expected[3], v(3));
}
#ifdef OPT_LIB
TEST_F(test_ivector, initialize_with_INT_MAX_plus_one)
{
  long int expected[1];
  expected[0] = (long int)(INT_MAX) + 1;
  ivector v(1, expected);
  EXPECT_NE(expected[0], v(0));
  //EXPECT_EXIT(ivector v(1, expected), ::testing::ExitedWithCode(1), "Overflowed");
}
#endif
TEST_F(test_ivector, initialize_with_dvector)
{
  dvector expected(1, 4);
  expected(1) = 0;
  expected(2) = 1;
  expected(3) = 2;
  expected(4) = INT_MAX;
  ivector actual(expected);
  EXPECT_DOUBLE_EQ(expected(1), actual(1));
  EXPECT_DOUBLE_EQ(expected(2), actual(2));
  EXPECT_DOUBLE_EQ(expected(3), actual(3));
  EXPECT_DOUBLE_EQ(expected(4), actual(4));
}
#ifdef OPT_LIB
TEST_F(test_ivector, initialize_with_dvector_INT_MAX_plus_one)
{
  dvector expected(1, 1);
  expected(1) = (long int)(INT_MAX) + 1;
  ivector actual(expected);
  EXPECT_NE(expected(1), (int)actual(1));
  //EXPECT_EXIT(ivector v(1, expected), ::testing::ExitedWithCode(1), "Overflowed");
}
#endif
TEST_F(test_ivector, square)
{
  ivector v(1, 4);
  v(1) = 0;
  v(2) = 1;
  v(3) = 2;
  v(4) = -4;
  ivector actual = square(v);
  EXPECT_EQ(0, actual(1));
  EXPECT_EQ(1, actual(2));
  EXPECT_EQ(4, actual(3));
  EXPECT_EQ(16, actual(4));
}
TEST_F(test_ivector, reallocate)
{
  ivector v(1, 4);
  v(1) = 0;
  v(2) = 1;
  v(3) = 2;
  v(4) = -4;
  EXPECT_EQ(1, v.indexmin());
  EXPECT_EQ(4, v.indexmax());
  EXPECT_EQ(4, v.size());
  v.reallocate(2.5);
  EXPECT_EQ(1, v.indexmin());
  EXPECT_EQ(10, v.indexmax());
  EXPECT_EQ(10, v.size());
  EXPECT_EQ(0, v(1));
  EXPECT_EQ(1, v(2));
  EXPECT_EQ(2, v(3));
  EXPECT_EQ(-4, v(4));
  EXPECT_EQ(0, v(5));
  EXPECT_EQ(0, v(6));
  EXPECT_EQ(0, v(7));
  EXPECT_EQ(0, v(8));
  EXPECT_EQ(0, v(9));
  EXPECT_EQ(0, v(10));
  v.reallocate(0.2);
  EXPECT_EQ(1, v.indexmin());
  EXPECT_EQ(2, v.indexmax());
  EXPECT_EQ(2, v.size());
  EXPECT_EQ(0, v(1));
  EXPECT_EQ(1, v(2));
}
TEST_F(test_ivector, reallocate_empty)
{
  ivector empty;
  empty.reallocate(1.5);
  EXPECT_EQ(1, empty.indexmin());
  EXPECT_EQ(-1, empty.indexmax());
  EXPECT_EQ(0, empty.size());
}
TEST_F(test_ivector, check_order)
{
  ivector v(1, 4);
  v(1) = 0;
  v(2) = 1;
  v(3) = 2;
  v(4) = -4;

  bool check_order(const ivector& v);
  ASSERT_FALSE(check_order(v));

  v = sort(v);

  ASSERT_TRUE(check_order(v));
}
TEST_F(test_ivector, common_same)
{
  ivector v(1, 4);
  v(1) = 0;
  v(2) = 1;
  v(3) = 2;
  v(4) = -4;

  int common(ivector& v,ivector& w);
  EXPECT_TRUE(common(v, v) == 1);

  bool check_order(const ivector& v);
  ASSERT_TRUE(check_order(v));
}
TEST_F(test_ivector, common_none)
{
  ivector v(1, 4);
  v(1) = 3;
  v(2) = 1;
  v(3) = 2;
  v(4) = -4;

  ivector w(1, 4);
  w(1) = -3;
  w(2) = -1;
  w(3) = -2;
  w(4) = 4;

  int common(ivector& v,ivector& w);
  EXPECT_FALSE(common(v, w) == 1);

  bool check_order(const ivector& v);
  ASSERT_TRUE(check_order(v));
  ASSERT_TRUE(check_order(w));
}
TEST_F(test_ivector, common_one)
{
  ivector v(1, 4);
  v(1) = 3;
  v(2) = 1;
  v(3) = 2;
  v(4) = -4;

  ivector w(1, 4);
  w(1) = -3;
  w(2) = 1;
  w(3) = -2;
  w(4) = 4;

  int common(ivector& v,ivector& w);
  EXPECT_TRUE(common(v, w) == 1);

  bool check_order(const ivector& v);
  ASSERT_TRUE(check_order(v));
  ASSERT_TRUE(check_order(w));
}
TEST_F(test_ivector, safe_deallocate)
{
  ad_exit=&test_ad_exit;

  ivector iv(1, 4);
  unsigned int iv_ncopies = iv.get_ncopies();
  ASSERT_EQ(iv_ncopies, 0);

  bool has_exception = false;
  {
    ivector copy = iv;
    iv_ncopies = iv.get_ncopies();
    ASSERT_EQ(iv_ncopies, 1);
    unsigned int copy_ncopies = copy.get_ncopies();
    ASSERT_EQ(iv_ncopies, copy_ncopies);

    try
    {
      iv.safe_deallocate();
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

  iv_ncopies = iv.get_ncopies();
  ASSERT_EQ(iv_ncopies, 0);

  try
  {
    iv.safe_deallocate();
  }
  catch (const int exit_code)
  {
    FAIL();
  }
}
TEST_F(test_ivector, copy_constructor_empty)
{
  ivector orig;
  ASSERT_FALSE(orig.allocated());
  ASSERT_TRUE(orig.get_v() == NULL);
  ASSERT_EQ(0, orig.get_ncopies());

  ivector copy(orig);
  ASSERT_FALSE(orig.allocated());
  ASSERT_FALSE(copy.allocated());
  ASSERT_TRUE(copy.get_v() == NULL);
  ASSERT_EQ(0, copy.get_ncopies());
  ASSERT_EQ(0, orig.get_ncopies());
  ASSERT_EQ(copy.indexmin(), orig.indexmin());
  ASSERT_EQ(copy.indexmax(), orig.indexmax());
}
TEST_F(test_ivector, fill)
{
  ivector v(1, 3);
  v.fill("{3, 2, 1}");
  ASSERT_EQ(3, v(1));
  ASSERT_EQ(2, v(2));
  ASSERT_EQ(1, v(3));
}
