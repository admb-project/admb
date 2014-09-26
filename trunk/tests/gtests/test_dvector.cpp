#include <gtest/gtest.h>
#include <fvar.hpp>

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
