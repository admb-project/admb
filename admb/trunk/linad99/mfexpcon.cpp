/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */


#include <fvar.hpp>

  double mfexp(double x)
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

  double mfexp(double x,double b)
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

