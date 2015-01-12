/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */


#include "fvar.hpp"
dvector solve(const banded_symmetric_dmatrix& _m,const dvector&_v,
  const int& _ierr)
{
  int & ierr=(int&)_ierr;
  ADUNCONST(dvector,v)
  ADUNCONST(banded_symmetric_dmatrix,m)
  int mmin=m.indexmin();
  m.shift(1);
  v.shift(1);
  const banded_lower_triangular_dmatrix& C=choleski_decomp(m,ierr);
  dvector w=solve_trans(C,solve(C,v));
  m.shift(mmin);
  w.shift(mmin);
  v.shift(mmin);
  return w;
}
dvector solve(const banded_symmetric_dmatrix& m,const dvector&v)
{
  int ierr=0;
  return solve(m,v,ierr);
}


dmatrix solve(const banded_symmetric_dmatrix& m,const dmatrix& n,
  const int& _ierr)
{
  int& ierr=(int&) _ierr;
  ierr=0;
  dmatrix tmp=trans(n);
  const banded_lower_triangular_dmatrix& C=choleski_decomp(m,ierr);
  int mmin=tmp.indexmin();
  int mmax=tmp.indexmax();
  dmatrix w(mmin,mmax);
  for (int i=mmin;i<=mmax;i++)
  {
    w(i)=solve_trans(C,solve(C,tmp(i)));
  }
  return trans(w);
}


dmatrix solve(const banded_symmetric_dmatrix& m,const dmatrix& n)
{
  int ierr=0;
  return solve(m,n,ierr);
} 


dvector solve(const banded_lower_triangular_dmatrix& m,const dvector&v)
{
  int bw=m.bandwidth();
  int imin=m.indexmin();
  int imax=m.indexmax();
  if (v.indexmin() != imin || v.indexmax() != imax)
  {
    cerr << " Incompatible vector and matrix sizes in solve " << endl;
    ad_exit(1);
  }
  dvector x(imin,imax);
  x(imin)=v(imin)/m(imin,imin);
  for (int i=imin;i<=imax;i++)
  {
    int jmin=admax(imin,i-bw+1);
    double ssum=0.0;
    for (int j=jmin;j<=i-1;j++)
    {
      ssum+=m(i,j)*x(j);
    }
    x(i)=(v(i)-ssum)/m(i,i);
  }
  return x;
}

dvector solve_trans(const banded_lower_triangular_dmatrix& M,const dvector& y)
{
  int mmin=M.indexmin();
  int mmax=M.indexmax();
  int bw=M.bandwidth();

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
    int jmax=admin(mmax,i+bw-1);
    for (j=i+1;j<=jmax;j++)
    {
      sum+=M(j,i)*x(j);
    }
    x(i)=(y(i)-sum)/M(i,i);
  }

  return x;
}

dvector lower_triangular_solve_trans(const dmatrix& M,const dvector& y)
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
    int jmax=mmax;
    for (j=i+1;j<=jmax;j++)
    {
      sum+=M(j,i)*x(j);
    }
    x(i)=(y(i)-sum)/M(i,i);
  }
  return x;
}

dvector lower_triangular_solve(const dmatrix& m,const dvector&v)
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
  for (int i=imin;i<=imax;i++)
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

dvector choleski_solve_error(dmatrix M,dvector& v,int& ierror)
{
  dmatrix C=choleski_decomp_error(M,ierror);

  if (ierror==1)
  {
    return v;
  }
  else
  {
    return lower_triangular_solve_trans(C,lower_triangular_solve(C,v));
  }
}

dvector choleski_solve_neghess_error(dmatrix M,dvector& v,int& ierror)
{
  dmatrix C=choleski_decomp_neghess_error(M,ierror);

  if (ierror==1)
  {
    return v;
  }
  else
  {
    return lower_triangular_solve_trans(C,lower_triangular_solve(C,v));
  }
}

