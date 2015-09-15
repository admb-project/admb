#include <gtest/gtest.h>
#include <df1b2fun.h>

class test_df1b2vector: public ::testing::Test {};

TEST_F(test_df1b2vector, operator_div)
{
  df1b2vector vector(1, 4);
  vector.initialize();
  dvariable variable;
  variable = 5;
  const df1b2vector& result = vector / varible;
  ASSERT_DOUBLE_EQ(1.0/5.0, value(result(1)));
  ASSERT_DOUBLE_EQ(2.0/5.0, value(result(2)));
  ASSERT_DOUBLE_EQ(3.0/5.0, value(result(3)));
  ASSERT_DOUBLE_EQ(4.0/5.0, value(result(4)));
}
