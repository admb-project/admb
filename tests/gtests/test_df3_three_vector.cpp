#include <gtest/gtest.h>
#include <df1b2fun.h>
#include <df33fun.h>

class test_df3_three_vector: public ::testing::Test {};

TEST_F(test_df3_three_vector, default_constructor)
{
  df3_three_vector vec;
  ASSERT_EQ(-1, vec.indexmax());
  ASSERT_EQ(0, vec.indexmin());

  vec.allocate(1, 4);
  ASSERT_EQ(4, vec.indexmax());
  ASSERT_EQ(1, vec.indexmin());

  vec.initialize();
  ASSERT_DOUBLE_EQ(0, value(vec[1]));
  ASSERT_DOUBLE_EQ(0, value(vec[2]));
  ASSERT_DOUBLE_EQ(0, value(vec[3]));
  ASSERT_DOUBLE_EQ(0, value(vec[4]));

  vec.deallocate();
  ASSERT_EQ(-1, vec.indexmax());
  ASSERT_EQ(0, vec.indexmin());
}
