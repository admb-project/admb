#include <gtest/gtest.h>
#include "df1b2fun.h"

class test_df1b2_init_bounded_number_vector: public ::testing::Test {};

TEST_F(test_df1b2_init_bounded_number_vector, constructor)
{
  df1b2_init_bounded_number_vector v;
  ASSERT_FALSE(v.allocated());
  ASSERT_EQ(1, v.indexmin());
  ASSERT_EQ(0, v.indexmax());
}
