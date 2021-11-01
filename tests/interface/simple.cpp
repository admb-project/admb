#include "model_parameters.h"

class simple: public model_parameters
{
public:
  data_int n;
  data_vector x;
  data_vector y;

  param_init_number b0;
  param_init_number b1;
  param_vector yhat;
  objective_function_value f;

  simple(int argc, char * argv[]):
    model_parameters(argc, argv)
  {
    n.allocate("n");
    x.allocate(1,n,"x");
    y.allocate(1,n,"y");

    b0.allocate("b0");
    b1.allocate("b1");

    yhat.allocate(1, n, "yhat");
    yhat.initialize();

    f.allocate("f");
  }
  void userfunction()
  {
    f = 0.0;
    yhat = b0 + b1 * x;
    f = regression(y, yhat);
  }
};

int main(int argc,char * argv[])
{
  simple mp(argc,argv);
  mp.minimize(argc, argv);

  return 0;
}
