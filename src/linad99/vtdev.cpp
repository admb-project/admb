/**
@file
@author David Fournier
@copyright Copyright (c) 2008-2020 Regents of the University of California

@brief Function t_deviate(const prevariable&,const prevariable&)
*/

#include <fvar.hpp>

/**
 * Description not yet available.
 * \param
 */
dvariable t_deviate(const prevariable& _x,const prevariable& _a)
{
  prevariable& x= (prevariable&)(_x);
  prevariable& a= (prevariable&)(_a);

  dvariable y=cumd_norm(x);

  y=.9999*y+.00005;

  dvariable z=inv_cumd_t(a,y);

  return z;
}
