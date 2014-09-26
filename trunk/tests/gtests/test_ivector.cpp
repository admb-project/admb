#include <gtest/gtest.h>
#include <fvar.hpp>
#include <climits>

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
