/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include <fvar.hpp>
#ifndef OPT_LIB
  #include <cassert>
  #include <climits>
#endif

#ifdef __TURBOC__
  #pragma hdrstop
  #include <iostream.h>
#endif

#if defined (__WAT32__)
  #include <iostream.h>
  #include <strstrea.h>
#endif

#ifdef __ZTC__
  #include <iostream.hpp>
#endif

#define TINY 1.0e-20;

dmatrix solve(const dmatrix& aa,const dmatrix& tz,
  const double& ln_unsigned_det,double& sign);

/**
/param aa
/param tz
*/
dmatrix solve(const dmatrix& aa, const dmatrix& tz)
{
  double ln = 0;
  double sgn = 0;
  return solve(aa,tz,ln,sgn);
}

/**
/param aa
/param tz
/param ln_unsigned_det
/param sign
*/
dmatrix solve(const dmatrix& aa,const dmatrix& tz,
  const double& _ln_unsigned_det,double& sign)
{
  double& ln_unsigned_det = (double&)_ln_unsigned_det;
#if !defined(OPT_LIB) && (__cplusplus >= 201103L)
  int n = [](unsigned int colsize) -> int
  {
    assert(colsize <= INT_MAX);
    return static_cast<int>(colsize);
  } (aa.colsize());
#else
  int n = static_cast<int>(aa.colsize());
#endif
  int lb=aa.colmin();
  int ub=aa.colmax();
  if (lb!=aa.rowmin()||ub!=aa.colmax())
  {
    cerr << "Error matrix not square in solve()"<<endl;
    ad_exit(1);
  }
  dmatrix bb(lb,ub,lb,ub);
  bb=aa;
  ivector indx(lb,ub);
  int One=1;
  indx.fill_seqadd(lb,One);
  dvector vv(lb,ub);

  double d = 1.0;
  for (int i=lb;i<=ub;i++)
  {
    double big=0.0;
    for (int j=lb;j<=ub;j++)
    {
      double temp=fabs(bb(i,j));
      if (temp > big)
      {
        big=temp;
      }
    }
    if (big == 0.0)
    {
      cerr << "Error in matrix inverse -- matrix singular in inv(dmatrix)\n";
    }
    vv[i]=1.0/big;
  }

  for (int j=lb;j<=ub;j++)
  {
    for (int i=lb;i<j;i++)
    {
      double sum=bb(i,j);
      for (int k=lb;k<i;k++)
      {
        sum -= bb(i,k)*bb(k,j);
      }
      //a[i][j]=sum;
      bb(i,j)=sum;
    }
    int imax = j;
    double big=0.0;
    for (int i=j;i<=ub;i++)
    {
      double sum=bb(i,j);
      for (int k=lb;k<j;k++)
      {
        sum -= bb(i,k)*bb(k,j);
      }
      bb(i,j)=sum;
      double dum=vv[i]*fabs(sum);
      if (dum >= big)
      {
        big=dum;
        imax=i;
      }
    }
    if (j != imax)
    {
      for (int k=lb;k<=ub;k++)
      {
        double dum=bb(imax,k);
        bb(imax,k)=bb(j,k);
        bb(j,k)=dum;
      }
      d = -1.*d;
      vv[imax]=vv[j];

      //if (j<ub)
      {
        int itemp=indx(imax);
        indx(imax)=indx(j);
        indx(j)=itemp;
      }
      //cout << "indx= " <<indx<<endl;
    }

    if (bb(j,j) == 0.0)
    {
      bb(j,j)=TINY;
    }

    if (j != n)
    {
      double dum=1.0/bb(j,j);
      for (int i=j+1;i<=ub;i++)
      {
        bb(i,j) = bb(i,j) * dum;
      }
    }
  }

  // get the determinant
  sign=d;
  dvector part_prod(lb,ub);
  part_prod(lb)=log(fabs(bb(lb,lb)));
  if (bb(lb,lb)<0) sign=-sign;
  for (int j=lb+1;j<=ub;j++)
  {
    if (bb(j,j)<0) sign=-sign;
    part_prod(j)=part_prod(j-1)+log(fabs(bb(j,j)));
  }
  ln_unsigned_det=part_prod(ub);

  dmatrix z=trans(tz);
  int mmin=z.indexmin();
  int mmax=z.indexmax();
  dmatrix x(mmin,mmax,lb,ub);
  //dvector x(lb,ub);

  dvector y(lb,ub);
  //int lb=rowmin;
  //int ub=rowmax;
  dmatrix& b=bb;
  ivector indxinv(lb,ub);
  for (int i=lb;i<=ub;i++)
  {
    indxinv(indx(i))=i;
  }
  for (int kk=mmin;kk<=mmax;kk++)
  {
    for (int i=lb;i<=ub;i++)
    {
      y(indxinv(i))=z(kk)(i);
    }

    for (int i=lb;i<=ub;i++)
    {
      double sum=y(i);
      for (int j=lb;j<=i-1;j++)
      {
        sum-=b(i,j)*y(j);
      }
      y(i)=sum;
    }
    for (int i=ub;i>=lb;i--)
    {
      double sum=y(i);
      for (int j=i+1;j<=ub;j++)
      {
        sum-=b(i,j)*x(kk)(j);
      }
      x(kk)(i)=sum/b(i,i);
    }
  }
  return trans(x);
}

/**
\todo Need test
*/
double ln_det_choleski(
  const banded_symmetric_dmatrix& MM,
  int& ierr)
{
  banded_lower_triangular_dmatrix tmp = choleski_decomp(MM, ierr);

  int mmin=tmp.indexmin();
  int mmax=tmp.indexmax();
  double ld=0.0;
  for (int i=mmin;i<=mmax;i++)
  {
    ld+=log(tmp(i,i));
  }
  return 2.0*ld;
}

double norm(const banded_symmetric_dmatrix& B)
{
  return sqrt(norm2(B));
}

double norm2(const banded_symmetric_dmatrix& B)
{
  double nm=0.0;
  for (int i=1;i<=B.bw-1;i++)
  {
    nm+=norm2(B.d(i));
  }
  nm*=2;
  nm+=norm2(B.d(0));
  return nm;
}

#undef TINY

