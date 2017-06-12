#include <gtest/gtest.h>
#include "admodel.h"

class test_param_init_bounded_number_matrix: public ::testing::Test {};

TEST_F(test_param_init_bounded_number_matrix, constructor)
{
  gradient_structure gs;

  param_init_bounded_number_matrix n;
  ASSERT_FALSE(n.allocated());
  ASSERT_EQ(0, n.indexmin());
  ASSERT_EQ(-1, n.indexmax());
}
TEST_F(test_param_init_bounded_number_matrix, allocate)
{
  gradient_structure gs;

  param_init_bounded_number_matrix n;

  dmatrix bmin(1, 3, 2, 4);
  dmatrix bmax(1, 3, 2, 4);
  n.allocate(1, 3, 2, 4, bmin, bmax, "id");

  ASSERT_TRUE(n.allocated());
  ASSERT_EQ(1, n.indexmin());
  ASSERT_EQ(3, n.indexmax());
  ASSERT_EQ(2, n[1].indexmin());
  ASSERT_EQ(4, n[1].indexmax());
  ASSERT_EQ(2, n[2].indexmin());
  ASSERT_EQ(4, n[2].indexmax());
  ASSERT_EQ(2, n[3].indexmin());
  ASSERT_EQ(4, n[3].indexmax());

  n.set_scalefactor(1.4);

  dmatrix scalefactor(1, 3, 2, 4);
  scalefactor = n.get_scalefactor();

  for (int i = 1; i <= 3; ++i)
  {
    for (int j = 2; j <= 4; ++j)
    {
      ASSERT_DOUBLE_EQ(1.4, scalefactor(i, j));
      ASSERT_DOUBLE_EQ(1.4, n(i, j).get_scalefactor());
    }
  }
  scalefactor.initialize();
  n.set_scalefactor(scalefactor);
  for (int i = 1; i <= 3; ++i)
  {
    for (int j = 2; j <= 4; ++j)
    {
      ASSERT_DOUBLE_EQ(0, n(i, j).get_scalefactor());
    }
  }
}
