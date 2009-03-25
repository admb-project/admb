/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */



#include <fvar.hpp>

dvariable cumd_logistic(_CONST prevariable& x)
{
  if (value(x)>=0.0)	
  {	  
    return 1.0/(1.0+exp(-x));
  }
  else  
  {	  
    dvariable y=exp(x);	   
    return y/(1.0+y);
  }
}

dvariable inv_cumd_logistic(_CONST prevariable& x)
{
  return log(x/(1.0-x));
}
