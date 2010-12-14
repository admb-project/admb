/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */


#include "fvar.hpp"

  /** Log negative bionomial density; constant objects.
  \ingroup PDF
  \param x
  \param mu
  \param tau
  \return 
  */
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

  /** Negative bionomial density; constant objects.
  \ingroup PDF
  \param x
  \param mu
  \param tau
  \return 
  */ 
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

  /**  Log Poisson density; constant objects.
  \ingroup PDF
  \param x Number of observed occurences, \f$k\f$.
  \param mu Mean or expected value, \f$\mu\f$.
  \return Log of Poisson density. \f$-\mu+k*\log(\mu)-k!\f$.
  */
  double log_density_poisson(double x,double mu)
  {
    return -mu+x*log(mu)-gammln(x+1);
  }
    
