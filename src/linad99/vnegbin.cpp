/**
@file
@author David Fournier
@copyright Copyright (c) 2008-2020 Regents of the University of California

@brief Poisson and negative binomial probability density functions for differentiable objects.
*/
#include "fvar.hpp"


/** Log negative bionomial density; variable objects.
 A local parameter r is used to make it robust.
 \f$ r=\frac{\mu}{10.0^{-120}+\tau-1.0} \f$
 \ingroup PDF
 \param x
 \param mu
 \param tau
 \return Log of NegativeBinomial density. \f$ log(\Gamma(x+r))-log(\Gamma(r))-log(x!)+rlog(r)+xlog(\mu)-(r+x)log(r+\mu) \f$
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
A local parameter r is used to make it robust.
\f$ r=\frac{\mu}{10.0^{-120}+\tau-1.0} \f$
\ingroup PDF
\param x
\param mu
\param tau
\return Log of NegativeBinomial density. \f$ \frac{\Gamma(x+r)}{\Gamma(r)x!}(\frac{r}{r+\mu})^r(\frac{\mu}{r+\mu})^x \f$
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
  \return Log of Poisson density. \f$-\mu+k*\log(\mu)-k!\f$.
  */
  dvariable log_density_poisson(double x,const prevariable& mu)
  {
    return -mu+x*log(mu)-gammln(x+1);
  }
