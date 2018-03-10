#include <memory>
#include <fvar.hpp>
#include <gtest/gtest.h>

class test_shared_ptr: public ::testing::Test {};

TEST_F(test_shared_ptr, default_constructor)
{
  std::shared_ptr<double_and_int> ptr(NULL);
  EXPECT_EQ(ptr.use_count(), 0);
  EXPECT_TRUE(ptr == NULL);
}
TEST_F(test_shared_ptr, default_constructor_NULL)
{
  std::shared_ptr<double_and_int> ptr2(NULL);
  std::shared_ptr<double_and_int> ptr(ptr2);
  EXPECT_EQ(ptr.use_count(), 0);
  EXPECT_TRUE(ptr == NULL);
}
TEST_F(test_shared_ptr, allocated)
{
  std::shared_ptr<double_and_int> ptr(new double_and_int);
  EXPECT_EQ(ptr.use_count(), 1);
  EXPECT_TRUE(ptr != NULL);
}
TEST_F(test_shared_ptr, allocated2x)
{
  std::shared_ptr<double_and_int> ptr2(new double_and_int);
  std::shared_ptr<double_and_int> ptr(ptr2);
  EXPECT_EQ(ptr.use_count(), 2);
  EXPECT_TRUE(ptr != NULL);
}
TEST_F(test_shared_ptr, equals)
{
  std::shared_ptr<double_and_int> ptr2(new double_and_int);
  std::shared_ptr<double_and_int> ptr(ptr2);
  ptr->x = 2.0;

  EXPECT_DOUBLE_EQ(ptr->x, ptr2->x);
}
TEST_F(test_shared_ptr, move)
{
  std::shared_ptr<double_and_int> ptr2(new double_and_int);
  ptr2->x = 2.0;
  std::shared_ptr<double_and_int> ptr(std::move(ptr2));
  EXPECT_TRUE(ptr2 == NULL);
  EXPECT_EQ(ptr2.use_count(), 0);
  EXPECT_EQ(ptr.use_count(), 1);

  EXPECT_DOUBLE_EQ(ptr->x, 2.0);
}
