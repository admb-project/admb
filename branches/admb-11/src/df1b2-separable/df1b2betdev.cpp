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
#include "df1b2fun.h"

/**
 * Description not yet available.
 * \param
 */
df1b2variable beta_deviate(const df1b2variable& _a,const df1b2variable& _b,
  const df1b2variable& _x,double eps)
{
  df1b2variable& x= (df1b2variable&)(_x);
  df1b2variable& a= (df1b2variable&)(_a);
  df1b2variable& b= (df1b2variable&)(_b);

  df1b2variable y=cumd_norm(x);
  y=.9999999*y+.00000005;

  df1b2variable z=inv_cumd_beta_stable(a,b,y,eps);

  return z;
}
