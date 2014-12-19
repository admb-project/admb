/*
 * $Id$
 *
 * Authors: Anders Nielsen <anders@nielsensweb.org> and Casper Berg <cbe@aqua.dtu.dk>
 * Copyright (c) 2008-2012 Regents of the University of California
 */
/**
 * \file
 * Matrix exponential function for dvar_matrix.
 */
#include <fvar.hpp>
#define TINY 1.0e-20;

/**
 * Description not yet available.
 * \param
 */
dmatrix fabs(const dmatrix & X){
  int rmin = X.rowmin();
  int rmax = X.rowmax();
  int cmin = X.colmin();
  int cmax = X.colmax();
  dmatrix ret(rmin,rmax,cmin,cmax);
  for(int i = rmin; i<=rmax; ++i){
    for(int j = cmin; j<=cmax; ++j){
      ret(i,j) = fabs(X(i,j));
    }
  }
  return ret;
}

dvar_matrix solve(const dvar_matrix& aa, const dvar_matrix& tz,
  dvariable ln_unsigned_det, dvariable& sign);

dvar_matrix solve(const dvar_matrix& aa, const dvar_matrix& tz)
{
  dvariable ln;
  dvariable sgn;
  return solve(aa,tz,ln,sgn);
}

  /**
  \ingroup matop
   Matrix exponential.

The matrix exponential is calculated using the Pade approximation adapted from
Moler, Cleve; Van Loan, Charles F. (2003), "Nineteen Dubious Ways to Compute the
Exponential of a Matrix, Twenty-Five Years Later"

The main use of the matrix exponential is to solve linear ordinary differential
equation (ODE) systems:
\f[
\frac{d}{dt}y(t) = Ay(t)\ , \ \mbox{with } y(0) = y_0
\f]
   \item then the solution becomes
\f[
   y(t) = e^{At}y_0
\f]

  \param A square dmatrix
  \returns The matrix exponential of A
  */
dmatrix expm(const dmatrix& A)
{
  int rmin = A.rowmin();
  int rmax = A.rowmax();
  if(rmax != A.colmax())
  {
    cout<<"Error: Not square matrix in expm."<<endl;
    ad_exit(1);
  }
  if(rmin != A.colmin())
  {
    cout<<"Error: Not square matrix in expm."<<endl;
    ad_exit(1);
  }
  dmatrix I(rmin,rmax,rmin,rmax);
  dmatrix AA(rmin,rmax,rmin,rmax);
  dmatrix X(rmin,rmax,rmin,rmax);
  dmatrix E(rmin,rmax,rmin,rmax);
  dmatrix D(rmin,rmax,rmin,rmax);
  dmatrix cX(rmin,rmax,rmin,rmax);
  I.initialize();
  for(int i = rmin; i<=rmax; ++i){I(i,i) = 1.0;}
  double log2NormInf;
  log2NormInf = log(max(rowsum(fabs(A))));
  log2NormInf/=log(2.0);
  int e = (int)log2NormInf + 1;
  int s = e+1;
  s = (s<0) ? 0 : s;
  AA = 1.0/pow(2.0,s)*A;
  X = AA;
  double c = 0.5;

  E = I+c*AA;
  D = I-c*AA;
  int q = 6, p = 1;
  for(int k = 2;  k<=q; ++k){
    c*=((double)q-k+1.0)/((double)k*(2*q-k+1));
    X = AA*X;
    cX = c*X;
    E+=cX;
    if(p==1){D+=cX;}else{D-=cX;}
    p = (p==1) ? 0 : 1;
  }
  // E = inv(D)*E;
  E = solve(D,E);
  for(int k = 1; k<=s; ++k){
    E = E*E;
  }
  return E;
}

  /**
  \ingroup matop
   Matrix exponential.

The matrix exponential is calculated using the Pade approximation adapted from
Moler, Cleve; Van Loan, Charles F. (2003), "Nineteen Dubious Ways to Compute the
Exponential of a Matrix, Twenty-Five Years Later"


The main use of the matrix exponential is to solve linear ordinary differential
equation (ODE) systems:
\f[
\frac{d}{dt}y(t) = Ay(t)\ , \ \mbox{with } y(0) = y_0
\f]
   \item then the solution becomes
\f[
   y(t) = e^{At}y_0
\f]

  \param A square dvar_matrix
  \returns The matrix exponential of A
  */
dvar_matrix expm(const dvar_matrix& A)
{
  RETURN_ARRAYS_INCREMENT();
  int rmin = A.rowmin();
  int rmax = A.rowmax();

  if(rmax != A.colmax())
  {
    cout<<"Error: Not square matrix in expm."<<endl;
    ad_exit(1);
  }
  if(rmin != A.colmin())
  {
    cout<<"Error: Not square matrix in expm."<<endl;
    ad_exit(1);
  }

  dvar_matrix I(rmin,rmax,rmin,rmax);
  dvar_matrix AA(rmin,rmax,rmin,rmax);
  dvar_matrix X(rmin,rmax,rmin,rmax);
  dvar_matrix E(rmin,rmax,rmin,rmax);
  dvar_matrix D(rmin,rmax,rmin,rmax);
  dvar_matrix cX(rmin,rmax,rmin,rmax);

  I.initialize();
  for(int i = rmin; i<=rmax; ++i){I(i,i) = 1.0;}

  dvariable log2NormInf;
  log2NormInf = log(max(rowsum(fabs(value(A)))));
  log2NormInf/=log(2.0);
  int e = (int)value(log2NormInf) + 1;
  int s = e+1;
  s = (s<0) ? 0 : s;
  AA = 1.0/pow(2.0,s)*A;

  X = AA;
  dvariable c = 0.5;

  E = I+c*AA;
  D = I-c*AA;
  int q = 6, p = 1, k;
  for(k = 2;  k<=q; ++k){
    c*=((double)q-k+1.0)/((double)k*(2*q-k+1));
    X = AA*X;
    cX = c*X;
    E+=cX;
    if(p==1){D+=cX;}else{D-=cX;}
    p = (p==1) ? 0 : 1;
  }
  // E = inv(D)*E;
  E = solve(D,E);
  for(k = 1; k<=s; ++k){
    E = E*E;
  }
  RETURN_ARRAYS_DECREMENT();
  return E;
}

dvar_matrix solve(const dvar_matrix& aa, const dvar_matrix& tz,
  dvariable ln_unsigned_det, dvariable& sign)
{
  RETURN_ARRAYS_INCREMENT();
  int n = aa.colsize();
  int lb=aa.colmin();
  int ub=aa.colmax();
  if (lb!=aa.rowmin()||ub!=aa.colmax())
  {
    cerr << "Error matrix not square in solve()"<<endl;
    ad_exit(1);
  }
  dvar_matrix bb(lb,ub,lb,ub);
  bb=aa;
  ivector indx(lb,ub);
  int One=1;
  indx.fill_seqadd(lb,One);
  dvariable d;
  dvariable big,dum,sum,temp;
  dvar_vector vv(lb,ub);

  d=1.0;
  for (int i=lb;i<=ub;i++)
  {
    big=0.0;
    for (int j=lb;j<=ub;j++)
    {
      temp=fabs(bb(i,j));
      if (temp > big)
      {
        big=temp;
      }
    }
    if (big == 0.0)
    {
     cerr << "Error in matrix inverse -- matrix singular in inv(dvar_matrix)\n";
    }
    vv[i]=1.0/big;
  }

  for (int j=lb;j<=ub;j++)
  {
    for (int i=lb;i<j;i++)
    {
      sum=bb(i,j);
      for (int k=lb;k<i;k++)
      {
        sum -= bb(i,k)*bb(k,j);
      }
      //a[i][j]=sum;
      bb(i,j)=sum;
    }
    int imax = j;
    big=0.0;
    for (int i=j;i<=ub;i++)
    {
      sum=bb(i,j);
      for (int k=lb;k<j;k++)
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
      for (int k=lb;k<=ub;k++)
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
      for (int i=j+1;i<=ub;i++)
      {
        bb(i,j) = bb(i,j) * dum;
      }
    }
  }

  // get the determinant
  sign=d;
  dvar_vector part_prod(lb,ub);
  part_prod(lb)=log(fabs(bb(lb,lb)));
  if (bb(lb,lb)<0) sign=-sign;
  for (int j=lb+1;j<=ub;j++)
  {
    if (bb(j,j)<0) sign=-sign;
    part_prod(j)=part_prod(j-1)+log(fabs(bb(j,j)));
  }
  ln_unsigned_det=part_prod(ub);

  dvar_matrix z=trans(tz);
  int mmin=z.indexmin();
  int mmax=z.indexmax();
  dvar_matrix x(mmin,mmax,lb,ub);
  //dvar_vector x(lb,ub);

  dvar_vector y(lb,ub);
  //int lb=rowmin;
  //int ub=rowmax;
  dvar_matrix& b=bb;
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
      sum=y(i);
      for (int j=lb;j<=i-1;j++)
      {
        sum-=b(i,j)*y(j);
      }
      y(i)=sum;
    }
    for (int i=ub;i>=lb;i--)
    {
      sum=y(i);
      for (int j=i+1;j<=ub;j++)
      {
        sum-=b(i,j)*x(kk)(j);
      }
      x(kk)(i)=sum/b(i,i);
    }
  }
  RETURN_ARRAYS_DECREMENT();
  return trans(x);
}
#undef TINY
