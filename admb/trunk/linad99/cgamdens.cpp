/**
  * $Id:   $
  *
  * $Rev   ::                       $: Revision of last commit
  * $Author::                       $: Author of last commit
  * $Date  ::                       $: Date of last commit
  *
  * Author: David Fournier
  * Copyright (c) 2008 Regents of the University of California 
  */
#define HOME_VERSION
double get_values(double x,double y,int print_switch);


#include "fvar.hpp"

  double gamma_density(double x,double r, double mu)
  {
    return exp(r*log(mu) + (r-1)*log(x)-mu*x-gammln(r));
  }
    
  double log_gamma_density(double x,double r, double mu)
  {
    return r*log(mu) + (r-1)*log(x)-mu*x-gammln(r);
  }
    

