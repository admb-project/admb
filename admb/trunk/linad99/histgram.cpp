/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#include <fvar.hpp>

ivector histogram(double min,double max,int nbin,_CONST dvector& v)
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




