/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
/**
  \file minim.pp
  Minimize artibrary user-supplied function.
 */
#include <fvar.hpp>
#ifdef DEBUG
  #include <cassert>
#endif

/**
  Minimize artibrary user-supplied function.
  \param x Vector of independent variables
  \param pf Pointer to function to be minmized with prototype
  double pf(const dvar_vector&);
  \returns double containing value of the function at the minimum.
 */
double fmm::minimize(const independent_variables & x,
  double (*pf)(const dvar_vector&))
{
  double f = 0.0;

  int nvar = static_cast<int>(x.size());
#ifdef DEBUG
  assert(nvar > 0);
#endif
  dvector g(1,nvar);
#ifndef SAFE_INITIALIZE
  g.initialize();
#endif
  {
    gradient_structure gs;
    while (ireturn >= 0)
    {
      fmin(f,x,g);
      if(ireturn > 0)
      {
        {
          f=(*pf)(x);
        }
        gradcalc(nvar,g);
      }
    }
  }
  return f;
}
