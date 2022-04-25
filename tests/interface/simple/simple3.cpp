#include <future>
#include "model_parameters.h"

void compute(dvector& x, dvector& y, dvariable& b0, dvariable& b1, dvar_vector& yhat, objective_function_value& f)
{
  yhat = b0 + b1 * x;
  f = regression(y, yhat);
}

class simple: public model_parameters
{
  std::function<void(void)> f;

public:
  simple(int argc, char * argv[]):
    model_parameters(argc, argv)
  {
  }
  void minimize(int argc, char* argv[], std::function<void(void)> user_function)
  {
    f = std::move(user_function);
    model_parameters::minimize(argc, argv);
  }
  void userfunction()
  {
    f();
  }
};

int main(int argc,char * argv[])
{
  simple mp(argc,argv);

  data_int n;
  data_vector x;
  data_vector y;

  param_init_number b0;
  param_init_number b1;
  param_vector yhat;
  objective_function_value f;

  n.allocate("n");
  x.allocate(1,n,"x");
  y.allocate(1,n,"y");

  b0.allocate("b0");
  b1.allocate("b1");

  yhat.allocate(1, n, "yhat");
  yhat.initialize();

  f.allocate("f");

  mp.minimize(argc, argv, [&x, &y, &b0, &b1, &yhat, &f]()
  {
    compute(x, y, b0, b1, yhat, f);
  });

  return 0;
}
