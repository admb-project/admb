#include <gtest/gtest.h>
#include <functional>
#include <future>
#include <admodel.h>

class test_template: public ::testing::Test {};

namespace admb
{
  class independent_variable: public named_dvariable
  {
  public:
  independent_variable() { }
  independent_variable(const independent_variable&) = delete;
  independent_variable(independent_variable&&) = delete;
  ~independent_variable() { }
  independent_variable& operator=(const independent_variable&) = delete;
  independent_variable& operator=(independent_variable&&) = delete;
  };

  class model: public function_minimizer
  {
  std::function<void()> _run;

  public:
  model() = delete;
  model(const std::function<void()>& run): _run(run) 
  { 
    // Points to independent variables
    initial_params::varsptr.initialize();
  }
  model(const model&) = delete;
  model(model&&) = delete;
  virtual ~model() { }

  model& operator=(const model&) = delete;
  model& operator=(model&&) = delete;
  void userfunction()
  {
    _run();
  }
  };

  template <typename procedure_section>
  void minimize(procedure_section&& run)
  {
    model m(run);

    param_init_number b0;
    b0.allocate("bo");

    objective_function_value f;

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

void empty() {}

//void parameters(independent_variable& b0, independent_variable& b1) {}

void simple()
{
  cout << __FILE__ << ':' << __LINE__ << endl;
/*
  dvector x("{-1, 0, 1, 2, 3, 4, 5, 6, 7, 8}");
  dvector y{1.4, 4.7, 5.1, 8.3, 9.0, 14.5, 14.0, 13.4, 19.2, 18.0};

  independent_variable b0;   
  independent_variable b1;   
  dvar_vector yhat = b0 + b1 * x;
  return regression(y, yhat);
*/
}

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
/*
TEST_F(test_template, parameters)
{
  independent_variable a;
  independent_variable b;

  admb::minimize([&a, &b]() { return parameters(a, b); });
}
*/
