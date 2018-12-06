#include <gtest/gtest.h>
#include <functional>
#include <future>
#include <admodel.h>

class test_template: public ::testing::Test {};

namespace admb
{
	/*
  class independent_variable: public initial_params
  {
  public:
  independent_variable()
  {
    initial_params::allocate(1);
  }
  independent_variable(const independent_variable&) = delete;
  ~independent_variable()
  {
  }
  independent_variable& operator=(const independent_variable&) = delete;
  independent_variable& operator=(independent_variable&&) = delete;
  };
  */
  class model: public function_minimizer
  {
  std::function<void()> _run;

  public:
  model() 
  { 
    initial_params::varsptr.initialize();
  }
  model(const std::function<void()>& run): _run(run) 
  { 
    initial_params::varsptr.initialize();
  }
  model(const model&) = delete;
  model(model&&) = delete;
  virtual ~model() { }

  model& operator=(const model&) = delete;
  model& operator=(model&&) = delete;
  void set_userfunction(std::function<void()> run)
  {
    _run = run;
  }
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

void simple()
{
  cout << __FILE__ << ':' << __LINE__ << endl;
/*
  const int n = 10;
  dvector x("{-1, 0, 1, 2, 3, 4, 5, 6, 7, 8}");
  cout << x << endl;
  //dvector y{1.4, 4.7, 5.1, 8.3, 9.0, 14.5, 14.0, 13.4, 19.2, 18.0};
*/
/*
  independent_variable b0;   
  independent_variable b1;   
  dvar_vector yhat;
  yhat = b0 + b1 * x;
  dvariable f = regression(y, yhat);
  return std::move(f);
*/
}

TEST_F(test_template, simple)
{
  admb::minimize(simple);
}
TEST_F(test_template, lamda)
{
  admb::minimize([]() { return simple(); });
}
TEST_F(test_template, async_minimize_simple)
{
  std::async([]()
  {
    admb::minimize([]() { return simple(); });
  });
}
