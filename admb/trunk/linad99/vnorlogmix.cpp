/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#include <fvar.hpp>

dvariable robust_normal_logistic_mixture_deviate(const prevariable& x,
  double spread)
{

  dvariable y=cumd_norm(x);
  y = 0.99999999*y + 0.000000005; // To gain numerical stability
  dvariable z = inv_cumd_normal_logistic_mixture(y,spread);
  return z;
}

dvariable robust_normal_mixture_deviate(const prevariable& x,
  double spread)
{
  dvariable y=cumd_norm(x);
  y = 0.99999999*y + 0.000000005; // To gain numerical stability
  dvariable z = inv_cumd_normal_mixture(y,spread);
  return z;
}

