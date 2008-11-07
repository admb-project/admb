/**
  * $Id:   $
  *
  * $Rev   ::                       $: Revision of last commit
  * $Author::                       $: Author of last commit
  * $Date  ::                       $: Date of last commit
  *
  * Author: David Fournier
  * Copyright (c) 2008 Regents of the University of California 
  */
#include <fvar.hpp>

double inv_cumd_exponential(double y)
{
  if (y<=0.5)
    return log(2.0*y);
  else
    return log(2.0*(1-y));
}


double cumd_exponential(double x)
{
  if (x<=0.0)
    return 0.5*exp(x);
  else
    return 1.0-0.5*exp(-x);
}

