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
#include <df1b2fun.h>

/**
 * Description not yet available.
 * \param
 */
df1b2vector column(const df1b2matrix& _M,int n)
{
  ADUNCONST(df1b2matrix,M)
  int mmin=M.indexmin();
  int mmax=M.indexmax();
  if (n<M(mmin).indexmin() || n>M(mmin).indexmax())
  {
    cerr << "Index out of range in "
        " df1b2vector column(const df1b2matrix& M,int n) "
      << endl;
    ad_exit(1);
  }
  df1b2vector tmp(mmin,mmax);
  for (int i=mmin;i<=mmax;i++)
  {
    tmp(i)=M(i,n);
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
 df1b2matrix trans(_CONST df1b2matrix& _m1)
 {
   ADUNCONST(df1b2matrix,m1)
   int rmin=m1.indexmin();
   int rmax=m1.indexmax();
   int cmin=m1(rmin).indexmin();
   int cmax=m1(rmin).indexmax();
   df1b2matrix tmp(cmin,cmax,rmin,rmax);

   for (int i=rmin; i<=rmax; i++)
   {
     for (int j=cmin; j<=cmax; j++)
     {
       tmp(j,i)=m1(i,j);
     }
   }
   return (tmp);
 }
