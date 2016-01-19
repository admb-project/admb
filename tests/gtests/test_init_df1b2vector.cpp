#include <gtest/gtest.h>
#include "df1b2fun.h"

class test_init_df1b2vector: public ::testing::Test {};

TEST_F(test_init_df1b2vector, constructor)
{
  init_df1b2vector v;
  ASSERT_EQ(0, v.indexmin());
  ASSERT_EQ(-1, v.indexmax());
}
TEST_F(test_init_df1b2vector, copy_is_empty)
{
  init_df1b2vector copy;
  init_df1b2vector v(copy);
  ASSERT_EQ(0, v.indexmin());
  ASSERT_EQ(-1, v.indexmax());
}
