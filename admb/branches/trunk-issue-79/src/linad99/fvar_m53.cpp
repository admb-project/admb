/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#include "fvar.hpp"


dvar_vector lower_triangular_solve(const dvar_matrix& m,const dvar_vector&v)
{
  int imin=m.indexmin();
  int imax=m.indexmax();
  if (v.indexmin() != imin || v.indexmax() != imax)
  {
    cerr << " Incompatible vector and matrix sizes in solve " << endl;
    ad_exit(1);
  }
  dvar_vector x(imin,imax);
  x(imin)=v(imin)/m(imin,imin);
  for (int i=2;i<=imax;i++)
  {
    int jmin=imin;
    dvariable ssum=0.0;
    for (int j=jmin;j<=i-1;j++)
    {
      ssum+=m(i,j)*x(j);
    }
    x(i)=(v(i)-ssum)/m(i,i);
  }
  return x;
}



dvariable lower_triangular_ln_det(const dvar_matrix& m)
{
  int sgn;
  return lower_triangular_ln_det(m,sgn);
}

dvariable lower_triangular_ln_det(const dvar_matrix& m,int& sgn)
{
  sgn=1;
  int imin=m.indexmin();
  int imax=m.indexmax();
  dvariable ssum=0.0;
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



/*
dvar_vector lower_triangular_solve(const dvar_matrix& a, const dvar_vector & b)
{
  int i,k;
  dvariable sum;

  int mmin=b.indexmin();
  int mmax=b.indexmax();
  dvar_vector x(mmin,mmax);

  for (i=mmin;i<=mmax;i++) 
  {
    sum=b[i];
    for (k=i-1;k>=mmin;k--) 
    {
      sum -= a[i][k]*x[k];
    }
    x[i]=sum/a[i][i];
  }
  return x;
  for (i=mmax;i>=mmin;i--) 
  {
    for (sum=x[i],k=i+1;k<=mmax;k++) 
    {
      sum -= a[k][i]*x[k];
    }
    x[i]=sum/a[i][i];
  }
}
 */

