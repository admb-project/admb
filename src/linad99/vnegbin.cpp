/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
/**
 * \file
 * Description not yet available.
 */
#include "fvar.hpp"

  /** Log negative bionomial density; variable objects.
  \ingroup PDF
  \param x
  \param mu
  \param tau
  \return 
  */
  dvariable log_negbinomial_density(double x,const prevariable& mu, 
    const prevariable& tau)
  {
    if (value(tau)-1.0<0.0)
    {
      cerr << "tau <=1 in log_negbinomial_density " << endl;
      ad_exit(1);
    }
    RETURN_ARRAYS_INCREMENT();	
    dvariable r=mu/(1.e-120+(tau-1));
    dvariable tmp;
    tmp=gammln(x+r)-gammln(r) -gammln(x+1)
      +r*log(r)+x*log(mu)-(r+x)*log(r+mu);
    RETURN_ARRAYS_DECREMENT();	
    return tmp;
  }

  /** Negative bionomial density; variable objects.
  \ingroup PDF
  \param x
  \param mu
  \param tau
  \return 
  */ 
  dvariable negbinomial_density(double x,const prevariable& mu, 
    const prevariable& tau)
  {
    if (value(tau)-1.0<=0.0)
    {
      cerr << "tau <=1 in log_negbinomial_density " << endl;
      ad_exit(1);
    }
    RETURN_ARRAYS_INCREMENT();	
    dvariable r=mu/(1.e-120+(tau-1));
    dvariable tmp;
    //tmp=exp(gammln(x+r)-gammln(r) -gammln(x+1)
     // +r*log(r)+x*log(mu)-(r+x)*log(r+mu));
    tmp=gammln(x+r);
    tmp-=gammln(r);
    tmp-=gammln(x+1);
    tmp+=r*log(r);
    tmp+=x*log(mu);
    tmp-=(r+x)*log(r+mu);
    tmp=exp(tmp);


    RETURN_ARRAYS_DECREMENT();	
    return tmp;
  }

  /**  Log Poisson density; variable objects.
  \ingroup PDF
  \param x Number of observed occurences, \f$k\f$.
  \param mu Mean or expected value, \f$\mu\f$.
  \return Log of Poisson density. \f$-\mu+k \log(\mu)-\log(k!)\f$.
  */
  dvariable log_density_poisson(double x,const prevariable& mu)
  {
    return -mu+x*log(mu)-gammln(x+1);
  }
