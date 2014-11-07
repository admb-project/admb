/*
 * $Id$
 *
 * Authors: Anders Nielsen <anders@nielsensweb.org> and Casper W. Berg <cbe@aqua.dtu.dk>
 * Copyright (c) 2008-2012 Regents of the University of California
 */
/**
 * \file
 * Matrix exponential function for df1b2_matrix.
 */

#include <df1b2fun.h>
#define TINY 1.0e-20;

/**
 * Description not yet available.
 * \param
 */
df1b2matrix solve(const df1b2matrix& aa,const df1b2matrix& tz)
{
  df1b2variable ln;
  df1b2variable sgn;
  return solve(aa,tz,ln,sgn);
}

/**
 * Description not yet available.
 * \param
 \n\n The implementation of this algorithm was inspired by
    "Numerical Recipes in C", 2nd edition,
    Press, Teukolsky, Vetterling, Flannery, chapter xx
 */
df1b2matrix solve(const df1b2matrix& aa,const df1b2matrix& tz,
  df1b2variable ln_unsigned_det,df1b2variable& sign)
{
  RETURN_ARRAYS_INCREMENT();
  int n = aa.colsize();
  int lb = aa.colmin();
  int ub = aa.colmax();
  if (lb!=aa.rowmin()||ub!=aa.colmax())
  {
    cerr << "Error matrix not square in solve()"<<endl;
    ad_exit(1);
  }
  df1b2matrix bb(lb,ub,lb,ub);
  bb = aa;
  ivector indx(lb,ub);
  int One = 1;
  indx.fill_seqadd(lb,One);
  df1b2variable d;
  df1b2variable big,dum,sum,temp;
  df1b2vector vv(lb,ub);

  d = 1.0;
  for (int i = lb;i<=ub;i++)
  {
    big = 0.0;
    for (int j = lb;j<=ub;j++)
    {
      temp = fabs(bb(i,j));
      if (value(temp) > value(big))
      {
        big = temp;
      }
    }
    if (value(big) == 0.0)
    {
      cerr <<
        "Error in matrix inverse -- matrix singular in inv(df1b2matrix)\n";
    }
    vv[i] = 1.0/big;
  }

  for (int j = lb;j<=ub;j++)
  {
    for (int i = lb;i<j;i++)
    {
      sum = bb(i,j);
      for (int k = lb;k<i;k++)
      {
        sum -= bb(i,k)*bb(k,j);
      }
      // a[i][j] = sum;
      bb(i,j) = sum;
    }
    int imax = j;
    big = 0.0;
    for (int i = j;i<=ub;i++)
    {
      sum = bb(i,j);
      for (int k = lb;k<j;k++)
      {
        sum -= bb(i,k)*bb(k,j);
      }
      bb(i,j) = sum;
      dum = vv[i]*fabs(sum);
      if (value(dum) >= value(big))
      {
        big = dum;
        imax = i;
      }
    }
    if (j != imax)
    {
      for (int k = lb;k<=ub;k++)
      {
        dum = bb(imax,k);
        bb(imax,k) = bb(j,k);
        bb(j,k) = dum;
      }
      d = -1.*d;
      vv[imax] = vv[j];

      // if (j<ub)
      {
        int itemp = indx(imax);
        indx(imax) = indx(j);
        indx(j) = itemp;
      }
      // cout << "indx= " <<indx<<endl;
    }

    if (value(bb(j,j)) == value(0.0))
    {
      bb(j,j) = TINY;
    }

    if (j != n)
    {
      dum = 1.0/bb(j,j);
      for (int i = j+1;i<=ub;i++)
      {
        bb(i,j) = bb(i,j) * dum;
      }
    }
  }

  // get the determinant
  sign = d;
  df1b2vector part_prod(lb,ub);
  part_prod(lb) = log(fabs(bb(lb,lb)));
  if (value(bb(lb,lb))<0) sign=-sign;
  for (int j = lb+1;j<=ub;j++)
  {
      if (value(bb(j,j))<0) sign=-sign;
    part_prod(j) = part_prod(j-1)+log(fabs(bb(j,j)));
  }
  ln_unsigned_det = part_prod(ub);

  df1b2matrix z = trans(tz);
  int mmin = z.indexmin();
  int mmax = z.indexmax();
  df1b2matrix x(mmin,mmax,lb,ub);
  // df1b2vector x(lb,ub);

  df1b2vector y(lb,ub);
  // int lb = rowmin;
  // int ub = rowmax;
  df1b2matrix& b = bb;
  ivector indxinv(lb,ub);
  for (int i = lb;i<=ub;i++)
  {
    indxinv(indx(i)) = i;
  }
  for (int kk = mmin;kk<=mmax;kk++)
  {
    for (int i = lb;i<=ub;i++)
    {
      y(indxinv(i)) = z(kk)(i);
    }

    for (int i = lb;i<=ub;i++)
    {
      sum = y(i);
      for (int j = lb;j<=i-1;j++)
      {
        sum-=b(i,j)*y(j);
      }
      y(i) = sum;
    }
    for (int i = ub;i>=lb;i--)
    {
      sum = y(i);
      for (int j = i+1;j<=ub;j++)
      {
        sum-=b(i,j)*x(kk)(j);
      }
      x(kk)(i) = sum/b(i,i);
    }
  }
  RETURN_ARRAYS_DECREMENT();
  return trans(x);
}

/**
  \ingroup matop
   Matrix exponential.

   The matrix exponential is calculated using the Pade approximation adapted from Moler, Cleve; Van Loan, Charles F. (2003), "Nineteen Dubious Ways to Compute the Exponential of a Matrix, Twenty-Five Years Later"

The main use of the matrix exponential is to solve linear ordinary differential equation (ODE) systems:
\f[
\frac{d}{dt}y(t) = Ay(t)\ , \ \mbox{with } y(0) = y_0
\f]
   \item then the solution becomes
\f[
   y(t) = e^{At}y_0
\f]

  \param A square df1b2matrix
  \returns The matrix exponential of A
  */
df1b2matrix expm(const df1b2matrix & A)
{
  RETURN_ARRAYS_INCREMENT();
  int rmin = A.rowmin();
  int rmax = A.rowmax();

  if(rmax != A.colmax())
    {cout<<"Error: Not square matrix in expm."<<endl; ad_exit(1);}
  if(rmin != A.colmin())
    {cout<<"Error: Not square matrix in expm."<<endl; ad_exit(1);}

  df1b2matrix I(rmin,rmax,rmin,rmax);
  df1b2matrix AA(rmin,rmax,rmin,rmax);
  df1b2matrix X(rmin,rmax,rmin,rmax);
  df1b2matrix E(rmin,rmax,rmin,rmax);
  df1b2matrix D(rmin,rmax,rmin,rmax);
  df1b2matrix cX(rmin,rmax,rmin,rmax);

  I.initialize();
  for(int i = rmin; i<=rmax; ++i){I(i,i) = 1.0;}

  df1b2variable log2NormInf;
  log2NormInf = log(max(rowsum(fabs(value(A)))));
  log2NormInf/=log(2.0);
  int e = (int)value(log2NormInf) + 1;
  int s = e+1;
  s = (s<0) ? 0 : s;
  AA = 1.0/pow(2.0,s)*A;

  X = AA;
  df1b2variable c = 0.5;

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
  RETURN_ARRAYS_DECREMENT();
  return E;
}

#undef TINY
