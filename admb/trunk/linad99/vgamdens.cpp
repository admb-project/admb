/**
  * $Id$
  *
  * $Rev   ::                       $: Revision of last commit
  * $Author::                       $: Author of last commit
  * $Date  ::                       $: Date of last commit
  *
  * Author: David Fournier
  * Copyright (c) 2008 Regents of the University of California 
  */

#define HOME_VERSION
#include <fvar.hpp>



  dvariable log_gamma_density(const prevariable& _x,double r, double mu)
  {
    prevariable& x= (prevariable&)(_x);

    return r*log(mu) + (r-1)*log(x)-mu*x-gammln(r);
  }
    
  dvariable log_gamma_density(const dvariable& _x,const dvariable& _r,
    const  dvariable& _mu)
  {
    prevariable& x= (prevariable&)(_x);
    prevariable& r= (prevariable&)(_r);
    prevariable& mu= (prevariable&)(_mu);
    return r*log(mu) + (r-1)*log(x)-mu*x-gammln(r);
  }
    
    
  dvariable gamma_density(const prevariable& _x,double r, double mu)
  {
    prevariable& x= (prevariable&)(_x);

    return exp(r*log(mu) + (r-1)*log(x)-mu*x-gammln(r));
  }
    
  dvariable gamma_density(const dvariable& _x,const dvariable& _r,
    const  dvariable& _mu)
  {
    prevariable& x= (prevariable&)(_x);
    prevariable& r= (prevariable&)(_r);
    prevariable& mu= (prevariable&)(_mu);
    return exp(r*log(mu) + (r-1)*log(x)-mu*x-gammln(r));
  }
    
    
