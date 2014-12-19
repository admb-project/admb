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
#include <fvar.hpp>

/**
 * Description not yet available.
 * \param
 */
d4_array orthpoly2(int d1,int d2, int n,int m)
{
  d4_array A(0,d1,0,d2,1,n,1,m);
  d4_array B(0,d1,0,d2,1,n,1,m);
  int alpha,beta,i,j,ii,jj;
  int N=(1+d1)*(1+d2);
  ivector ialpha(1,N);
  ivector ibeta(1,N);


  for (alpha=0;alpha<=d1;alpha++)
  {
    for (beta=0;beta<=d2;beta++)
    {
      for (i=1;i<=n;i++)
      {
        for (j=1;j<=m;j++)
        {
#if defined(USE_DDOUBLE)
#undef double
          A(alpha,beta,i,j)=pow(double(i-1)/double(n-1),alpha)*
            pow(double(j-1)/double(m-1),beta);
#define double dd_real
#else
          A(alpha,beta,i,j)=pow(double(i-1)/double(n-1),alpha)*
            pow(double(j-1)/double(m-1),beta);
#endif
        }
      }
    }
  }
  ii=1;
  for (alpha=0;alpha<=d1;alpha++)
  {
    for (beta=0;beta<=d2;beta++)
    {
      ialpha(ii)=alpha;
      ibeta(ii)=beta;
      ii++;
    }
  }
  for (ii=1;ii<=N;ii++)
  {
    //cout     << "X" << endl;
    if (ii>1)
    {
//cout << dot(B(ialpha(ii-1),ibeta(ii-1)),A(ialpha(ii),ibeta(ii))) << endl;
      //cout << dot(B(ialpha(ii-1),ibeta(ii-1)),
       //  A(ialpha(ii),ibeta(ii))/norm(A(ialpha(ii),ibeta(ii)))) << endl;
    }
    B(ialpha(ii),ibeta(ii))=A(ialpha(ii),ibeta(ii))/
      norm(A(ialpha(ii),ibeta(ii)));
    //if (ii>1)
// cout << dot(B(ialpha(ii-1),ibeta(ii-1)),B(ialpha(ii),ibeta(ii))) << endl;
    //cout     << "Y" << endl;
    for (jj=ii+1;jj<=N;jj++)
    {
      A(ialpha(jj),ibeta(jj))-=
        dot(B(ialpha(ii),ibeta(ii)),A(ialpha(jj),ibeta(jj)))*
        B(ialpha(ii),ibeta(ii));
      //cout << dot(B(ialpha(ii),ibeta(ii)),A(ialpha(jj),ibeta(jj))) << endl;
    }
    //cout     << "Z" << endl;
  }
  return B;
}

/**
 * Description not yet available.
 * \param
 */
double dot(const dmatrix& M,const dmatrix& N)
{
  int mmin=M.indexmin();
  int mmax=M.indexmax();
  if (mmin!=N.indexmin() ||
      mmax!=N.indexmax() )
  {
    cerr << "matrix shapes unequal in"
      " double dot(const dmatrix& M,const dmatrix& N)"
      << endl;
    ad_exit(1);
  }
  if (M(mmin).indexmin()!=N(mmin).indexmin() ||
      M(mmin).indexmax()!=N(mmin).indexmax() )
  {
    cerr << "matrix shapes unequal in"
      " double dot(const dmatrix& M,const dmatrix& N)"
      << endl;
    ad_exit(1);
  }
  double ssum=0;
  for (int i=mmin;i<=mmax;i++)
  {
    int jmin=M(i).indexmin();
    int jmax=M(i).indexmax();
    for (int j=jmin;j<=jmax;j++)
    {
      ssum+=M(i,j)*N(i,j);
    }
  }
  return ssum;
}
