/**
@file
@author David Fournier
@copyright Copyright (c) 2008-2020 Regents of the University of California

@brief Function beta_deviate.
*/
#include <fvar.hpp>

/**
 * Description not yet available.
 * \param
 */
double beta_deviate(double a,double b,double x,double eps)
{
  double y=cumd_norm(x);
  y=.9999999*y+.00000005;
  double z=inv_cumd_beta_stable(a,b,y,eps);
  return z;
}
