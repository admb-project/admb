/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */

#include <df1b2fun.h>

df1b2vector lower_triangular_solve_trans(const df1b2matrix& M,
  const df1b2vector& y)
{
  int mmin=M.indexmin();
  int mmax=M.indexmax();

  if (y.indexmin() !=mmin || y.indexmax() !=mmax)
  {
    cerr << "incompatible size in solve_trans" << endl;
    ad_exit(1);
  }
  df1b2vector x(mmin,mmax);
  int i,j;

  for (i=mmax;i>=mmin;i--)
  {
    df1b2variable ssum=0.0;
    int jmax=mmax;
    for (j=i+1;j<=jmax;j++)
    {
      ssum+=M(j,i)*x(j);
    }
    x(i)=(y(i)-ssum)/M(i,i);
  }
  return x;
}


df1b2vector lower_triangular_solve(const df1b2matrix& m,const df1b2vector& v)
{
  int imin=m.indexmin();
  int imax=m.indexmax();
  if (v.indexmin() != imin || v.indexmax() != imax)
  {
    cerr << " Incompatible vector and matrix sizes in solve " << endl;
    ad_exit(1);
  }
  df1b2vector x(imin,imax);
  x(imin)=v(imin)/m(imin,imin);
  for (int i=imin+1;i<=imax;i++)
  {
    int jmin=imin;
    df1b2variable ssum=0.0;
    for (int j=jmin;j<=i-1;j++)
    {
      ssum+=m(i,j)*x(j);
    }
    x(i)=(v(i)-ssum)/m(i,i);
  }
  return x;
}
df1b2variable lower_triangular_ln_det(const df1b2matrix& m)
{
  int sgn;
  return lower_triangular_ln_det(m,sgn);
}

df1b2variable lower_triangular_ln_det(const df1b2matrix& m,int& sgn)
{
  sgn=1;
  int imin=m.indexmin();
  int imax=m.indexmax();
  df1b2variable ssum=0.0;
  for (int i=imin;i<=imax;i++)
  {
    if (value(m(i,i))>0.0)
    {
      ssum+=log(m(i,i));
    }
    else
    {
      sgn=-sgn;
      ssum+=log(-m(i,i));
    }
  }
  return ssum;
}

