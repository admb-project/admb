#include <gtest/gtest.h>
#include <adpool.h>

class test_adpool: public ::testing::Test {};

TEST_F(test_adpool, default_constructor_set_size)
{
  adpool a;
  ASSERT_EQ(0, a.size);

  a.set_size(1);
  ASSERT_EQ(1, a.size);

  a.set_size(-1);
  ASSERT_LT(0, a.size);

  a.set_size(0);
  ASSERT_EQ(0, a.size);
}
