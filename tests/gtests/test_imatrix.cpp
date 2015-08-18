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
