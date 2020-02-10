#include <gtest/gtest.h>
#include <fvar.hpp>
#include <climits>

class test_lmatrix: public ::testing::Test {};

TEST_F(test_lmatrix, rowmax_plus_1)
{
  lmatrix m(1, 4, 1, 3);
  m.initialize();
  ASSERT_THROW(m[5],int);
}
TEST_F(test_lmatrix, rowmax)
{
  lmatrix m(1, 4, 1, 3);
  ASSERT_EQ(m.rowsize() + m.rowmin() - 1,m.rowmax());
}
