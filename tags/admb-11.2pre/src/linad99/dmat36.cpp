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
lower_triangular_dmatrix::lower_triangular_dmatrix(int min,int max):
  dmatrix(min,max)
{
  for (int i=min;i<=max;i++)
  {
    (*this)(i).allocate(min,i);
  }
}

/**
 * Description not yet available.
 * \param
 */
dvector solve(const lower_triangular_dmatrix& m,const dvector&v)
{
  int imin=m.indexmin();
  int imax=m.indexmax();
  if (v.indexmin() != imin || v.indexmax() != imax)
  {
    cerr << " Incompatible vector and matrix sizes in solve " << endl;
    ad_exit(1);
  }
  dvector x(imin,imax);
  x(imin)=v(imin)/m(imin,imin);
  for (int i=2;i<=imax;i++)
  {
    int jmin=imin;
    double ssum=0.0;
    for (int j=jmin;j<=i-1;j++)
    {
      ssum+=m(i,j)*x(j);
    }
    x(i)=(v(i)-ssum)/m(i,i);
  }
  return x;
}

/**
 * Description not yet available.
 * \param
 */
dmatrix symmetrize(const lower_triangular_dmatrix & T)
{
  int min=T.indexmin();
  int max=T.indexmax();
  dmatrix tmp(min,max,min,max);
  int i,j;
  for (i=min;i<=max;i++)
  {
    tmp(i,i)=T(i,i);
    for (j=i+1;j<=max;j++)
    {
      tmp(i,j)=T(j,i);
      tmp(j,i)=T(j,i);
    }
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvector solve_trans(const lower_triangular_dmatrix& M,const dvector& y)
{
  int mmin=M.indexmin();
  int mmax=M.indexmax();

  if (y.indexmin() !=mmin || y.indexmax() !=mmax)
  {
    cerr << "incompatible size in solve_trans" << endl;
    ad_exit(1);
  }
  dvector x(mmin,mmax);
  int i,j;

  for (i=mmax;i>=mmin;i--)
  {
    double sum=0.0;
    for (j=i+1;j<=mmax;j++)
    {
      sum+=M(j,i)*x(j);
    }
    x(i)=(y(i)-sum)/M(i,i);
  }

  return x;
}

/**
 * Description not yet available.
 * \param
 */
dmatrix fillout(const lower_triangular_dmatrix& M)
{
  int mmin=M.indexmin();
  int mmax=M.indexmax();
  int i,j;
  dmatrix tmp(mmin,mmax,mmin,mmax);
  for (i=mmin;i<=mmax;i++)
  {
    for (j=1;j<i;j++)
      tmp(j,i)=0;
    for (j=i;j<=mmax;j++)
      tmp(j,i)=M(j,i);
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dmatrix fillout_trans(const lower_triangular_dmatrix& M)
{
  int mmin=M.indexmin();
  int mmax=M.indexmax();
  int i,j;
  dmatrix tmp(mmin,mmax,mmin,mmax);
  for (i=mmin;i<=mmax;i++)
  {
    for (j=1;j<i;j++)
      tmp(i,j)=0;
    for (j=i;j<=mmax;j++)
      tmp(i,j)=M(j,i);
  }
  return tmp;
}
