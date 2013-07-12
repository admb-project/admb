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
#include <df1b2fun.h>

/**
 * Description not yet available.
 * \param
 */
df1b2variable inv_cumd_t(const df1b2variable& n,const df1b2variable&  u,
  double eps)
{
  double sgn;
  df1b2variable v;
  if (value(u)<0.5)
  {
    v=2.0*u;
    sgn=-1.0;
  }
  else
  {
    v=2.0*(1.0-u);
    sgn=1.0;
  }
  df1b2variable pfive=0.5;
  df1b2variable w=inv_cumd_beta_stable(0.5*n,pfive,v,eps);
  return sgn*sqrt(n*(1.0/w-1.0));
}
