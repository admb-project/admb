/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
/**
 * \file
 * Description not yet available.
 */
#include "fvar.hpp"

  /** Log negative bionomial density; constant objects.
   A local parameter r is used to make it robust.
   \f$ r=\frac{\mu}{10.0^{-120}+\tau-1.0} \f$
  \ingroup PDF
  \param x
  \param mu
  \param tau
  \return Log of NegativeBinomial density. \f$ log(\Gamma(x+r))-log(\Gamma(r))-log(x!)+rlog(r)+xlog(\mu)-(r+x)log(r+\mu) \f$
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
   A local parameter r is used to make it robust.
   \f$ r=\frac{\mu}{10.0^{-120}+\tau-1.0} \f$
  \ingroup PDF
  \param x
  \param mu
  \param tau
  \return NegativeBinomial density. \f$ \frac{\Gamma(x+r)}{\Gamma(r)x!}(\frac{r}{r+\mu})^r(\frac{\mu}{r+\mu})^x \f$
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
