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
#include "fvar.hpp"


/**
 * Safe version of exp that interpolates values greater than equal to 60 in each element 
 * of a vector v1.
 * \param v1 a data vector
 * \param d macro for CGNU_DOUBLE
 */
dvector mfexp(const dvector& v1, const double d)
{
  int mmin=v1.indexmin();
  int mmax=v1.indexmax();
  dvector vtmp(mmin,mmax);
  double* pvtmpi = vtmp.get_v() + mmin;
  double* pv1i = v1.get_v() + mmin;
  for (int i=mmin;i<=mmax;i++)
  {
    if (*pv1i < d)
    {
      *pvtmpi = exp(*pv1i);
    }
    else
    {
      double x = *pv1i - d;
      *pvtmpi = exp(d) * (1.0 + 2.0 * x)/(1.0 + x);
    }
    ++pvtmpi;
    ++pv1i;
  }
  return vtmp;
}

/**
 * Safe version of exp that interpolates values greater than equal to 60 in each element 
 * of a vector v1.
 * \param v1 a data vector
 */
dvector mfexp(const dvector& v1)
{
  return mfexp(v1, 60.0);
}
