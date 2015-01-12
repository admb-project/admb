/*
 * $Id$
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
dvariable cumd_cauchy(_CONST prevariable& x)
{
  dvariable t;
  const double r2=sqrt(2.0);
  t=atan(x/r2);
  return (0.5 + t/3.1415927);
}

/**
 * Description not yet available.
 * \param
 */
dvariable kludge_cumd_cauchy(_CONST prevariable& x)
{
  const double r2=sqrt(2.0);
  dvariable t=atan(x/r2);
  return (0.5 + t/3.1415927);
}

/**
 * Description not yet available.
 * \param
 */
dvariable inv_cumd_cauchy(_CONST prevariable& x)
{
  const double r2=sqrt(2.0);
  return (r2*tan(3.1415927*(x-0.5)));
}
