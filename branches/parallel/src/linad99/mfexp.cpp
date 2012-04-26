/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
/**
  \file
  Robust exponential functions for variable scalar objects.
 */
#include <fvar.hpp>

/**
  Robust exponential function for arguments > 60 or < -60.
  Prevents overflow and underflow for arguments outside of the domain
  of exp().
  \param x dvariable exponent.
  \return \f$e^x\f$
  \ingroup misc
 */
  dvariable mfexp(_CONST prevariable& x)
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
  Robust exponential function.
  Prevents overflow and underflow for arguments outside of the domain
  \param x dvariable exponent.
  \param b double user specified function domain bound.
  \return \f$e^x\f$
  \ingroup misc
 */
  dvariable mfexp(_CONST prevariable& x,double b)
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
