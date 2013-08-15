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
dvar_vector posfun(const dvar_vector&x,double eps,const prevariable& _pen)
{
  int mmin=x.indexmin();
  int mmax=x.indexmax();
  dvar_vector tmp(mmin,mmax);
  for (int i=mmin;i<=mmax;i++)
  {
    tmp(i)=posfun(x(i),eps,_pen);
  }
  return tmp;
}
