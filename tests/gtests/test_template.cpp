#include <gtest/gtest.h>
#include <functional>
#include <future>

class test_template: public ::testing::Test {};

namespace admb
{
  template <typename procedure_section>
  void minimize(procedure_section&& run)
  {
    run();
  }
}

using std::cout;
using std::endl;

/*
# number of observations
10
# x values
-1  0  1  2  3  4  5  6  7  8
# y values
1.4  4.7  5.1  8.3  9.0  14.5  14.0  13.4  19.2  18.0

DATA_SECTION
  init_int n
  init_vector x(1,n)
  init_vector y(1,n)
PARAMETER_SECTION
  init_number b0
  init_number b1
  vector yhat(1,n)
  objective_function_value f
PROCEDURE_SECTION
  yhat=b0+b1*x;
  f=regression(y,yhat);
*/

void simple()
{
  cout << __FILE__ << ':' << __LINE__ << endl;
/*
  const int n = 10;
  dvector x{-1, 0, 1, 2, 3, 4, 5, 6, 7, 8};
  dvector y{1.4, 4.7, 5.1, 8.3, 9.0, 14.5, 14.0, 13.4, 19.2, 18.0};
  independent_variable b0;   
  independent_variable b1;   
  dvar_vector yhat;
  yhat = b0 + b1 * x;
  dvariable f = regression(y, yhat);
  return std::move(f);
*/
}
double simple_with_return()
{
  return 1.3;
}

TEST_F(test_template, simple)
{
  admb::minimize(simple);
}
TEST_F(test_template, async_simple)
{
  std::async(simple);
  /*
  auto result = std::async(admb::minimize, simple_with_return);
  auto result2 = std::async(admb::minimize, simple_with_return2);
  ASSERT_DOUBLE_EQ(result, 1.3);
  ASSERT_DOUBLE_EQ(result2, 2.3);
  */
}
TEST_F(test_template, simple_with_data_parameters)
{
  //dvector x{-1, 0, 1, 2, 3, 4, 5, 6, 7, 8};
  //dvector y{1.4, 4.7, 5.1, 8.3, 9.0, 14.5, 14.0, 13.4, 19.2, 18.0};
  //admb::minimize(simple, x, y);
}
