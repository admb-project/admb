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
 * Description not yet available.
 * \param
 */
dmatrix operator * (const d3_array & t,const dvector& v)
{
  int mmin=t.indexmin();
  int mmax=t.indexmax();
  dmatrix tmp(mmin,mmax);
  for (int i=mmin;i<=mmax;i++)
  {
    tmp(i)=t(i)*v;
  }
  return tmp;
}
