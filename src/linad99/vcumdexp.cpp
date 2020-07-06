/**
@file
@author David Fournier
@copyright Copyright (c) 2008-2020 Regents of the University of California

@brief Functions inv_cumd_exponential(const prevariable&) and cumd_exponential(const prevariable&)
*/

#include <fvar.hpp>

/**
 * Description not yet available.
 * \param
 */
dvariable inv_cumd_exponential(const prevariable& y)
{
  if (y<=0.5)
    return log(2.0*y);
  else
    return log(2.0*(1-y));
}

/**
 * Description not yet available.
 * \param
 */
dvariable cumd_exponential(const prevariable& x)
{
  if (x<=0.0)
    return 0.5*exp(x);
  else
    return 1.0-0.5*exp(-x);
}
