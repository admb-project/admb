#include <gtest/gtest.h>
#include "admodel.h"

class test_data_matrix: public ::testing::Test {};

TEST_F(test_data_matrix, constructor)
{
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
