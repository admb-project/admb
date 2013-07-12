/*
 * $Id$
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
dvariable beta_deviate(const prevariable& _a,const prevariable& _b,
  const prevariable& _x,double eps)
{
  prevariable& x= (prevariable&)(_x);
  prevariable& a= (prevariable&)(_a);
  prevariable& b= (prevariable&)(_b);

  dvariable y=cumd_norm(x);
  y=.9999999*y+.00000005;

  dvariable z=inv_cumd_beta_stable(a,b,y,eps);

  return z;
}
