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
 */
dvector mfexp(const dvector& v1)
{
  int mmin=v1.indexmin();
  int mmax=v1.indexmax();
  dvector vtmp(mmin,mmax);
  for (int i=mmin;i<=mmax;i++)
  {
    if (v1.elem(i)<60.)
    {
      vtmp.elem(i)=exp(v1.elem(i));
    }
    else
    {
      double x=v1.elem(i)-60.;
      vtmp.elem(i)=exp(60.)*(1.+2.*x)/(1.+x);
    }
  }
  return vtmp;
}

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
  for (int i=mmin;i<=mmax;i++)
  {
    if (v1.elem(i)<d)
    {
      vtmp.elem(i)=exp(v1.elem(i));
    }
    else
    {
      double x=v1.elem(i)-d;
      vtmp.elem(i)=exp(d)*(1.+2.*x)/(1.+x);
    }
  }
  return vtmp;
}
