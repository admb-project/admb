/**
@file
@author David Fournier
@copyright Copyright (c) 2008-2020 Regents of the University of California

@brief Functions cumd_cauchy(const prevariable&), kludge_cumd_cauchy(const prevariable&) and inv_cumd_cauchy(const prevariable&)
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
