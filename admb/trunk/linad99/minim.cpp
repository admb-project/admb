/**
  * $Id$
  *
  * $Rev   ::                       $: Revision of last commit
  * $Author::                       $: Author of last commit
  * $Date  ::                       $: Date of last commit
  *
  * Author: David Fournier
  * Copyright (c) 2008 Regents of the University of California 
  */
#define HOME_VERSION
#include <fvar.hpp>

double fmm::minimize(BOR_CONST independent_variables & x,double (*pf)(_CONST dvar_vector&))
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
#undef HOME_VERSION
