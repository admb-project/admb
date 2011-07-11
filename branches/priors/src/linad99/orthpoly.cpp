/*
 * $Id: orthpoly.cpp 946 2011-01-12 23:52:45Z johnoel $
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
/**
 * \file
 * Description not yet available.
 */
#include <fvar.hpp>

/**
 * Description not yet available.
 * \param
 */
dmatrix orthpoly(int n,int deg)
{
  int j; int is; int ik;
  dmatrix ocoff(0,deg,1,n);
  double sum;
  ocoff(0)=sqrt(double(n));
  for (is=1; is<=deg; is++)
  {
    for (j=1; j<=n; j++)
    {
      ocoff(is,j)=pow(double(j),is);
    }
  }
  for (is=0; is<=deg; is++) /* L1000  */
  {
    for (ik=0; ik<=is-1; ik++) /* L2000  */
    {
      sum=ocoff(is)*ocoff(ik);
      ocoff(is)-=sum*ocoff(ik);
    }
    sum=norm2(ocoff(is));
    ocoff(is)=ocoff(is)/sqrt(sum);
  }
  return trans(ocoff);
}

/**
 * Description not yet available.
 * \param
 */
dmatrix orthpoly(int n,int deg,int skip)
{
  int j; int is; int ik;
  dmatrix ocoff(0,deg,1,n);
  double sum;
  ocoff(0)=sqrt(double(n));
  for (is=1; is<=deg; is++)
  {
    for (j=1; j<=n; j++)
    {
      ocoff(is,j)=pow(double(j),is);
    }
  }
  for (is=0; is<=deg; is++) /* L1000  */
  {
    for (ik=0; ik<=is-1; ik++) /* L2000  */
    {
      sum=ocoff(is)*ocoff(ik);
      ocoff(is)-=sum*ocoff(ik);
    }
    sum=norm2(ocoff(is));
    ocoff(is)=ocoff(is)/sqrt(sum);
  }
  return trans(ocoff.sub(skip,deg));
}

/**
 * Description not yet available.
 * \param
 */
dmatrix orthpoly_constant_begin(int n,int deg,int nconst)
{
  int j; int is; int ik;
  dmatrix ocoff(0,deg,1,n);
  double sum;
  ocoff(0)=sqrt(double(n));
  if (nconst>n-1)
  {
    cerr << "nconst too large in orthpoly_constant_begin"
         << endl;
  }
  if (deg>n-nconst)
  {
    cerr << "deg too large in orthpoly_constant_begin"
         << endl;
  }
  for (is=1; is<=deg; is++)
  {
    if (nconst>1)
    {
      for (j=1; j<=nconst; j++)
      {
        ocoff(is,j)=1.0;
      }
      for (j=nconst+1; j<=n; j++)
      {
        ocoff(is,j)=pow(double(j-nconst+1),is);
      }
    }
    else
    {
      for (j=1; j<=n; j++)
      {
        ocoff(is,j)=pow(double(j),is);
      }
    }
  }
  for (is=0; is<=deg; is++) /* L1000  */
  {
    for (ik=0; ik<=is-1; ik++) /* L2000  */
    {
      sum=ocoff(is)*ocoff(ik);
      ocoff(is)-=sum*ocoff(ik);
    }
    sum=norm2(ocoff(is));
    ocoff(is)=ocoff(is)/sqrt(sum);
  }
  int ps=0;
  if (ps)
  {
    dmatrix tmp(0,deg,0,deg);
    for (int i=0;i<=deg;i++)
    {
      for (int j=0;j<=deg;j++)
      {
        tmp(i,j)=ocoff(i)*ocoff(j);
      }
    }
    cout << tmp << endl;
  }
  return trans(ocoff);
}

/**
 * Description not yet available.
 * \param
 */
dmatrix orthpoly_constant_begin_end(int n,int deg,int nconst_begin,
  int end_degree,int nconst_end)
{
  int j; int is; int ik;
  dmatrix ocoff(0,deg,1,n);
  double sum;
  ocoff(0)=sqrt(double(n));
  if (nconst_begin>n-1)
  {
    cerr << "nconst_begin too large in orthpoly_constant_begin"
         << endl;
  }
  if (deg>n-nconst_begin)
  {
    cerr << "deg too large in orthpoly_constant_begin"
         << endl;
  }
  for (is=1; is<=deg; is++)
  {
    if (nconst_begin>1)
    {
      for (j=1; j<=nconst_begin; j++)
      {
        ocoff(is,j)=1.0;
      }
      for (j=nconst_begin+1; j<=n; j++)
      {
        int jj=j;
        if (j>n-nconst_end+1 && is>=end_degree)
        {
          jj=n-nconst_end+1;
        }
        ocoff(is,j)=pow(double(jj-nconst_begin+1)/n,is);
      }
    }
    else
    {
      for (j=1; j<=n; j++)
      {
        int jj=j;
        if (j>n-nconst_end+1 && is>=end_degree)
        {
          jj=n-nconst_end+1;
        }
        ocoff(is,j)=pow(double(jj)/n,is);
      }
    }
  }
  for (is=0; is<=deg; is++) /* L1000  */
  {
    for (ik=0; ik<=is-1; ik++) /* L2000  */
    {
      sum=ocoff(is)*ocoff(ik);
      ocoff(is)-=sum*ocoff(ik);
    }
    sum=norm2(ocoff(is));
    ocoff(is)=ocoff(is)/sqrt(sum);
  }
  int ps=0;
  if (ps)
  {
    dmatrix tmp(0,deg,0,deg);
    for (int i=0;i<=deg;i++)
    {
      for (int j=0;j<=deg;j++)
      {
        tmp(i,j)=ocoff(i)*ocoff(j);
      }
    }
    cout << tmp << endl;
  }
  return trans(ocoff);
}

/**
 * Description not yet available.
 * \param
 */
dmatrix seldif_basis(int n)
{

  int i; int j;
  dmatrix ocoff(1,n,1,n);
  dmatrix ocoff1(1,n,1,n);
  ocoff.initialize();
  ocoff1.initialize();
  for (i=1; i<=n; i++)
  {
    for (j=i; j<=n; j++)
    {
      ocoff(i,j)=1;
    }
  }
  ocoff1=trans(ocoff);

  for (i=1; i<=n; i++) /* L1000  */
  {
    for (j=1; j<=i-1; j++) /* L2000  */
    {
      ocoff(i)-=(ocoff(i)*ocoff(j))*ocoff(j);
    }
    ocoff(i)/=norm(ocoff(i));
  }
  ocoff=trans(ocoff);

  cout << setw(10) << setprecision(4) << ocoff1 << endl << endl;

  dmatrix tmp1=(inv(ocoff1)*ocoff);
  dvector a(1,n);
  dvector b(1,n);

  for (i=1; i<=n; i++) /* L1000  */
  {
    a(i)=tmp1(i,i);
  }
  b(1)=0.0;
  for (i=2; i<=n; i++) /* L1000  */
  {
    b(i)=tmp1(i-1,i);
  }

  cout << a << endl << endl;
  cout << b << endl << endl;

  cout << ocoff1*tmp1(1) << endl;
  cout << ocoff1*tmp1(2) << endl;
  cout << ocoff1 *tmp1(3) << endl;
  cout << (ocoff1*tmp1(1)) * (ocoff1 *tmp1(3)) << endl;
  cout << (ocoff1*tmp1(2)) * (ocoff1 *tmp1(3)) << endl;

  return ocoff1;
}
