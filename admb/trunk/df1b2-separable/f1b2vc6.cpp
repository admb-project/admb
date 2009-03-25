/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */

#include <df1b2fun.h>

df1b2matrix exp(const df1b2matrix& _M)
{
  ADUNCONST(df1b2matrix,M)
  int rmin=M.indexmin();
  int rmax=M.indexmax();
  df1b2matrix tmp(rmin,rmax);
  for (int i=rmin;i<=rmax;i++) 
  {
    int cmin=M(i).indexmin();
    int cmax=M(i).indexmax();
    tmp(i).noallocate(cmin,cmax);
    for (int j=cmin;j<=cmax;j++) 
      tmp(i,j)=exp(M(i,j));
  }
  return tmp;
}

df1b2vector colsum(const df1b2matrix& _M)
{
  ADUNCONST(df1b2matrix,M)
  int rmin=M.indexmin();
  int rmax=M.indexmax();
  int cmin=M(rmin).indexmin();
  int cmax=M(rmin).indexmax();
  df1b2vector tmp(cmin,cmax);
  tmp.initialize();
  for (int i=rmin;i<=rmax;i++) 
  {
    for (int j=cmin;j<=cmax;j++) 
      tmp(j)+=M(i,j);
  }
  return tmp;
}
df1b2vector rowsum(const df1b2matrix& _M)
{
  ADUNCONST(df1b2matrix,M)
  int rmin=M.indexmin();
  int rmax=M.indexmax();
  df1b2vector tmp(rmin,rmax);
  tmp.initialize();
  for (int i=rmin;i<=rmax;i++) 
  {
    int cmin=M(rmin).indexmin();
    int cmax=M(rmin).indexmax();
    for (int j=cmin;j<=cmax;j++) 
      tmp(i)+=M(i,j);
  }
  return tmp;
}
