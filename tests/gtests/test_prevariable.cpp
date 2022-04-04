#include <gtest/gtest.h>
#include <fvar.hpp>

extern "C"
{
  void test_ad_exit(const int exit_code);
}

class test_prevariable: public ::testing::Test {};

TEST_F(test_prevariable, copy_constructor)
{
  gradient_structure gs;
  // prevariable p;
  // prevariable p(nullptr);

  dvar_vector v(1, 1);

  const prevariable& a = v(1);
  prevariable p(a);

  ASSERT_TRUE(v(1).v == p.v);
}
