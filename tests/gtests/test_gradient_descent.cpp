#include <functional>
#include <cmath>
#include <gtest/gtest.h>

class test_gradient_descent: public ::testing::Test {};

double gradient_descent(
  // Initial guess
  const double x0,
  // Targeted error
  const double minimum_error,
  // Step size is not adaptive
  const double gamma,
  // Adjoint function
  std::function<double(double)> dfx)
{
  double current_x = x0;
  double current_error = 0;

  do
  {
    double previous_x = current_x;
    current_x -= gamma * dfx(previous_x);
    current_error = std::abs(current_x - previous_x);
    printf("current: x = %f and error = %f\n", current_x, current_error);
  } while (minimum_error < current_error);

  return current_x;
}

TEST_F(test_gradient_descent, wiki)
{
  std::function<double(double)> dfx =
    [](double x) { return 4*(x*x*x) - 9*(x*x); };

  //from https://en.wikipedia.org/wiki/Gradient_descent
  ASSERT_NEAR(gradient_descent(6, 0.00001, 0.01, dfx), 2.249965, 0.000001);
}
TEST_F(test_gradient_descent, xsquare)
{
  std::function<double(double)> dfx =
    [](double x) { return 2.0 * x; };

  //from https://en.wikipedia.org/wiki/Gradient_descent
  ASSERT_NEAR(gradient_descent(6, 0.0000001, 0.001, dfx), 0.0, 0.0001);
}
