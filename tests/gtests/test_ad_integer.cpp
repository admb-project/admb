#include <gtest/gtest.h>
#include <fvar.hpp>

class test_ad_integer: public ::testing::Test {};

TEST_F(test_ad_integer, constructor)
{
  int l = __LINE__;
  ad_integer i(l);
  
  ASSERT_EQ(int(i), l);

  int l2 = __LINE__;

  ad_integer j = i.make_ad_integer(l2);

  ASSERT_EQ(int(j), l2);
}
