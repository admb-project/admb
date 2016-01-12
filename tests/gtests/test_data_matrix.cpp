#include <gtest/gtest.h>
#include "admodel.h"

extern "C"
{
  void test_ad_exit(const int exit_code);
}

class test_data_matrix: public ::testing::Test {};

TEST_F(test_data_matrix, constructor)
{
  ad_exit=&test_ad_exit;

  data_matrix m;

  ASSERT_STREQ("\0", m.get_name());
  ASSERT_EQ(1, m.rowmin());
  ASSERT_EQ(0, m.rowmax());
  ASSERT_THROW(m.colmin(), int);
  ASSERT_THROW(m.colmax(), int);
  std::cout << std::endl;
}
TEST_F(test_data_matrix, empty_assignment_double)
{
  ad_exit=&test_ad_exit;

  data_matrix m;
  double d = 5;
  m = d;

  ASSERT_STREQ("\0", m.get_name());
  ASSERT_EQ(1, m.rowmin());
  ASSERT_EQ(0, m.rowmax());
  ASSERT_THROW(m.colmin(), int);
  ASSERT_THROW(m.colmax(), int);
  std::cout << std::endl;
}
