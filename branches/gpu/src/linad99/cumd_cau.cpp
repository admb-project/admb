/*
 * $Id: cumd_cau.cpp 946 2011-01-12 23:52:45Z johnoel $
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
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
double cumd_cauchy(_CONST double& x)
{
  double t=0.0;
  const double r2=sqrt(2.0);
  t=atan(x/r2);
  return (0.5 + t/PI);
}

/**
 * Description not yet available.
 * \param
 */
double density_cauchy(_CONST double& x)
{
  const double r2=PI*sqrt(2.0);
  return 1./(r2*(1+0.5*x*x)); 
}

/**
 * Description not yet available.
 * \param
 */
double log_density_cauchy(_CONST double& x)
{
  const double r2=PI*sqrt(2.0);
  return -log(r2*(1+0.5*x*x)); 
}

/**
 * Description not yet available.
 * \param
 */
double inv_cumd_cauchy(_CONST double& x)
{
  const double r2=sqrt(2.0);
  return (r2*tan(PI*(x-0.5)));
}
