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
#include "fvar.hpp"

/**
 * Description not yet available.
 * \param
 */
dvector mfexp(_CONST dvector& v1)
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
 * Description not yet available.
 * \param
 */
dvector mfexp(_CONST dvector& v1, CGNU_DOUBLE d)
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
