/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */

#include "fvar.hpp"
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

