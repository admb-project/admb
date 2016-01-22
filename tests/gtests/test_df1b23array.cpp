#include <gtest/gtest.h>
#include "df1b2fun.h"

class test_df1b23array: public ::testing::Test {};

TEST_F(test_df1b23array, default_constructor)
{
  //df1b23array a(int nrl,int nrh,int ncl,int nch);
  df1b23array a;

  ASSERT_FALSE(a.allocated());
  ASSERT_EQ(1, a.indexmin());
  ASSERT_EQ(0, a.indexmax());
  ASSERT_EQ(0, a.size());
}
TEST_F(test_df1b23array, allocate4_deallocate)
{
  df1b23array a;
  int nrl = 1;
  int nrh = 4;
  int ncl = 2;
  int nch = 3;
  a.allocate(nrl, nrh, ncl, nch);
  ASSERT_TRUE(a.allocated());
  ASSERT_EQ(1, a.indexmin());
  ASSERT_EQ(4, a.indexmax());
  ASSERT_EQ(4, a.size());
  a.deallocate();
  ASSERT_FALSE(a.allocated());
  ASSERT_EQ(1, a.indexmin());
  ASSERT_EQ(0, a.indexmax());
  ASSERT_EQ(0, a.size());
}

