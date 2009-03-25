/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#include <df1b2fun.h>

df1b2variable inv_cumd_exponential(const df1b2variable& y)
{
  if (value(y)<=0.5)
    return log(2.0*y);
  else
    return log(2.0*(1-y));
}


df1b2variable cumd_exponential(const df1b2variable& x)
{
  if (value(x)<=0.0)
    return 0.5*exp(x);
  else
    return 1.0-0.5*exp(-x);
}

