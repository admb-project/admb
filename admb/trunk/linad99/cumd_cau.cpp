/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */

#include <fvar.hpp>

double cumd_cauchy(_CONST double& x)
{
  double t=0.0;
  const double r2=sqrt(2.0);
  t=atan(x/r2);
  return (0.5 + t/3.1415927);
}

double density_cauchy(_CONST double& x)
{
  const double r2=3.1415927*sqrt(2.0);
  return 1./(r2*(1+0.5*x*x)); 
}

double log_density_cauchy(_CONST double& x)
{
  const double r2=3.1415927*sqrt(2.0);
  return -log(r2*(1+0.5*x*x)); 
}

double inv_cumd_cauchy(_CONST double& x)
{
  const double r2=sqrt(2.0);
  return (r2*tan(3.1415927*(x-0.5)));
}
