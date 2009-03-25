/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */



#define HOME_VERSION
#include "df1b2fun.h"


/*
  df1b2variable log_negbinomial_density(double x,const df1b2variable& mu, 
    const df1b2variable& tau)
  {
    if (value(tau)<=1.0)
    {
      cerr << "tau <=1 in log_negbinomial_density " << endl;
      ad_exit(1);
    }
    df1b2variable r=mu/(tau-1.0);
    df1b2variable tmp;
    tmp=gammln(x+r)-gammln(r) -gammln(x+1)
      +r*log(r)+x*log(mu)-(r+x)*log(r+mu);
    return tmp;
  }
*/


  df1b2variable negbinomial_density(double x,const df1b2variable& mu, 
    const df1b2variable& tau)
  {
    if (value(tau)-1<0.0)
    {
      cerr << "tau <=1 in log_negbinomial_density " << endl;
      ad_exit(1);
    }
    df1b2variable r=mu/(1.e-120+tau-1.0);
    df1b2variable tmp;
    tmp=exp(gammln(x+r)-gammln(r) -gammln(x+1)
      +r*log(r)+x*log(mu)-(r+x)*log(r+mu));
    return tmp;
  }



  df1b2variable log_density_poisson(double x,const df1b2variable& mu)
  {
    return -mu+x*log(mu)-gammln(x+1);
  }

