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

