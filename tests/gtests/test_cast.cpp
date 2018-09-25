#include <gtest/gtest.h>
#include <fvar.hpp>

class test_cast: public ::testing::Test {};

bool func_withconst(const dvector& v) { return true; }
bool func_noconst(dvector& v) { return true; }
bool func_rvalue(dvector&& v) { return true; }

TEST_F(test_cast, func)
{
  dvector v2;
  ASSERT_TRUE(func_withconst(v2));
  ASSERT_TRUE(func_noconst(v2));

  const dvector v;
  ASSERT_TRUE(func_withconst(v));
  ASSERT_TRUE(func_noconst((dvector&)v));
}
