#include <gtest/gtest.h>
#include <fvar.hpp>
#include <adthread.h>

class test_adthread_manager: public ::testing::Test {};
TEST_F(test_adthread_manager, constructor)
{
  adpthread_manager am(1, 1);
}
TEST_F(test_adthread_manager, arr_link_constructor)
{
  arr_link al;
}
TEST_F(test_adthread_manager, arr_new)
{
  double_and_int* dai = arr_new(5);
  EXPECT_EQ(sizeof(void*), sizeof(vector_shape));
  //EXPECT_EQ(0, dai);
}

class test_dfpool: public ::testing::Test {};
TEST_F(test_dfpool, constructor)
{
  dfpool dfp;
}

class test_vector_shape_pool: public ::testing::Test {};
TEST_F(test_vector_shape_pool, constructor_pointer_size)
{
  size_t size = sizeof(void*);
  vector_shape_pool vsp(size);

  EXPECT_EQ(size, vsp.size);
}
TEST_F(test_vector_shape_pool, constructor_pointer_size_plus_one)
{
  size_t size = sizeof(void*);
  vector_shape_pool vsp(size + 1);

  EXPECT_EQ(size + 1, vsp.size);
}
TEST_F(test_vector_shape_pool, constructor_pointer_size_minus_one)
{
  size_t size = sizeof(void*);
  vector_shape_pool vsp(size - 1);

  EXPECT_EQ(size, vsp.size);
}
