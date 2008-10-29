

#define HOME_VERSION
//COPYRIGHT (c) 2003 OTTER RESEARCH LTD
#include "fvar.hpp"

  double log_density_negbinomial(double x,double mu,double tau)
  {
    if (tau-1.0<0.0)
    {
      cerr << "tau <=1 in log_negbinomial_density " << endl;
      ad_exit(1);
    }
    double r=mu/(1.e-120+(tau-1.0));
    return gammln(x+r)-gammln(r)-gammln(x+1)
      +r*log(r)+x*log(mu)-(r+x)*log(r+mu);
  }
  double density_negbinomial(double x,double mu,double tau)
  {
    if (tau-1.0<0.0)
    {
      cerr << "tau <=1 in negbinomial_density " << endl;
      ad_exit(1);
    }
    double r=mu/(1.e-120+(tau-1.0));
    return exp(gammln(x+r)-gammln(r)-gammln(x+1)
      +r*log(r)+x*log(mu)-(r+x)*log(r+mu));
  }
    
  double log_density_poisson(double x,double mu)
  {
    return -mu+x*log(mu)-gammln(x+1);
  }
    
