#include <gtest/gtest.h>
#include <fvar.hpp>
#include <climits>

extern "C"
{
  void test_ad_exit(const int exit_code);
}

class test_imatrix: public ::testing::Test {};

TEST_F(test_imatrix, rowmax_plus_1)
{
  ad_exit=&test_ad_exit;

  imatrix m(1, 4, 1, 3);
  m.initialize();
  ASSERT_THROW(m[5],int);
}
TEST_F(test_imatrix, rowmax)
{
  imatrix m(1, 4, 1, 3);
  int expected = m.rowsize() + m.rowmin() - 1;
  ASSERT_EQ(expected,m.rowmax());
}
TEST_F(test_imatrix, is_valid_row)
{
  imatrix m(1, 4, 1, 3);
  ASSERT_EQ(false, m.is_valid_row(-1));
  ASSERT_EQ(false, m.is_valid_row(0));
  ASSERT_EQ(true, m.is_valid_row(1));
  ASSERT_EQ(true, m.is_valid_row(2));
  ASSERT_EQ(true, m.is_valid_row(3));
  ASSERT_EQ(true, m.is_valid_row(4));
  ASSERT_EQ(false, m.is_valid_row(5));
  ASSERT_DEATH(m(0), "Assertion");
  ASSERT_DEATH(m(5), "Assertion");
}
TEST_F(test_imatrix, assignment)
{
  imatrix m(1, 4, 1, 3);
  m.initialize();
  for (int i = 1; i <= 4; ++i)
  {
    for (int j = 1; j <= 3; ++j)
    {
      ASSERT_EQ(0, m(i, j));
    }
  }
  m = 5;
  for (int i = 1; i <= 4; ++i)
  {
    for (int j = 1; j <= 3; ++j)
    {
      ASSERT_EQ(5, m(i, j));
    }
  }
}
TEST_F(test_imatrix, assignment_imatrix)
{
  ad_exit=&test_ad_exit;
  imatrix m(1, 4, 1, 3);
  imatrix m2(1, 2, 1, 2);
  ASSERT_THROW(m = m2, int);
}
TEST_F(test_imatrix, diagonal)
{
  imatrix m(1, 3, 1, 3);
  m.initialize();
  m(1, 1) = 10;
  m(2, 2) = 20;
  m(3, 3) = 30;
  ivector ret = diagonal(m);
  ASSERT_EQ(10, m(1, 1));
  ASSERT_EQ(20, m(2, 2));
  ASSERT_EQ(30, m(3, 3));
}
TEST_F(test_imatrix, min)
{
  int min(const imatrix& M);
  imatrix m(1, 3, 1, 3);
  m.initialize();
  m(2, 2) = -20;
  ASSERT_EQ(-20, min(m));
}
TEST_F(test_imatrix, max)
{
  int max(const imatrix& M);
  imatrix m(1, 3, 1, 3);
  m.initialize();
  m(2, 2) = 20;
  ASSERT_EQ(20, max(m));
}
