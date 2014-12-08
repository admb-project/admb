/*
  $Id$

  Author: David Fournier
  Copyright (c) 2008-2012 Regents of the University of California
 */
/**
  \file
  Functions for gamma probability density; constant objects.
 */

//double get_values(double x,double y,int print_switch);
#include "fvar.hpp"

/**
\ingroup PDF
Gamma probability density function; constant objects.
Mean \f$ = \frac{r}{\mu} \f$.
\param x Argument, \f$ x \ge 0 \f$.
\param r Shape parameter, \f$ r > 0 \f$.
\param mu Slope parameter, \f$ \mu > 0 \f$.
\returns \f$\frac{\mu^r}{\Gamma(r)}x^{r-1}e^{-\mu x}\f$
*/
double gamma_density(double x,double r, double mu)
{
  return exp(r*log(mu) + (r-1)*log(x)-mu*x-gammln(r));
}

/**
\ingroup PDF
Log gamma probability density function; constant objects.
Mean \f$ = \frac{r}{\mu} \f$.
\param x Argument, \f$ x \ge 0 \f$.
\param r Shape parameter, \f$ r > 0 \f$.
\param mu Slope parameter, \f$ \mu > 0 \f$.
\returns \f$r\log{\mu} + (r-1)\log{x}-\mu x-\log{\Gamma(r)}\f$
*/
double log_gamma_density(double x,double r, double mu)
{
  return r*log(mu) + (r-1)*log(x)-mu*x-gammln(r);
}
