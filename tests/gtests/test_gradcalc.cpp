#include <gtest/gtest.h>
#include <fvar.hpp>

extern "C"
{
  void test_ad_exit(const int exit_code);
}

class test_gradcalc: public ::testing::Test {};

TEST_F(test_gradcalc, nvarzero)
{
  ad_exit=&test_ad_exit;

  dvector g;

  //ASSERT_EQ(0, gradient_structure::NVAR);

  ASSERT_ANY_THROW({
    gradcalc(1, g);
  });
}
