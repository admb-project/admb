/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
/**
  \file
  Robust exponential functions for variable scalar objects.
 */
#include <fvar.hpp>

/**
  Robust exponential function for variable argument > 60 or < -60.
  Prevents overflow and underflow for arguments outside of the domain
  of exp().
  (Note: \f$e^{60} > 10^{26}\f$.)
  \param x dvariable exponent.
  \return \f$\left\{\begin{array} {r@{\quad:\quad}l}
                    x > 60 & e^{60}\frac{(1+2(x-60))}{1+x-60}\\
                    x < 60 & e^{-60}\frac{(1-x-60)}{1+2(-x-60)}\\
               {\rm else} & e^x
                    \end{array}\right.\f$ 
  \ingroup misc
 */
dvariable mfexp(const prevariable& x)
  {
    double b=60;
    if (x<=b && x>=-b)
    {
      return exp(x);
    }
    else if (x>b)
    {
      return exp(b)*(1.+2.*(x-b))/(1.+x-b);
    }
    else
    {
      return exp(-b)*(1.-x-b)/(1.+2.*(-x-b));
    }
  }

/**
  Robust exponential function for variable argument with user 
  specified domain bound.
  Prevents overflow and underflow for arguments outside of the domain
  \param x dvariable exponent.
  \param b double user specified function domain bound.
  \return \f$\left\{\begin{array} {r@{\quad:\quad}l}
                    x > b & e^b\frac{(1+2(x-b))}{1+x-b}\\
                    x < b & e^{-b}\frac{(1-x-b)}{1+2(-x-b)}\\
               {\rm else} & e^x
                    \end{array}\right.\f$ 
  \ingroup misc
 */
dvariable mfexp(const prevariable& x, double b)
  {
    if (x<=b && x>=-b)
    {
      return exp(x);
    }
    else if (x>b)
    {
      return exp(b)*(1.+2.*(x-b))/(1.+x-b);
    }
    else
    {
      return exp(-b)*(1.-x-b)/(1.+2.*(-x-b));
    }
  }
