/**
 * $Id: f1b2sol2.cpp 789 2010-10-05 01:01:09Z johnoel $
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include <df1b2fun.h>

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
df1b2vector solve(const df1b2matrix& aa,const df1b2vector& z,
  const df1b2variable & ln_unsigned_det,double& sign);

df1b2vector solve(const df1b2matrix& aa,const df1b2vector& z,
  const df1b2variable& ld, df1b2variable& sign)
{
  double sgn = 0;
  return solve(aa,z,ld,sgn);
}

df1b2vector csolve(const df1b2matrix& aa,const df1b2vector& z)
{
  double ln_unsigned_det = 0;
  double sign = 0;
  df1b2vector sol=solve(aa,z,ln_unsigned_det,sign);
  return sol;
}

df1b2vector solve(const df1b2matrix& aa,const df1b2vector& z)
{
  df1b2variable ln_unsigned_det;
  double sign;
  df1b2vector sol=solve(aa,z,ln_unsigned_det,sign);
  return sol;
}

/** LU Decomposition solver.
    \n\n The implementation of this algorithm was inspired by
    "Numerical Recipes in C", 2nd edition,
    Press, Teukolsky, Vetterling, Flannery, chapter 2
*/
df1b2vector solve(const df1b2matrix& aa,const df1b2vector& _z,
  const df1b2variable & _ln_unsigned_det,double& sign)
{
  ADUNCONST(df1b2variable,ln_unsigned_det)
  ADUNCONST(df1b2vector,z)
  int i,j,k,n;
  n=aa.colsize();
  int lb=aa.colmin();
  int ub=aa.colmax();
  if (lb!=aa.rowmin()||ub!=aa.colmax())
  {
    cerr << "Error matrix not square in solve()"<<endl;
    ad_exit(1);
  }
  df1b2matrix bb(lb,ub,lb,ub);
  bb=aa;
  ivector indx(lb,ub);
  int One=1;
  indx.fill_seqadd(lb,One);
  double  d;
  df1b2variable big,dum,sum,temp;
  df1b2vector vv(lb,ub);

  d=1.0;
  for (i=lb;i<=ub;i++)
  {
    big=0.0;
    for (j=lb;j<=ub;j++)
    {
      temp=fabs(bb(i,j));
      if (value(temp) > value(big))
      {
        big=temp;
      }
    }
    if (value(big) == 0.0)
    {
      cerr <<
        "Error in matrix inverse -- matrix singular in inv(df1b2matrix)\n";
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
      if ( value(dum) >= value(big))
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

    if (value(bb(j,j)) == 0.0)
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
  df1b2vector part_prod(lb,ub);
  part_prod(lb)=log(fabs(bb(lb,lb)));
  if (value(bb(lb,lb))<0) sign=-sign;
  for (j=lb+1;j<=ub;j++)
  {
    if (value(bb(j,j))<0) sign=-sign;
    part_prod(j)=part_prod(j-1)+log(fabs(bb(j,j)));
  }
  ln_unsigned_det=part_prod(ub);

  df1b2vector x(lb,ub);
  df1b2vector y(lb,ub);
  //int lb=rowmin;
  //int ub=rowmax;
  df1b2matrix& b=bb;
  ivector indxinv(lb,ub);
  for (i=lb;i<=ub;i++)
  {
    indxinv(indx(i))=i;
  }

  for (i=lb;i<=ub;i++)
  {
    y(indxinv(i))=z(i);
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
      sum-=b(i,j)*x(j);
    }
    x(i)=sum/b(i,i);
  }

  return x;
}
#undef TINY
