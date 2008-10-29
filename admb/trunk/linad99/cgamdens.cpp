#define HOME_VERSION
double get_values(double x,double y,int print_switch);

//COPYRIGHT (c) 2005 OTTER RESEARCH LTD

#include "fvar.hpp"

  double gamma_density(double x,double r, double mu)
  {
    return exp(r*log(mu) + (r-1)*log(x)-mu*x-gammln(r));
  }
    
  double log_gamma_density(double x,double r, double mu)
  {
    return r*log(mu) + (r-1)*log(x)-mu*x-gammln(r);
  }
    

