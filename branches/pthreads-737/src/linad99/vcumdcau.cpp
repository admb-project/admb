/*
 * $Id: vcumdcau.cpp 542 2012-07-10 21:04:06Z johnoel $
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
dvariable cumd_cauchy(const prevariable& x)
{
  dvariable t;
  const double r2=sqrt(2.0);
  t=atan(x/r2);
  return (0.5 + t/PI);
}

/**
 * Description not yet available.
 * \param
 */
dvariable kludge_cumd_cauchy(const prevariable& x)
{
  const double r2=sqrt(2.0);
  dvariable t=atan(x/r2);
  return (0.5 + t/PI);
}

/**
 * Description not yet available.
 * \param
 */
dvariable inv_cumd_cauchy(const prevariable& x)
{
  const double r2=sqrt(2.0);
  return (r2*tan(PI*(x-0.5)));
}
