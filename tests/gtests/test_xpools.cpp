#include <gtest/gtest.h>
#include <fvar.hpp>

class test_xpools: public ::testing::Test {};

TEST_F(test_xpools, sizes)
{
#ifdef USE_VECTOR_SHAPE_POOL
  if (!vector_shape::xpool)
  {
    vector_shape::xpool = new vector_shape_pool(sizeof(vector_shape));
  }
  if (!vector_shapex::xpool)
  {
    vector_shapex::xpool = new vector_shape_pool(sizeof(vector_shapex));
  }
  if (!arr_link::xpool)
  {
    arr_link::xpool = new vector_shape_pool(sizeof(arr_link));
  }
  ASSERT_EQ(vector_shape::xpool->size, sizeof(vector_shape));
  ASSERT_EQ(vector_shapex::xpool->size, sizeof(vector_shapex));
  ASSERT_EQ(arr_link::xpool->size, sizeof(arr_link));
#endif
}
