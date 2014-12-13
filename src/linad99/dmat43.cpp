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
banded_lower_triangular_dmatrix::
  banded_lower_triangular_dmatrix(const banded_lower_triangular_dmatrix& mm) :
  bw(mm.bw), d(mm.d)
{}

/**
 * Description not yet available.
 * \param
 */
banded_lower_triangular_dmatrix & banded_lower_triangular_dmatrix::operator =
  (const banded_lower_triangular_dmatrix& mm)
{
  if (mm.bw!=bw)
  {
    cerr << "shape error" << endl;
    ad_exit(1);
  }
  else
  {
    for (int i=0;i<=bw-1;i++)
    {
      d(i)=mm.d(i);
    }
  }
  return *this;
}

/**
 * Description not yet available.
 * \param
 */
banded_lower_triangular_dmatrix choleski_decomp_trust_bound(
  const banded_symmetric_dmatrix& _M,const int& _ierr)
{
  int & ierr = (int &) _ierr;
  ADUNCONST(banded_symmetric_dmatrix,M)
  int minsave=M.indexmin();
  M.shift(1);
  int n=M.indexmax();

  double delta=0.0;
  int bw=M.bandwidth();
  banded_lower_triangular_dmatrix L(1,n,bw);
#ifndef SAFE_INITIALIZE
    L.initialize();
#endif

  int i;
  double tmp;
    if (M(1,1)<=0)
    {
      if (ierr==0)
        cerr << "Error matrix not positive definite in choleski_decomp"
          <<endl;
      ierr=1;
      return L;
    }
  L(1,1)=sqrt(M(1,1));
  for (i=2;i<=bw;i++)
  {
    L(i,1)=M(i,1)/L(1,1);
  }

  for (i=2;i<=n;i++)
  {
    for (int j=i-bw+1;j<=i-1;j++)
    {
      if (j>1)
      {
        tmp=M(i,j);
        for (int k=i-bw+1;k<=j-1;k++)
        {
          if (k>0 && k>j-bw)
            tmp-=L(i,k)*L(j,k);
        }
        L(i,j)=tmp/L(j,j);
      }
    }
    tmp=M(i,i);
    for (int k=i-bw+1;k<=i-1;k++)
    {
      if (k>0)
        tmp-=L(i,k)*L(i,k);
    }
    if (tmp<=0)
    {
      delta=-tmp;
      ierr=1;
      break;
    }
    L(i,i)=sqrt(tmp);
    if (i==n)
    {
      ierr=0;
    }
  }
  dvector v(1,n);
  if (ierr==1)
  {
    int k=i;
    v.initialize();
    v(k)=1.0;
    for (i=k-1;i>=1;i--)
    {
      double ssum=0.0;
      int jmax=admin(n,i+bw-1);
      for (int j=i+1;j<=jmax;j++)
      {
        ssum+=L(j,i)*v(j);
      }
      v(i)=-ssum/L(i,i);
    }
    L(1,1)=delta/norm2(v);
  }

  M.shift(minsave);
  L.shift(minsave);

  return L;
}
//***********************************************************
//***********************************************************
/*
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
*/
//***********************************************************
//***********************************************************
//***********************************************************

