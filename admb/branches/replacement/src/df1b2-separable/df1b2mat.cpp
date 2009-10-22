/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#define HOME_VERSION
#include <df1b2fun.h>



df1b2matrix choleski_decomp(const df1b2matrix& MM)
{
  // kludge to deal with constantness
  df1b2matrix & M= * (df1b2matrix *) &MM;
  int rmin=M.indexmin();
  int cmin=M(rmin).indexmin();
  int rmax=M.indexmax();
  int cmax=M(rmin).indexmax();
 
  if (rmin != cmin )
  {
    cerr << "minimum row and column inidices must equal 1 in "
      "df1b2matrix choleski_decomp(const df1b2matrix& MM)"
         << endl;
    ad_exit(1);
  }
  if (rmax !=cmax)
  {
    cerr << "Error in df1b2matrix choleski_decomp(const df1b2matrix& MM)"
      " Matrix not square" << endl;
    ad_exit(1);
  }
 

  int n=rmax;
  df1b2matrix L(rmin,rmax,rmin,rmax);
#ifndef SAFE_INITIALIZE
    L.initialize();
#endif

  int i,j,k;
  df1b2variable tmp;
    if (value(M(rmin,rmin))<=0)
    {
      cerr << "Error matrix not positive definite in choleski_decomp"
        <<endl;
      ad_exit(1);
    }

  L(rmin,rmin)=sqrt(M(rmin,rmin));
  for (i=rmin+1;i<=rmax;i++)
  {
    L(i,rmin)=M(i,rmin)/L(rmin,rmin);
  }

  for (i=rmin+1;i<=rmax;i++)
  {
    for (j=rmin+1;j<=i-1;j++)
    {
      tmp=M(i,j);
      for (k=rmin;k<=j-1;k++)
      {
        tmp-=L(i,k)*L(j,k);
      }
      L(i,j)=tmp/L(j,j);
    }
    tmp=M(i,i);
    for (k=rmin;k<=i-1;k++)
    {
      tmp-=L(i,k)*L(i,k);
    }
    if (value(tmp)<=0)
    {
      cerr << "Error matrix not positive definite in choleski_decomp"
        <<endl;
      ad_exit(1);
    }
    L(i,i)=sqrt(tmp);
  }
  return L;
}

#undef HOME_VERSION
