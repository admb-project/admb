/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
/**
 * \file
 * Description not yet available.
 */
#include "df1b2fun.h"

/**
Log negative bionomial density; random effects objects.
A local parameter r is used to make it robust.
\f$ r=\frac{\mu}{\tau-1.0} \f$
\ingroup PDF
\param x
\param mu
\param tau
\return Log of NegativeBinomial density. \f$ log(\Gamma(x+r))-log(\Gamma(r))-log(x!)+rlog(r)+xlog(\mu)-(r+x)log(r+\mu) \f$
*/
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


/** Negative bionomial density; random effects objects.
 A local parameter r is used to make it robust.
 \f$ r=\frac{\mu}{10.0^{-120}+\tau-1.0} \f$
 \ingroup PDF
 \param x
 \param mu
 \param tau
 \return NegativeBinomial density. \f$ \frac{\Gamma(x+r)}{\Gamma(r)x!}(\frac{r}{r+\mu})^r(\frac{\mu}{r+\mu})^x \f$
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

/**  Log Poisson density; random effects objects.
 \ingroup PDF
 \param x Number of observed occurences, \f$k\f$.
 \param mu Mean or expected value, \f$\mu\f$.
 \return Log of Poisson density. \f$-\mu+k*\log(\mu)-k!\f$.
 */


  df1b2variable log_density_poisson(double x,const df1b2variable& mu)
  {
    return -mu+x*log(mu)-gammln(x+1);
  }

