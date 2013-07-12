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
#include <fvar.hpp>

/**
 * Description not yet available.
 * \param
 */
ivector histogram(double min, double max, int nbin, const dvector& v)
{
  ivector tmp(1,nbin);
  int mmin=v.indexmin();
  int mmax=v.indexmax();
  tmp.initialize();
  double delta=double(max-min)/nbin;
  for (int i=mmin;i<=mmax;i++)
  {
    int j= int((v(i)-min)/delta)+1;
    if (j<1) j=1;
    if (j>nbin) j=nbin;
    tmp(j)+=1;
  }
  return tmp;
}
