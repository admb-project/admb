#include <fvar.hpp>
#include <math.h>

#include "betacf.hpp"

dvariable betacf(const dvariable& _a, const dvariable& _b, const dvariable& _x, int MAXIT)
{
  double a=value(_a);
  double b=value(_b);
  double x=value(_x);

  dvariable hh;
  value(hh) = betacf(a, b, x, MAXIT);
  
  typedef tiny_ad::variable<1, 3> Float;
  Float a_ (a, 0);
  Float b_ (b, 1);
  Float x_ (x, 2);
  Float ans = betacf<Float>(a_, b_, x_, MAXIT);

  //value(hh) = ans.value;
  tiny_vec<double, 3> der = ans.getDeriv();

  gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation3ind, &(value(hh)), 
                         &(value(_a)), der[0] ,&(value(_b)), der[1], &(value(_x)), der[2]);
  return hh;
}

