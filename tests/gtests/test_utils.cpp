#include <gtest/gtest.h>
#include <fvar.hpp>

extern "C"
{
  void test_ad_exit(const int exit_code);
}

class test_utils: public ::testing::Test {};

TEST_F(test_utils, ranfill)
{
  double auto_rand(long int& idum, int reset);

  long idum = 5;

  double value = auto_rand(idum, -1);
  ASSERT_DOUBLE_EQ(value, 0.5);

  double value2 = auto_rand(idum, 1);
  ASSERT_DOUBLE_EQ(value2, 0.6659108996391296);

  void reinitialize_auto_rand();
  reinitialize_auto_rand();
}
TEST_F(test_utils, check_datafile_pointer)
{
  ad_exit=&test_ad_exit;

  void check_datafile_pointer(void* p);

  ASSERT_THROW(check_datafile_pointer(NULL),int);
}
TEST_F(test_utils, variance)
{
  dvector data(1, 5);
  data(1) = 600;
  data(2) = 470;
  data(3) = 170;
  data(4) = 430;
  data(5) = 300;

  ASSERT_DOUBLE_EQ(21704, var(data));
}
TEST_F(test_utils, std_dev)
{
  dvector data(1, 5);
  data(1) = 600;
  data(2) = 470;
  data(3) = 170;
  data(4) = 430;
  data(5) = 300;

  ASSERT_DOUBLE_EQ(std::sqrt(21704), std_dev(data));
}
