#include <gtest/gtest.h>
#include <fvar.hpp>

class test_xpools: public ::testing::Test {};

#ifdef USE_VECTOR_SHAPE_POOL
TEST_F(test_xpools, sizes)
{
  ASSERT_EQ(vector_shape::get_xpool().size, sizeof(vector_shape));
  ASSERT_EQ(vector_shapex::get_xpool().size, sizeof(vector_shapex));
}
#endif
