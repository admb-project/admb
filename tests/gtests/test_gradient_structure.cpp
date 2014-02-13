#include <gtest/gtest.h>
#include <fvar.hpp>

class test_gradient_structure :public ::testing::Test {};

TEST_F(test_gradient_structure, checktypes)
{
  ASSERT_EQ(sizeof(long long), sizeof(long long int));
}
/*
TEST_F(test_gradient_structure, default_constructor)
{
  gradient_structure gs;
}
*/
