/**
@file
@author David Fournier
@copyright Copyright (c) 2009-2020 ADMB Foundation

@brief Wrapper for betacf function.
*/
#include <fvar.hpp>
#include "betacf_val.hpp"

double betacf(const double a, const double b, const double x, int MAXIT){
  typedef double Float;
  return betacf<Float>(a,b,x,MAXIT);
}
