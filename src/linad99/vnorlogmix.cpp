/**
@file
@author David Fournier
@copyright Copyright (c) 2008-2020 Regents of the University of California

@brief Functions robust_normal_logistic_mixture_deviate(const prevariable&, double) and robust_normal_mixture_deviate(const prevariable&, double)
*/

#include <fvar.hpp>

/**
 * Description not yet available.
 * \param
 */
dvariable robust_normal_logistic_mixture_deviate(const prevariable& x,
  double spread)
{
  dvariable y=cumd_norm(x);
  y = 0.99999999*y + 0.000000005; // To gain numerical stability
  dvariable z = inv_cumd_normal_logistic_mixture(y,spread);
  return z;
}

/**
 * Description not yet available.
 * \param
 */
dvariable robust_normal_mixture_deviate(const prevariable& x,
  double spread)
{
  dvariable y=cumd_norm(x);
  y = 0.99999999*y + 0.000000005; // To gain numerical stability
  dvariable z = inv_cumd_normal_mixture(y,spread);
  return z;
}
