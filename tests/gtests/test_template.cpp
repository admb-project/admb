#include <gtest/gtest.h>
#include <functional>
#include <future>
#include <admodel.h>

class test_template: public ::testing::Test {};

namespace admb
{
  /// variable has a value, derivative and name.
  typedef std::tuple<double, double, std::string> variable;
  /// bounds has a value, minimum and maximum bounds.
  typedef std::tuple<double, double, double> bounds;
  /// bounded_variable has bounds, derivative and name.
  typedef std::tuple<bounds, double, std::string> bounded_variable;

  class model: public function_minimizer
  {
  std::function<dvariable(dvariable&, dvariable&)> _run;
  param_init_number b0;
  param_init_number b1;
  objective_function_value f;

  public:
  model(const std::function<dvariable(dvariable&, dvariable&)>& run): _run(run) 
  { 
    // Points to independent variables
    initial_params::varsptr.initialize();

    b0.allocate("b0");
    b1.allocate("b1");
  }
  model(const model&) = delete;
  model(model&&) = delete;
  virtual ~model() { }

  model& operator=(const model&) = delete;
  model& operator=(model&&) = delete;
  void userfunction()
  {
    //f = _parameters.run();
    f = _run(b0, b1);
  }
  };

  template <typename procedure_section>
  void minimize(const procedure_section& run)
  {
    model m(run);

    m.minimize();
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

TEST_F(test_template, lamda)
{
	/*
  gradient_structure gs;

  param_init_number a0;
  param_init_number a1;
  a0.allocate("a0");
  a1.allocate("a1");
  */

  dvector x("{-1, 0, 1, 2, 3, 4, 5, 6, 7, 8}");
  dvector y("{1.4, 4.7, 5.1, 8.3, 9.0, 14.5, 14.0, 13.4, 19.2, 18.0}");
  admb::minimize([&x, &y](dvariable& b0, dvariable& b1)
  {
    dvar_vector yhat = b0 + b1 * x;
    return regression(y, yhat);
  });
}

/*
void empty() {}

TEST_F(test_template, empty)
{
  admb::minimize(empty);
}
TEST_F(test_template, lamda)
{
  admb::minimize([]() { return empty(); });
}
TEST_F(test_template, async_minimize_empty)
{
  std::async([]()
  {
    admb::minimize([]() { return empty(); });
  });
}
TEST_F(test_template, sequence_2xempty)
{
  admb::minimize(empty);
  admb::minimize(empty);
}
*/
