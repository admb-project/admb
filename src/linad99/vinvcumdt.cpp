/**
@file
@author David Fournier
@copyright Copyright (c) 2008-2020 Regents of the University of California

@brief Function inv_cumd_t(const prevariable&, const prevariable&, double)
*/

#include <admodel.h>

/**
 * Description not yet available.
 * \param
 */
dvariable inv_cumd_t(const prevariable& n,const prevariable&  u,double eps)
{
  double sgn;
  dvariable v;
  if (u<0.5)
  {
    v=2.0*u;
    sgn=-1.0;
  }
  else
  {
    v=2.0*(1.0-u);
    sgn=1.0;
  }
  dvariable pfive=0.5;
  dvariable w=inv_cumd_beta_stable(0.5*n,pfive,v,eps);
  return sgn*sqrt(n*(1.0/w-1.0));
}
