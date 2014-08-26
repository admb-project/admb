/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include <fvar.hpp>

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
  int i,j,k,n;
  n=aa.colsize();
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
  double d;
  double big,dum,sum,temp;
  dvector vv(lb,ub);

  d=1.0;
  for (i=lb;i<=ub;i++)
  {
    big=0.0;
    for (j=lb;j<=ub;j++)
    {
      temp=fabs(bb(i,j));
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

  for (j=lb;j<=ub;j++)
  {
    for (i=lb;i<j;i++)
    {
      sum=bb(i,j);
      for (k=lb;k<i;k++)
      {
        sum -= bb(i,k)*bb(k,j);
      }
      //a[i][j]=sum;
      bb(i,j)=sum;
    }
    int imax = j;
    big=0.0;
    for (i=j;i<=ub;i++)
    {
      sum=bb(i,j);
      for (k=lb;k<j;k++)
      {
        sum -= bb(i,k)*bb(k,j);
      }
      bb(i,j)=sum;
      dum=vv[i]*fabs(sum);
      if ( dum >= big)
      {
        big=dum;
        imax=i;
      }
    }
    if (j != imax)
    {
      for (k=lb;k<=ub;k++)
      {
        dum=bb(imax,k);
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
      dum=1.0/bb(j,j);
      for (i=j+1;i<=ub;i++)
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
  for (j=lb+1;j<=ub;j++)
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
  for (i=lb;i<=ub;i++)
  {
    indxinv(indx(i))=i;
  }
  for (int kk=mmin;kk<=mmax;kk++)
  {
    for (i=lb;i<=ub;i++)
    {
      y(indxinv(i))=z(kk)(i);
    }

    for (i=lb;i<=ub;i++)
    {
      sum=y(i);
      for (int j=lb;j<=i-1;j++)
      {
        sum-=b(i,j)*y(j);
      }
      y(i)=sum;
    }
    for (i=ub;i>=lb;i--)
    {
      sum=y(i);
      for (int j=i+1;j<=ub;j++)
      {
        sum-=b(i,j)*x(kk)(j);
      }
      x(kk)(i)=sum/b(i,i);
    }
  }
  return trans(x);
}

double ln_det_choleski(
  const banded_symmetric_dmatrix& MM, const int& _ierr)
{
  banded_lower_triangular_dmatrix tmp=choleski_decomp(MM,_ierr);

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

