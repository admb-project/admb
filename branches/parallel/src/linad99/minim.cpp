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
#include <fvar.hpp>

/**
 * Description not yet available.
 * \param
 */
double fmm::minimize(const independent_variables & x, double (*pf)(const dvar_vector&))
{  
  int nvar=x.size();
  double f;
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
  return(f);
}
