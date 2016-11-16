#include <iostream>
using std::cout;
using std::endl;
#include <gtest/gtest.h>

#define TINY_AD_USE_TINY_VEC
#include <tiny_ad.hpp>

class test_tiny_ad: public ::testing::Test {};

TEST_F(test_tiny_ad, report_example_5_3)
{
  // Track 3rd order derivs wrt. 2 parameters
  typedef tiny_ad::variable<3, 2> Float;

  // Let a = 1.23 have parameter index 0
  Float a (1.23, 0);                   

  // Let b = 2.34 have parameter index 1
  Float b (2.34, 1);

  // Run the algorithm
  Float y = a * sin(a + b);

  // Get all 3rd order derivatives
  tiny_vec<double, 8> res = y.getDeriv();

  const double abs_error = 0.00001;
  ASSERT_NEAR(2.36511, res[0], abs_error);
  ASSERT_NEAR(1.94969, res[1], abs_error);
  ASSERT_NEAR(1.94969, res[2], abs_error);
  ASSERT_NEAR(1.53427, res[3], abs_error);
  ASSERT_NEAR(1.94969, res[4], abs_error);
  ASSERT_NEAR(1.53427, res[5], abs_error);
  ASSERT_NEAR(1.53427, res[6], abs_error);
  ASSERT_NEAR(1.11884, res[7], abs_error);
}
TEST_F(test_tiny_ad, x2_1deriv)
{
  // Track 3rd order derivs wrt. 2 parameters
  typedef tiny_ad::variable<1, 1> Float;

  // Let x = 1.23 have parameter index 0
  Float x (1.23, 0);                   

  // Run the algorithm
  Float y = x * x;

  // Get all 3rd order derivatives
  tiny_vec<double, 1> res = y.getDeriv();

  const double abs_error = 0.00001;
  ASSERT_NEAR(2.46, res[0], abs_error);
}
TEST_F(test_tiny_ad, x2_2deriv)
{
  // Track 3rd order derivs wrt. 2 parameters
  typedef tiny_ad::variable<2, 1> Float;

  // Let x = 1.23 have parameter index 0
  Float x (1.23, 0);                   

  // Run the algorithm
  Float y = x * x;

  // Get all 3rd order derivatives
  tiny_vec<double, 1> res = y.getDeriv();

  const double abs_error = 0.00001;
  ASSERT_NEAR(2, res[0], abs_error);
}
TEST_F(test_tiny_ad, x2_3deriv)
{
  // Track 3rd order derivs wrt. 2 parameters
  typedef tiny_ad::variable<3, 1> Float;

  // Let x = 1.23 have parameter index 0
  Float x (1.23, 0);                   

  // Run the algorithm
  Float y = x * x;

  // Get all 3rd order derivatives
  tiny_vec<double, 1> res = y.getDeriv();

  const double abs_error = 0.00001;
  ASSERT_NEAR(0, res[0], abs_error);
}
TEST_F(test_tiny_ad, yx_1deriv)
{
  // Track 3rd order derivs wrt. 2 parameters
  typedef tiny_ad::variable<1, 2> Float;

  // Let x = 1.23 have parameter index 0
  Float x (1.23, 0);                   

  // Let y = 2.34 have parameter index 1
  Float y (2.34, 1);

  // Run the algorithm
  Float xy = x * y;

  // Get all 3rd order derivatives
  tiny_vec<double, 2> res = xy.getDeriv();

  const double abs_error = 0.00001;
  ASSERT_NEAR(2.34, res[0], abs_error);
  ASSERT_NEAR(1.23, res[1], abs_error);
}
TEST_F(test_tiny_ad, yx_2deriv)
{
  // Track 3rd order derivs wrt. 2 parameters
  typedef tiny_ad::variable<2, 2> Float;

  // Let x = 1.23 have parameter index 0
  Float x (1.23, 0);                   

  // Let y = 2.34 have parameter index 1
  Float y (2.34, 1);

  // Run the algorithm
  Float xy = x * y;

  // Get all 3rd order derivatives
  tiny_vec<double, 4> res = xy.getDeriv();

  const double abs_error = 0.00001;
  ASSERT_NEAR(0, res[0], abs_error);
  ASSERT_NEAR(1, res[1], abs_error);
  ASSERT_NEAR(1, res[2], abs_error);
  ASSERT_NEAR(0, res[3], abs_error);
}
