/**
@file
@author David Fournier
@copyright Copyright (c) 2008-2020 Regents of the University of California

@brief Function norm_to_gamma(const prevariable&, const prevariable&, double)
*/

#include <fvar.hpp>

/**
 * Description not yet available.
 * \param
 */
dvariable norm_to_gamma(const prevariable & v,const prevariable& alpha,
  double bound)
{
  dvariable z=bounded_cumd_norm(v,bound);
  return inv_cumd_gamma(z,alpha);
}
