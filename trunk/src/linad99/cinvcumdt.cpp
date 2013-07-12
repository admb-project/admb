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
#include <admodel.h>

/**
 * Description not yet available.
 * \param
 */
double inv_cumd_t(double n,double u,double eps)
{
  double v,sgn;
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
  double w=inv_cumd_beta_stable(0.5*n,0.5,v,eps);
  return sgn*sqrt(n*(1.0/w-1.0));
}
