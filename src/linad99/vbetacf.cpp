/**
@file
@author David Fournier
@copyright Copyright (c) 2008-2020 Regents of the University of California

@brief Function betacf(const dvariable&, const dvariable&, const dvariable&, int MAXIT)
*/

#include <fvar.hpp>
#include "betacf_val.hpp"

dvariable betacf(const dvariable& a, const dvariable& b, const dvariable& x, int MAXIT)
{  
  typedef tiny_ad::variable<1, 3> Float;
  Float a_ (value(a), 0);
  Float b_ (value(b), 1);
  Float x_ (value(x), 2);
  Float ans = betacf<Float>(a_, b_, x_, MAXIT);
  tiny_vec<double, 3> der = ans.getDeriv();

  dvariable hh;
  value(hh) = ans.value;
  gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation3ind, &(value(hh)), 
                         &(value(a)), der[0] ,&(value(b)), der[1], &(value(x)), der[2]);
  return hh;
}
