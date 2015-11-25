/*
\file Robust exponential functions for constant scalar objects.

Author: David Fournier
Copyright (c) 2008-2015 Regents of the University of California
*/
#include <fvar.hpp>

/**
Robust exponential function for constant argument with user
specified domain bound.
Prevents overflow and underflow for arguments outside of the domain
\param x exponent.
\param b ouble user specified function domain bound.
\return \f$\left\{\begin{array} {r@{\quad:\quad}l}
                    x > b & e^b\frac{(1+2(x-b))}{1+x-b}\\
                    x < b & e^{-b}\frac{(1-x-b)}{1+2(-x-b)}\\
               {\rm else} & e^x
                    \end{array}\right.\f$
\ingroup misc
*/
double mfexp(double x, double b)
{
  if (x > b)
  {
    return exp(b)*(1.+2.*(x-b))/(1.+x-b);
  }
  else if (x < -b)
  {
    return exp(-b)*(1.-x-b)/(1.+2.*(-x-b));
  }
  return exp(x);
}
/**
Robust exponential function for constant argument > 60 or < -60.
Prevents overflow and underflow for arguments outside of the domain
of exp().
(Note: \f$e^{60} > 10^{26}\f$.)
\param x exponent.
\return \f$\left\{\begin{array} {r@{\quad:\quad}l}
                    x > 60 & e^{60}\frac{(1+2(x-60))}{1+x-60}\\
                    x < 60 & e^{-60}\frac{(1-x-60)}{1+2(-x-60)}\\
               {\rm else} & e^x
                    \end{array}\right.\f$
\ingroup misc
*/
double mfexp(double x)
{
  double b = 60;
  return mfexp(x, b);
}

