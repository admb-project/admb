#include <gtest/gtest.h>
#include <admodel.h>

extern "C"
{
  void test_ad_exit(const int exit_code);
}

class test_data_int: public ::testing::Test { };

TEST_F(test_data_int, set_to_zero)
{
  data_int data;
  int i = int(data);
  i *= -1;

  int result = i + data;
  
  ASSERT_EQ(result, 0);
}
TEST_F(test_data_int, assignment)
{
  data_int data;

  data = 5;
  ASSERT_EQ((int)data, 5);

  data_int other;

  other = data;
  ASSERT_EQ((int)other, 5);
}
