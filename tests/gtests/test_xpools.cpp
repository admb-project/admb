#include <gtest/gtest.h>
#include <fvar.hpp>

class test_xpools: public ::testing::Test {};

#ifdef USE_VECTOR_SHAPE_POOL
TEST_F(test_xpools, sizes)
{
#ifdef USE_VECTOR_SHAPE_POOL
  ASSERT_EQ(vector_shape::xpool->size, sizeof(vector_shape));
  ASSERT_EQ(vector_shapex::xpool->size, sizeof(vector_shapex));
  ASSERT_EQ(arr_link::xpool->size, sizeof(arr_link));
#endif
}
#endif
