#include <gtest/gtest.h>
#include <admodel.h>
#include <df1b2fun.h>

void test_ad_exit(const int exit_code);

class test_data_number: public ::testing::Test { };

TEST_F(test_data_number, constructor)
{
  data_number M;
  M = 4;
  double d = M;

  ASSERT_DOUBLE_EQ(d, 4);

  M.initialize();
  ASSERT_DOUBLE_EQ(M.value(), 0);

  M = 2.5;

  ASSERT_DOUBLE_EQ(M.value(), 2.5);
}
