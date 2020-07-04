#include <gtest/gtest.h>
#include <fvar.hpp>

class test_xpools: public ::testing::Test {};

TEST_F(test_xpools, sizes)
{
  ASSERT_EQ(vector_shape::get_xpool().size, sizeof(vector_shape));
  ASSERT_EQ(vector_shapex::get_xpool().size, sizeof(vector_shapex));
  ASSERT_EQ(arr_link::get_xpool().size, sizeof(arr_link));
}
