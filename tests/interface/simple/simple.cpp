#include "admb.h"

int main(int argc,char * argv[])
{
  dvector x("{ -1, 0, 1, 2, 3, 4, 5, 6, 7, 8 }");
  dvector y("{ 1.4, 4.7, 5.1, 8.3, 9.0, 14.5, 14.0, 13.4, 19.2, 18.0 }");

  minimizer m(argc,argv);

  param_init_number b0("b0");
  param_init_number b1("b1");
  objective_function_value f("f");

  m.minimize([&x, &y, &b0, &b1, &f]()
  {
    auto yhat = b0 + b1 * x;
    f = regression(y, yhat);
  });

  cout << "b0: " << value(b0) << endl;
  cout << "b1: " << value(b1) << endl;
  cout << "f: " << value(f) << endl;

  return 0;
}
