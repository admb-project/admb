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
#include <df1b2fun.h>

/**
 * Description not yet available.
 * \param
 */
df1b2variable robust_normal_logistic_mixture_deviate(const df1b2variable& x,
  double spread)
{

  df1b2variable y=cumd_norm(x);
  y = 0.99999999*y + 0.000000005; // To gain numerical stability
  df1b2variable z = inv_cumd_normal_logistic_mixture(y,spread);
  return z;
}

/**
 * Description not yet available.
 * \param
 */
df1b2variable robust_normal_mixture_deviate(const df1b2variable& x,
  double spread)
{
  df1b2variable y=cumd_norm(x);
  y = 0.99999999*y + 0.000000005; // To gain numerical stability
  df1b2variable z = inv_cumd_normal_mixture(y,spread);
  return z;
}
